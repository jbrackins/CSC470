/**************************************************************************//**
* @file grade.cpp
*
* @brief This program compiles a students source code and then
* runs the resulting executable against test cases. The test
* cases are stored in <filename>.tst and the answer to that test case is
* stored in <filename>.ans. This program searches the directory level
* where the source code is stored and all folders below it for test cases.
* The students executable's output is compared to the answers in the
* <filename>.ans files. The program tells the user if the students
* source code specified in the commandline argument is not found.
* It also tells lets the user know if they used the wrong commandline
* arguments.
*
* @mainpage Grading Progam
*
* @section course_section Course Information
*
* @authors Benjamin Sherman, Anthony Morast, James Tillma
*
* @date Februaty 19th, 2014
*
* @par Instructor:
* Dr. Logar
*
* @par Course:
* CSC 470
*
* @section Program Program 2 Information
*
* @bugs
* @usage make will invoke the Makefile. please ensure that the test executable
* file is in the testing directories root directory. This is the same folder
* that contains the test directory's "golden" cpp. It is recommended to use
* the mv command to move the test executable into this directory if it is not
* the directory in which the user has compiled the executable to begin with.
******************************************************************************/

/*******************************************************************************
  Tester.cpp
	CSC 470 Tester Program
	Date: Feb 2014
	Authors: Ryan Feather, Ryan Brown, and Kelsey Bellew
	
	Usage:
	  -Program expects to be passed a .cpp file program via the command line
	  -Program will compile and run the .cpp file passed to it and then search
		for all files ending in .tst in the current and subdirectories and read
		these files as inputs to the program being tested.
	  -Results of the tests will be listed in a .log file in the same directory
		as this program when ran.
		
	Restrictions:
	  -Program expects the .cpp file being tested to:
		o Successfully compile
		o Not crash when given the input from a .tst file
		o Take all input via the command line (cin)
*******************************************************************************/  

/*******************************************************************************
  Tester.cpp (Version 2.0.0)
	CSC 470 Tester Program
	Date: March 23 2014
	Authors: Joseph Manke, Adam Meaney and Alex Wulff
	
	Usage:
	  -This program expects to find all program source files to test in 
	   subdirectories of exectution.  This program also expects a golden or 
	   truth program's source to be located at the level of execution and all 
	   pre-built test files at the execution level or below.
	  -The program offers a text menu for test case generation and immediately
	   prompts the user at the start of the program.  The generator will 
	   terminate execution of the program and will require running again to
	   use the new test cases.
	  -Results of the tests will be listed in a .log file in the same directory
	   as all test programs when ran as well as the level of execution for a 
	   quick view of performance.  Any tests that fail a critical test as noted
	   by "*_crit.tst" will be awarded no points on earlier success and will 
	   fail.
		
	Updates:
	   All contributors of Lounge Against The Machine have noted their 
	   contributions and comments on the original by noting the start of their
	   changes with a //QQQ!!! <editor> : <comments> format.
*******************************************************************************/

#include "test_dir.hpp"
#include "test_gen.hpp"
#include "test_log.hpp"
#include "test_run.hpp"
#include "test_string.hpp"

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <string>
#include <fstream>
#include <time.h>
#include <vector>
#include <sstream>
// QQQ!!! Alex : added
#include <unistd.h>
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <dirent.h>
using namespace std;


/*********************************GLOBALS************************************/
vector<string> STUDENTVECTOR;
vector<string> TESTCASES;
string GOLDCPP;
int TOTALPASSED;
/****************************************************************************/


//Side note: GROSS, I hate hate HATE long main functions, fix this ASAP
int main(int argc, char* argv[])
{
    string progname, prog_cpp, progcomp, progdir;

    //holds each test and result on a separate line
    vector<string> finaloutfilecontents;
    finaloutfilecontents.clear();
    TOTALPASSED = 0;
    //test for proper program usage from command line
    if(argc != 1) //QQQ!!! Alex: change to != 2
    {
        cout << "\nUsage:\ntester <source_file>\n Exiting.\n" << endl;
        return -1;
    }  

    // QQQ!!! Alex : make gold cpp = ""
    GOLDCPP.clear();

    //fill strings with proper names

    // QQQ!!! Alex: moved to runtests to run on each test 
    /*  prog_cpp = argv[1];
    progname = prog_cpp.substr(0,prog_cpp.find("."));
    progcomp = "g++ -o " + progname  + " " + prog_cpp;
    size_t found = prog_cpp.find_last_of("/\\");// QQQ!!! Alex : why not just ints?
    progdir = progname.substr(0,found+1);

    //compile program to be tested
    system(progcomp.c_str());*/

    char dir[1024];
    getcwd(dir, sizeof(dir));
    string loc (dir);

    TESTCASES = find_tsts(progdir);

    find_students(loc, 0);
    //QQQ!!! Alex: inserting here for new functionality
    string ans;
    do
    {
        cout << "\nGenerate new test cases?" << endl;
        cin >> ans;
        transform( ans.begin(), ans.end(), ans.begin(), ::tolower);
        if (ans.compare("y") == 0 || ans.compare("yes") == 0 )
            {
            // make tests
            generatetestcases();
            cout << "\nTest generation completed\n\n";
            // find all tests and use generated tests to make ans
            TESTCASES = find_tsts(progdir);
            find_students(loc, 0);
            generateanswers();
            // clean  
            cleanup();
            return 0;
            }
        else if (ans.compare("n") == 0 || ans.compare("no") == 0 )
        {
            break;
        }
    }while (1);

    // QQQ!!! Alex : gathers all of the .tst files in current and sub directories of the program
    // being tested
    // vector<string> testcases;
    TESTCASES = find_tsts(progdir);

    // QQQ!!! Alex: get the testcases
    find_students(loc, 0);

    // QQQ!!! Alex : while more .tst files need ran, continue running the tests against the
    //program
    int score = 0;
    vector<string> performance;
    string currentProg;


    // QQQ!!! Alex : foreach program (edited to end of main)
    for (int h = 0; h < STUDENTVECTOR.size(); h+=1)
    {
        score = 0;
        // and for each test case
        for(int i=0;i<TESTCASES.size();i++)
        {
            /* QQQ!!! Alex: deprecating this and reworking runtests to return 0 fail, 1 pass 

            //running the test and capturing results
            string results = runtests(progname, testcases.at(i));

            //making sure the runtests() function executed successfully 
            if(results != "files did not open for comparison\n")
            {)
            //storing the results of the test into finaloutfilecontents
            finaloutfilecontents.push_back(results);
            }
            */
            int result = runtests(STUDENTVECTOR[h], TESTCASES.at(i));
            string current = TESTCASES.at(i);
            // failure on critical test
            if (result == 0 && current.substr(current.length() - 8)
                            .find("crit.tst") != -1 )
            {
                score = -1;
                // output the failure
                writeindividualreport(STUDENTVECTOR[h], TESTCASES.at(i), result);
                break; // stop tests
            }
            if (result == -999 )  //infinite loop
            {
                score = -1;
                writeindividualreport(STUDENTVECTOR[h], TESTCASES.at(i), result);
                break; //stop tests
            }
            if (result == 1)
            {
                score += 1;
                TOTALPASSED +=1;
            }
            writeindividualreport(STUDENTVECTOR[h], TESTCASES.at(i), result);
        }
        // QQQ!!! Alex : get report on this program
        currentProg = Generate_Performance_Report(STUDENTVECTOR[h], score, TESTCASES.size());
        finaloutfilecontents.push_back(currentProg);
    }

    //writing all of the results to the .out file
    writefinaloutfile(finaloutfilecontents);//QQQ!!! Alex : progname, finaloutfilecontents);  

    // clean up globals
    cleanup();
    //deleting the temp file
    //remove("temp.txt");

    //exit program
    return 0;
}
/********************************** END main **********************************/
