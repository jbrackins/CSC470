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

#include "main.hpp"
#include "test_dir.hpp"
#include "test_gen.hpp"
#include "test_log.hpp"
#include "test_run.hpp"
#include "test_string.hpp"
#include "test_ui.hpp"

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>

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
vector<report> INDIVIDUALREPORTS;
vector<string> TESTCASES;
vector<string> LOGVECTOR;
vector<string> SUMMARYVECTOR;
vector<string> STUDENTVECTOR;
string GOLDCPP;
string SPECFILE;
string TEMPSPEC;
string TEMPGCPP;
string HOME_DIR;
int TOTALPASSED;
int loop_time;      //time tester will allow a program to run
/****************************************************************************/

/**************************************************************************//**
 * @authors xxxxxxx
 *
 * @par Description: Main function. Sets a few default global values,
 * then invokes the user interface.
 *
 * @param[in] xxx - xxxxxxxx
 *
 * @returns xxx -
 *
 *****************************************************************************/
int main(int argc, char* argv[])
{
    loop_time = 60;

    char dir[1024];
    getcwd(dir, sizeof(dir));
    HOME_DIR = dir;
    

    main_menu();

    
    return 0;
}