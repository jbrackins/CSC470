/*************************************************************************//**
 * @file 
 *
 * @mainpage Program 1 - Automated Grading System
 * 
 * @section course_section CSC 470
 *
 * @author Julian Brackins
 * 
 * @date February 9, 2014
 * 
 * @par Professor: 
 *         Dr. Logar
 * 
 * @par Course: 
 *         CSC 470
 * 
 * @par Location: 
 *         McLaury - 313
 *
 * @section program_section Program Information 
 * 
 * @details PENDING
 *
 * @section compile_section Compiling and Usage 
 *
 * @par Compiling Instructions: 
 *      g++ -o grade grade.cpp -g or make 
 * 
 * @par Usage: 
   @verbatim  
   ./<name>
   @endverbatim 
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 * 
 * @bug PENDING 
 * 
 * @todo EVerything
 * 
 * @par Modifications and Development Timeline: 
   @verbatim 
   Date          Modification 
   ------------  -------------------------------------------------------------- 
   Feb 09, 2014  Implemented compile_file(), started run_file(). also created
                 add_extension() to handle removing extensions from .cpp files
   Feb 11, 2014  Set up GitHub. http clone url:
                 https://github.com/jbrackins/CSC470.git
   Feb 12, 2014  printed usage, revamping program structure to handle commands
                 within the software rather than via command line
                 made routine to count the number of .tst files in directory
   Feb 13, 2014  run_file() now redirects input such that case_x.tst is read
                 in as the commands for the test and case_x.out is the result
                 from forementioned test.
                 run_file() now returns integer, 1 if it passes a test case, 
                 0 if it fails
                 test_loop() runs through each test case run and tallies how 
                 many were successes
                 is_dir() detects if object in directory is a directory
                 queue_directories() recursively traverses a folder system and
                 utilizes is_dir() to find all subdirectories. Each of these
                 subdirectories found is pushed into a queue.
                 Subdirectory traversal ((((should)))) be complete.
   @endverbatim
 *
 *****************************************************************************/

/*************************************************************************//**
*********************************INCLUDES*************************************
******************************************************************************/

#define CURR_VER "1.0"
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <iostream>     //cout cin
#include <fstream>      //file i/o
#include <string>       //basic string handling. cstyle also used for directory

#include <dirent.h>     //
#include <cstring>      //
#include<sys/stat.h>    //Handling directory traversal
#include<sys/types.h>   //
#include <queue>  

/*************************************************************************//**
*********************************NAMESPACE************************************
******************************************************************************/

using namespace std;

/*************************************************************************//**
********************************FUNCTION PROTOTYPES***************************
******************************************************************************/

void compile_file(string cpp_file);
int run_file(string cpp_file, string test_case);
string add_extension(string input);
string get_extension(string input);
bool change_dir(string dir_name);
string get_pathname();
int count_case();       //POSSIBLY OBSOLETE, JUST RETURN SIZE OF TEST CASE QUEUE...

string case_name(string test_case, string ext);
void test_loop(string cpp_file);
bool event_loop();
int result_compare(string test_file);
void usage();
bool is_dir(string dir);
void queue_directories(string base_dir, queue<string>& queue);

void dir_list();
void queue_test_cases(queue<string>& queue);

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Main function. 
 * Simply prints usage() statement then executes the event_loop().
 *
 * @param[in] argc - # of arguments.
 * @param[in] argv - argument vector.
 *
 * @returns 0 - successfully exit program.
 *
 *****************************************************************************/

int main(int argc, char ** argv)
{

    usage();
    while(event_loop() == true){};

    return 0;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Using C++ String manipulation, a g++ compile command is sent to the
 * terminal in order to compile the file brought in by the argument
 * cpp_file.
 *
 * The compile line is as follows
 * compile_file(example.cpp);
 * "g++ -o example example.cpp"
 *
 * @param[in] cpp_file - name of .cpp file to be compiled by program
 *
 * @returns none
 *
 *****************************************************************************/

void compile_file(string cpp_file)
{
    string buffer("g++ -o");
    buffer += " " + cpp_file + " " + add_extension(cpp_file);
    system(buffer.c_str());
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Using C++ String manipulation, a command is sent to the terminal in 
 * order to run the file brought in by the argument cpp_file
 * String buffers are used to handle piping both for inputting
 * An integer value is returned from this function.
 * A 0 indicates the program failed the test case.
 * A 1 indicates the program has identical results to the test case.
 *
 * The run line sent to system() is as follows
 * run_file(example, case_x.tst);
 * <full_path>/./example < case_x.tst > case_x.out 
 *
 * @param[in] cpp_file - name of program file to be run
 * @param[in] test_case - string with test case file name
 *
 * @returns result_compare(test_case) - 0 if test fails, 1 if test succeeds
 *
 *****************************************************************************/

int run_file(string cpp_file, string test_case) //case_num
{
    //create .out file name
    string case_out(case_name(test_case, "out"));

    //set up piping buffers
    string buffer1("");
    string buffer2(" < ");
    string buffer3(" > ");

    //construct run command, then send to system
    buffer1 += cpp_file + buffer2 + test_case + buffer3 + case_out;
    system(buffer1.c_str());

    //0 = Fail, 1 = Pass
    return result_compare(test_case);
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * This function is needed to handle the addition of the .cpp extension on file
 * names. This is important, for example, when compiling the file, as you need
 * the full name of the file (example.cpp) as well as the name of the file sans
 * extension (example)
 *
 * @param[in] input - string containing file name
 *
 * @returns newstring - string similar to parameter input with .cpp extension
 *
 *****************************************************************************/

string add_extension(string input)
{
    input.append(".cpp");  
    return input;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * This function is needed to detect the extension on a given file. The
 * extension on the given file is returned as a string.
 * Used for detecting whether files in a directory contain a .tst extension,
 * therefore indicating that the file is a test case.
 *
 * @param[in] input - string containing file name and extension
 *
 * @returns extension - file extension
 *
 *****************************************************************************/
string get_extension(string input)
{
    unsigned found = input.find_last_of(".");
    string extension( input.substr(found+1) );
    return extension;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Directory traversal is quintessential in this program in order to find all
 * available test cases for a given program. change_dir() is the heart of the
 * traversal functions designed for this project.
 * It should be noted that most path names read in here should be the full
 * path name to avoid getting stuck in deep-nested directories. Using the full
 * path will allow the program to change to a specific directory, rather than 
 * be restricted to the sub directories present in the current path.
 * Regardless, the function returns a boolean value to indicate whether or not
 * the directory change was successful.
 *
 * @param[in] dir_name - full path of a directory
 *
 * @returns true - successful directory change
 * @returns false - failed to change directories
 *
 *****************************************************************************/
bool change_dir(string dir_name)
{
    string path;
    if(chdir(dir_name.c_str()) == 0) 
    {
        path = get_pathname();
        //cout << "In " << path << "\n";
        return true;
    }
    return false;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Returns a string with the current working directory. Useful not only in
 * testing, as the directory traversal can be confusing, but is also needed to
 * pass in pathnames as parameters for other functions in the program.
 *
 * 
 * @returns path - string containing the current working directory
 *
 *****************************************************************************/

string get_pathname()
{
    char buffer[1024];
    string path;

    getcwd(buffer, sizeof(buffer));
    //printf("In %s\n", buffer);
    path = buffer;

    return path;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Find number of test cases in directory.
 * Using DIR, current directory is traversed. The name of each file and directory
 * is read in one by one to the DIR pointer. Every file with a tst extension is
 * tallied to count the total number of test cases in the directory.
 *
 * @returns count - number of .tst files in current directory
 *
 *****************************************************************************/
int count_case()
{
    DIR *dp;
    int count = 0;
    char* name;
    struct dirent *ep;     
    dp = opendir ("./");

    //cout << get_pathname() << endl;
    if (dp != NULL)
    {
        while (ep = readdir (dp))
        {
            name = ep->d_name;
            string str_name(get_extension(name));
            if (str_name.compare("tst") == 0)
                count++;
        }
        (void) closedir (dp);
    }
    //printf("There's %d file(s) in the directory.\n", count);

    return count;
}


/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * String mutation to create a file of the same name, but with a different
 * extension.
 *
 * @param[in] test_case - string containing file name and extension
 * @param[in] ext - new file name extension
 *
 * @returns temp - new string with extension the same as the ext param.
 *
 *****************************************************************************/
string case_name(string test_case, string ext)
{
    char buffer [20];
    int n;
    string temp(test_case.begin(), test_case.end()-4);

    //get a new extension (brought in by second parameter)
    if ( ext.compare("tst") == 0)
        temp += ".tst";
    else if ( ext.compare("ans") == 0)
        temp += ".ans";
    else if ( ext.compare("out") == 0)
        temp += ".out";
    else if ( ext.compare("tmp") == 0)
        temp += ".tmp";
    else if ( ext.compare("log") == 0)
        {
            //HANDLE TIMESTAMP
            temp += ".log";
        }
    else
        cout << "Please indicate an extension in second parameter...\n";
    return temp;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * The algorithm for traversing through each directory, running the program 
 * and checking the results from the test cases present in each subdirectory.
 *
 * The algorithm is as follows: 
 * -create a queue of every subdirectory in program folder
 * -change to directory where program is located
 * -compile program
 * -while subdirectory queue is not empty:
 *   -de-queue first subdirectory in queue
 *     -change into that subdirectory
 *   -create a queue of every .tst file in current directory
 *   -while test case queue is not empty:
 *   -de-queue first test case in queue
 *     -run program using that test case
 *       -count whether the program passed or failed test case
 * -change back to home directory (where program is located)
 * -create a queue of every .tst file in home directory
 *   -while test case queue is not empty:
 *   -de-queue first test case in queue
 *     -run program using that test case
 *       -count whether the program passed or failed test case
 *
 * @param[in] cpp_file - program name
 *
 * @returns none
 *
 *****************************************************************************/
void test_loop(string cpp_file)
{
    int test_cases_temp = 0;
    int test_cases_total = 0;
    int i;
    int total = 0;

    queue<string> sub_dir;                  //queue of all the subdirectories
    queue<string> test_cases;               //queue of test cases in current directory

    queue_directories(cpp_file, sub_dir);   //place all subdirectory names in queue
    string homepath(get_pathname() + "/");  //create string with home path name

    string subpath(get_pathname() + "/");   //create a string with current directory path

    string progpath(get_pathname() + "/" + cpp_file + "/"); //string with path to prog file

    //TEST OUTPUT
    //cout << "subpath " << progpath << endl;
    //cout << "queue size: " << sub_dir.size() << endl;


    change_dir(progpath);       //change directory to where prog file is located
    compile_file(cpp_file);     //compile the prog file

    while(sub_dir.size() != 0)  //sub_dir queue is empty if you're done testing all subdirectories
    {       
        change_dir(homepath + sub_dir.front()); //change to next subdirectory in queue 
        sub_dir.pop();                          //remove that sub directory from queue
        queue_test_cases(test_cases);           //queue .tst files in current directory

        test_cases_temp = count_case();         //count the number of .tst files... MIGHT REMOVE
        test_cases_total += test_cases_temp;

        while(test_cases.size() != 0)   //test_cases is empty if done testing current directory
        {
            subpath = get_pathname() + "/";     //reset current subpath
            //cout << "TEST CASE: " << test_cases.front() << endl;
            //count successful tests
            //run program using currently queued test case
            //remove test case from queue.
            total += run_file(progpath + cpp_file, subpath + test_cases.front());
            test_cases.pop();   
        }
    }

    //test to see if there are any test cases in the home directory of the cpp as well!!
    change_dir(homepath + cpp_file);
    queue_test_cases(test_cases);
    test_cases_temp = count_case();
    test_cases_total += test_cases_temp;


    while(test_cases.size() != 0) //test_cases is empty if done testing home directory
    {
        subpath = get_pathname() + "/";
        total += run_file(progpath + cpp_file, subpath + test_cases.front());
        test_cases.pop();
    }

    cout << "\n\n\n\n\n\n\n" << total << "/" << test_cases_total << " test cases passed\n";

    //return to the homepath if not there already (important for next test)
    change_dir(homepath);
    }


/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Prints usage statement
 *
 * @returns true  - basically anything EXCEPT "exit" was sent to the console
 * @returns false - "exit" was sent to console
 *
 *****************************************************************************/
bool event_loop()
{
    string input;
    string arg;
    char* command;
    char* filename;
    char buffer[100];

    cout << ">> ";             //prompt

    //read in commands, break up arguments into tokens
    fgets(buffer,100, stdin);
    command = strtok(buffer," \n");
    filename = strtok(NULL, " \n");

    //Check to see if NULL command was sent from console
    if(command != NULL)
    {
        input = command;
        
        //test <filename>
        //handle improper commands here as well
        if(input.compare("test") == 0)
        {
            if(filename != NULL)
            {
            arg = filename;
            cout << "testing " << arg << "\n";

            test_loop(arg);
        }
        else
            cout << "Invalid Input!!\n";
        }
        //Print list of "program" folders
        if(input.compare("dir") == 0)
            dir_list();
        //Exit
        if(input.compare("exit") == 0)
        {
            cout << "Exiting Program...\n";
            return false;
        }
    }
    return true;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * The result_compare() function is designed to determine whether or not the
 * program passes or fails a test case. in the run_file() command, the results
 * of the test are piped into a .out file with the same name as the .tst file
 * used for testing input. A file with the same name but a .ans extension will
 * contain the expected result from the given test case.
 * By this logic, a successful test case run will result in a .out file that is
 * identical to the .ans file. This function runs the diff command on the two
 * files to determine if the files are identical. If the two files match, the
 * program passed the test case, and a 1 is returned. If the files do not match,
 * a 0 is returned.
 * The results of the diff command are actually piped into a .tmp file. This
 * temporary file will be empty if the files are identical, and will contain
 * the differences between the two files if they are not identical. The file
 * is opened to determine if it has any contents, and if not, the .out and .ans
 * files can be confirmed to be identical.
 *
 * @param[in] test_file - test file name
 *
 * @returns 1 - Empty .tmp file, test passed.
 * @returns 0 - diff command yielded results, test failed.
 *
 *****************************************************************************/
int result_compare(string test_file)
{
    int length;
    ifstream fin;

    string case_out(case_name(test_file, "out"));
    string case_ans(case_name(test_file, "ans"));
    string case_tmp(case_name(test_file, "tmp"));   //create temp file
    
    //perform diff command
    string buffer("diff ");
    buffer += case_out + " " + case_ans + " > " + case_tmp;
    system(buffer.c_str());    
    
    fin.open(case_tmp.c_str(), ios::binary);    //open file
    fin.seekg(0, ios::end);                     //cursor at EOF
    length = fin.tellg();                       //find cursor position
    fin.close();

    //remove tmp file
    buffer = "rm " + case_tmp;
    system(buffer.c_str());

    if ( length == 0 ) //File is empty, no diff between .ans and .tmp
        return 1;
    else
        return 0;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Prints usage statement
 *
 * @returns none
 *
 *****************************************************************************/
void usage()
{
    cout << "\n\n*************AUTOMATED GRADING SYSTEM*************\n";
    cout << "*********************ver  ";
    cout << CURR_VER << "*********************\n\n";


    cout << "COMMANDS:\n";
    cout << "test <filename>  : compile <filename> and test it\n";  
    cout << "                   against available test suites\n";
    cout << "dir              : print a list of directories\n"; 
    cout << "                   located in current directory\n";
    cout << "exit             : exit Automated Grading System\n\n";
}









/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Prints usage statement
 *
 * @returns none
 *
 *****************************************************************************/
bool is_dir(string dir)
{
    struct stat fileInfo;
    stat(dir.c_str(), &fileInfo);
    if (S_ISDIR(fileInfo.st_mode)) {
        return true;
    } else {
        return false;
    }
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Recursively traverse the directory structure, adding the name of each
 * subdirectory to a queue. These subdirectories are the test suites, which
 * will later be referenced to run the corresponding program against each
 * test case in the subdirectory.
 *
 * @param[in] test_file - the base directory
 * @param[in,out] queue - subdirectory queue.
 *
 * @returns none
 *
 *****************************************************************************/
void queue_directories(string base_dir, queue<string>& queue)
{
    DIR *dp;
    struct dirent *dirp;
    string path;

    string dir_name(base_dir);

    base_dir += "/";
    if ((dp = opendir(base_dir.c_str())) == NULL) 
    {
        cout << "Error opening subdirectories...\n";
        return;
    } 
    else 
    {
        while ((dirp = readdir(dp)) != NULL) 
        {
            if (dirp->d_name != string(".") && dirp->d_name != string("..")) 
            {
                if (is_dir(base_dir + dirp->d_name) == true)            //it's a directory
                {
                    path = base_dir + dirp->d_name + "/";
                    //cout << path << endl;
                    queue.push(path);                                   //push string into queue
                    queue_directories(base_dir + dirp->d_name, queue);  //recursion!!
                }
            }
        }
        closedir(dp);
    }
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Prints a list of all folders in the current directory. This is useful for
 * the ./grade user, as it lists all directories that could contain programs
 * to test.
 * A modified version of queue_directories(), sans the recursion.
 * 
 * @returns none
 *
 *****************************************************************************/
void dir_list()
{
    DIR *dp;
    struct dirent *dirp;
    string path(get_pathname());
    path += "/";
    string file_name;

    if ((dp = opendir(path.c_str())) == NULL) 
    {
        cout << "Error opening directory...\n";
        return;
    } 
    else 
    {
        cout << "Directory List:\n\n";
        while ((dirp = readdir(dp)) != NULL) 
        {
            if (dirp->d_name != string(".") && dirp->d_name != string("..")) 
            {
                if (is_dir(path + dirp->d_name) == true) 
                {
                    file_name =  dirp->d_name;
                    cout << file_name << "\n";
                }
            }
        }
        closedir(dp);
    }
    cout << "\n";
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Traverse the directory, adding the name of each test case to a queue. 
 * These queued test cases will later be referenced to run the corresponding 
 * program against each test case in the directory.
 * A modified version of queue_directories(), this version points to each
 * object in the directory and determines if each one is a file, rather than a
 * directory. From there, if the file contains the .tst extension, it is added
 * to the queue. No recursion in this one, since and individual test case queue 
 * is built for each sub directory.
 *
 * @param[in,out] queue - test case queue.
 *
 * @returns none
 *
 *****************************************************************************/
void queue_test_cases(queue<string>& queue)
{
    DIR *dp;
    struct dirent *dirp;
    string path(get_pathname());
    path += "/";
    string file_name;

    if ((dp = opendir(path.c_str())) == NULL) 
    {
        cout << "Error opening directory...\n";
        return;
    } 
    else 
    {
        //cout << "files in: " << path << "\n";
        while ((dirp = readdir(dp)) != NULL) 
        {
            if (dirp->d_name != string(".") && dirp->d_name != string("..")) 
            {
                if (is_dir(path + dirp->d_name) == false)       //NOT a directory
                {
                    file_name =  dirp->d_name;
                    string ext (file_name.end()-3, file_name.end());    //get ext
                    if(ext.compare("tst") == 0)                         //check if it's a .tst
                    {
                        //cout << file_name << "\n";
                        queue.push(file_name);                  //add .tst file name to queue
                    }
                }
            }
        }
        closedir(dp);
    }
}
