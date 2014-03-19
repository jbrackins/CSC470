// Doxygen Header:
/**************************************************************************//**
* @file grade.cpp
*
* @brief This program compiles a students source code and then
* runs the resulting executable against test cases. The test
* cases are stored in <filename>.tst and the answer to that test case is
* stored in <filename>.ans. This program searches the directory level
* where the executable is stored and all folders below it for test cases.
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
* @usage This program is designed to run on a linux system with g++.
* It is run as such: ./grade <student_source_code>.cpp
******************************************************************************/
#include <iostream>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <algorithm>
#include <time.h>
#include <ctime>
using namespace std;

///////////////////////////////////////////////////////////////////////////////
////                       FUNCTION PROTOTYPES
///////////////////////////////////////////////////////////////////////////////
void drct_recur ( char * buffer);
void get_folders (char * buffer);
void get_files (char * buffer);
bool testOutput(string solution);
void gradeSolution(vector<string> tst, char arg[]);
void getTstCases();
bool compareFileNames(string a, string b);
string getDateTime();
string getFileStream(string file);


vector<string> tstLocations;
vector<string> ansLocations;

/**************************************************************************//**
 * @authors Benjamin Sherman, Anthony Morast, James Tillma
 *
 * @par Description: This is the main function. It calls the function that
 * gets all the test cases and the function that grades a students program.
 *
 * @param[in] argc - number of commandline arguments.
 * @param[in] argv - an array of strings, each string is a commandline
 * argument.
 *
 * @returns 0 Program successfully executed.
 *****************************************************************************/
int main (int argc, char* argv[])
{
    if(argc != 2)
    {
        cout << "Usage: ./grade <source_code.cpp>" << endl;
        //return -1;
    }
    ifstream fin;
    fin.open(argv[argc-1]);
    if(!fin)
    {
        cout << "Usage: ./grade <source_code.cpp>" << endl;
        cout << "Student source code does not exist or is inaccessible" << endl;
        return -1;
    }
    getTstCases();
    gradeSolution(tstLocations, argv[argc -1]);
    cout << endl;
    return 0;
}

/**************************************************************************//**
 * @authors Benjamin Sherman, Anthony Morast, James Tillma
 *
 * @par Description: This function is the compilation of some of the code
 * James and Anthony pushed to github on 2/9/14. It uses popen to process
 * all the system commands so that we can get the system command output
 * and ignore the system command output in the terminal.
 *****************************************************************************/
void gradeSolution(vector<string> tst, char arg[100])
{
    string source = "";
    string cp;
    char buffer[20] = "";
    ofstream logFile;
    int pass = 0, fail = 0;
    string input, result, sol, caseName, logFileContents = "";
    char append_str[] = "g++ "; //g++ compiler call
    // get file to execute from the command line
    source = arg;
    source = source.substr(0,source.find_last_of('.') + 1);
    source += "log";
    logFile.open(source.c_str(), ios_base::app);
    strcat(append_str,arg); //append to compiler call

    if(!logFile) return;
    for(int i = 0; i < (int)tst.size(); i++)
    {
        cp = "cp " + tst[i] + " infile.txt";
        FILE *f = popen(cp.c_str(), "r");
        f = popen(append_str, "r"); // call g++ pogramname
        pclose(f);
        // execute program
        f = popen("./a.out  < infile.txt > outfile.txt 2> /dev/null", "r"); 
        pclose(f);
        input = getFileStream(tst[i]);
        result  =  getFileStream("outfile.txt");
        sol =  getFileStream(ansLocations[i]);

        caseName = tst[i].substr(tst[i].find_last_of('/') + 1);
        caseName = caseName.substr(0, caseName.find_last_of('.'));

        if(testOutput(ansLocations[i]))
        {
            logFileContents += "\t" + getDateTime() + "\n\tpass " + caseName;
            pass += 1;
        }
        else
        {
            logFileContents += "\t" + getDateTime() + "\n\tfail " + caseName;
            fail += 1;
        }

        logFileContents += "\n\t\tInput:" + input + "\n\t\tAnswer:"
            + result + "\n\tSolution:" +  sol + "\n";
    }
    result = "";
    sprintf(buffer, "%d", pass);
    result += buffer;
    result +=  " passed\t";
    sprintf(buffer, "%d", fail);
    result += buffer;
    result += " failed\n";
    sprintf(buffer, "%d", int(100*((double)pass/(double)tst.size())));
    result += buffer;
    result += "% passed \n";
    logFileContents.insert(0, result);
    logFile << logFileContents;
    logFile.close();
}

/**************************************************************************//**
 * @author Benjamin Sherman
 *
 * @par Description: This function reads a file and stores its contents as a
 * stirng.
 *
 * @param[in] file - name of file to open.
 *
 * @returns strStream - string that represents the contents of a file.
 *****************************************************************************/
string getFileStream(string file)
{
    ifstream fin;
    string strStream = "";
    fin.open(file.c_str());
    if(!fin)
        return "";
    char stream[3000] = "", temp[3000] = "";
    strcpy(stream, "\0");
    fin.getline(temp, 512, '\n');
    while(!fin.eof())
    {
        strcat(stream, "\n\t\t");
        strcat(stream, temp);
        fin.getline(temp, 512, '\n');
    }
    fin.close();
    strStream = stream;
    return strStream;
}

/**************************************************************************//**
 * @author Benjamin Sherman
 *
 * @par Description: This function gets the current date and time and
 * formats it to a nice human readable string.
 *
 * @returns dateTime - date and time as a string.
 *****************************************************************************/
string getDateTime()
{
    char buffer[256] = "";
    string dateTime;
    char hrMnSec[9] = "";
    string m, d, y;
    time_t curTime = time(NULL);
    struct tm *curDate = localtime(&curTime);
    sprintf(buffer, "%d", curDate->tm_mon + 1);
    m = buffer;//curDate->tm_mon + 1;
    sprintf(buffer, "%d", curDate->tm_mday);
    d = buffer;//curDate->tm_mday;
    sprintf(buffer, "%d", curDate->tm_year - 100);
    y = buffer;//curDate->tm_year;
    dateTime = m + "/" + d + "/" + y;
    strftime(hrMnSec, 9, "%H:%M:%S", localtime(&curTime));
    dateTime += "  " + (string)hrMnSec;

    return dateTime;
}

/**************************************************************************//**
 * @author Benjamin Sherman
 *
 * @par Description: This is the main function. It calls the function that
 * recursively traverses the user
 * specified directory.
 *
 * @returns 0 Program successfully executed.
 *****************************************************************************/
void getTstCases ()
{
    char path[PATH_MAX] = "";
	bool ansFound;
	string tst, ans;
    getcwd(path, sizeof(path));

    drct_recur ( path);
    // check that a tst file has a matching ans file
    for(int i = 0; i < (int)tstLocations.size(); i++)
    {
		ansFound = false;
		tst = tstLocations[i].substr(0, tstLocations[i].find_last_of("."));
        tst = tst.substr(tst.find_last_of("/") + 1);
    	for(int j = 0; j < (int)ansLocations.size(); j++)
		{
            ans = ansLocations[j].substr(0, ansLocations[j].find_last_of("."));
            ans = ans.substr(ans.find_last_of("/") + 1);
            if(tst == ans)
                ansFound = true;
		}
        // discard tst file if no matching ans file found
        if(!ansFound)
            tstLocations.erase(tstLocations.begin() + i);
    }
    sort (tstLocations.begin(), tstLocations.end(), compareFileNames);
    sort (ansLocations.begin(), ansLocations.end(), compareFileNames);
}
bool compareFileNames(string a, string b)
{
    string fileA = a.substr(a.find_last_of('/') + 1);
    string fileB = b.substr(b.find_last_of('/') + 1);
    if(fileA > fileB)
        return true;
    else
        return false;
}

/**************************************************************************//**
 * @author Benjamin Sherman
 *
 * @par Description: This function calls the diff function, if there is
 * no output from the diff function, the solution is correct and it returns
 * true
 *
 * @returns true - solution is correct
 * @returns false - solution is incorrect
 *****************************************************************************/
bool testOutput(string solution)
{
    string temp = "diff " + solution + " outfile.txt";
    char result[100] = "";
    strcpy(result, "");

    FILE *f    = popen(temp.c_str(), "r");
    fgets(result, 100, f);

    //cout << result << endl;
    pclose(f);
    if(!strcmp(result, "\0"))
        return true;
    return false;
}

/**************************************************************************//**
 * @author Benjamin Sherman
 *
 * @par Description:
 * This function calls "get_folders" and "get_files". It
 * returns on completion of the these two functions.  It gets called
 * again in "get_folders" if a folder is found under the directory path
 * contained in the variable "buffer".
 *
 * @param[in] buffer - contains a file/folder directory path.
 *****************************************************************************/
void drct_recur (char * buffer)
{
    get_folders ( buffer);
    get_files (  buffer);
}

/**************************************************************************//**
 * @author Benjamin Sherman
 *
 * @par Description:
 I This function will loop through the folders and files
 * contained within the directory ignoring all of the files and stepping
 * into all of the folders by calling it's self.  This function will keep
 * calling it's self only if it finds a folder in the first directory or any
 * subdirectory after that.
 *
 * @param[in] buffer - contains a file/folder directory path.
 *****************************************************************************/
void get_folders (char * buffer)
{
    DIR *a_folder;
    struct dirent *dir_handle;
    vector<string> paths;
    bool subdir = false;
    int attrib;
    char path[PATH_MAX] = "";
    strcat(path, "~");
    strcat(path, buffer);
    a_folder = opendir(buffer);
    if ( a_folder == NULL ) // call directory
    {
        return;
    }

    dir_handle = readdir(a_folder);
    if ( dir_handle == NULL )
    {
        return;
    }
    strcpy(path, buffer);
    // search for and step into folders
    do
    {
        attrib = (int)dir_handle->d_type;
        if ( attrib == 4 && strcmp( dir_handle->d_name, "." ) != 0
             && strcmp(dir_handle->d_name, "..") != 0)
        {
            // set to true when we find and step into a folder
            subdir = true;
            char name[PATH_MAX];
            strcpy(name, dir_handle->d_name);
            strcat(path, "/");
            strcat(path, dir_handle->d_name);
            paths.push_back(path);
        }

        if (subdir)
        {
            strcat(path, "/..");
            getcwd(path, sizeof(path));
        }
        // reset test variable that determines 
        // if we found and processed a folder
        subdir = false;
        // reset path
        strcpy(path, buffer);
    } while ( (dir_handle = readdir(a_folder))!= NULL );

    while(!paths.empty())
    {   string temp =  paths.back();
        paths.pop_back();
        char pth[PATH_MAX];
        strcpy(pth, temp.c_str());
        drct_recur(pth);
    }

    closedir(a_folder);
}

/**************************************************************************//**
 * @author Benjamin Sherman
 *
 * @par Description:
 * This function will loop through the folders and files
 * contained within the directory ignoring all of the folders. It will check
 * if each file in a directory has a "tst" extension. If a file does have
 * a "tst" extension, the function will append that file's directory address
 * to the global vector<string> tstLocations.
 *
 * @param[in] buffer - contains a file/folder directory path.
 *****************************************************************************/
void get_files (char * buffer)
{
    DIR *a_file;
    struct dirent *dir_handle;

    a_file = opendir(buffer);
    dir_handle = readdir(a_file);
    string ext = dir_handle->d_name;
    string path;
    string name = dir_handle->d_name;

    if ( dir_handle != NULL )
    {
        do // search for files with "tst" extension
        {
            path = buffer;
            name = dir_handle->d_name;
            if(name.find_last_of(".") != string::npos)
            ext = name.substr(name.find_last_of(".") );
            else ext = "";
            if ( 8 == (int)dir_handle->d_type 
                && (ext == ".tst"  || ext == ".ans"))
            {
                path += ("/" + name);
                if(ext == ".tst")
	            	tstLocations.push_back(path);
                else if(ext == ".ans")
					ansLocations.push_back(path);
            }

        }
        while ( (dir_handle = readdir(a_file)) != NULL);
    }

    closedir(a_file);
}
