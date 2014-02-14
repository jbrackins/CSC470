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
int count_case();

string case_name(string test_case, string ext);
void test_loop(string cpp_file);
bool event_loop();
int result_compare(string test_file);
void usage();
bool is_dir(string dir);
void queue_directories(string baseDir, queue<string>& queue);

void dir_list();
void queue_test_cases(queue<string>& queue);

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Main function. current list of tasks:
 * compile the file given in as the first argument
 * run file given as the first argument
 * exit program
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



    //
    



    //string dir(argv[1]);
    //change_dir(dir);
    //find_subdir();
    //compile_file(argv[1]);    
    //run_file(argv[1]);
    //count_case();
    //test_loop(argv[1]);

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
 * order to run the file brought in by the argument cpp_file.
 *
 * Should work on piping next
 *
 * @param[in] cpp_file - name of .cpp file to be compiled by program
 *
 * @returns none
 *
 *****************************************************************************/

int run_file(string cpp_file, string test_case) //case_num
{
    int total = 0;

    string case_out(case_name(test_case, "out"));
    //cout << "case suite: " << case_tst << " " << case_ans << "\n";


    string buffer1("");
    string buffer2(" < ");
    string buffer3(" > ");

    buffer1 += cpp_file + buffer2 + test_case + buffer3 + case_out;
    
    //cout << buffer1 << endl;
    system(buffer1.c_str());

    return result_compare(test_case);
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * This function is needed to handle the removal of the .cpp extension on file
 * names. This is important, for example, when compiling the file, as you need
 * the full name of the file (example.cpp) as well as the name of the file sans
 * extension (example)
 *
 * @param[in] input - char* containing file name and extension
 *
 * @returns newstring - string similar to parameter input without the extension
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
 * This function is needed to handle the removal of the .cpp extension on file
 * names. This is important, for example, when compiling the file, as you need
 * the full name of the file (example.cpp) as well as the name of the file sans
 * extension (example)
 *
 * @param[in] input - char* containing file name and extension
 *
 * @returns newstring - string similar to parameter input without the extension
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
 * This function is needed to handle the removal of the .cpp extension on file
 * names. This is important, for example, when compiling the file, as you need
 * the full name of the file (example.cpp) as well as the name of the file sans
 * extension (example)
 *
 * @param[in] input - char* containing file name and extension
 *
 * @returns newstring - string similar to parameter input without the extension
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
 * This function is needed to handle the removal of the .cpp extension on file
 * names. This is important, for example, when compiling the file, as you need
 * the full name of the file (example.cpp) as well as the name of the file sans
 * extension (example)
 *
 * @param[in] input - char* containing file name and extension
 *
 * @returns newstring - string similar to parameter input without the extension
 *
 *****************************************************************************/

string get_pathname()
{
    char directory[1024];
    string path;

    getcwd(directory, sizeof(directory));
    //printf("In %s\n", directory);
    path = directory;

    return path;
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
int count_case()
{
    DIR *dp;
    int count = 0;
    char* name;
    struct dirent *ep;     
    dp = opendir ("./");

    cout << get_pathname() << endl;
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
    else
    perror ("Error in opening Directory...");

    printf("There's %d file(s) in the directory.\n", count);

    return count;
}


/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * This function is needed to handle the removal of the .cpp extension on file
 * names. This is important, for example, when compiling the file, as you need
 * the full name of the file (example.cpp) as well as the name of the file sans
 * extension (example)
 *
 * @param[in] input - char* containing file name and extension
 *
 * @returns newstring - string similar to parameter input without the extension
 *
 *****************************************************************************/

string case_name(string test_case, string ext)
{
    char buffer [20];
    int n;
    //n = sprintf (buffer, "%d", case_num);
    
    string temp(test_case.begin(), test_case.end()-4);
    //string new_case("case_");

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
 * Prints usage statement
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
    queue<string> test_cases;  
    queue_directories(cpp_file, sub_dir);
    string homepath(get_pathname() + "/");
    
    string subpath(get_pathname() + "/");

    string progpath(get_pathname() + "/" + cpp_file + "/");
    cout << "subpath " << progpath << endl;
    cout << "queue size: " << sub_dir.size() << endl;


    change_dir(progpath);
    compile_file(cpp_file);

    while(sub_dir.size() != 0)
    {
       
        change_dir(homepath + sub_dir.front()); 
        sub_dir.pop();
        queue_test_cases(test_cases);

        
        test_cases_temp = count_case();
        test_cases_total += test_cases_temp;


        while(test_cases.size() != 0)
        {
            subpath = get_pathname() + "/";
            cout << "TEST CASE: " << test_cases.front() << endl;
            total += run_file(progpath + cpp_file, subpath + test_cases.front());
            test_cases.pop();
        }



    }

//test to see if there are any test cases in the home directory for the cpp as well!!
change_dir(homepath + cpp_file);
queue_test_cases(test_cases);
test_cases_temp = count_case();
test_cases_total += test_cases_temp;


while(test_cases.size() != 0)
{
    subpath = get_pathname() + "/";
    total += run_file(progpath + cpp_file, subpath + test_cases.front());
    test_cases.pop();
}

    cout << "\n\n\n\n\n\n\n" << total << "/" << test_cases_total << " test cases passed\n";

    change_dir(homepath);
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
bool event_loop()
{
    string input;
    string arg;
    char* command;
    char* filename;
    char buffer[100];




    cout << ">> ";             //prompt
    
    /*read in commands, break up arguments into tokens*/
    fgets(buffer,100, stdin);
    command = strtok(buffer," \n");
    filename = strtok(NULL, " \n");

if(command != NULL)
{
    input = command;
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

    if(input.compare("dir") == 0)
        dir_list();

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
 * Prints usage statement
 *
 * @returns none
 *
 *****************************************************************************/
int result_compare(string test_file)
{
    int length;
    ifstream fin;

    string case_out(case_name(test_file, "out"));
    string case_ans(case_name(test_file, "ans"));
    string case_tmp(case_name(test_file, "tmp"));
    
    string buffer("diff ");
    buffer += case_out + " " + case_ans + " > " + case_tmp;
    system(buffer.c_str());    
    
    fin.open(case_tmp.c_str(), ios::binary);
    fin.seekg(0, ios::end); // cursor at EOF
    length = fin.tellg(); // find cursor position
    fin.close();

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

void queue_directories(string baseDir, queue<string>& queue)
{
    DIR *dp;
    struct dirent *dirp;
    string path;

    string dir_name(baseDir);

    baseDir += "/";
    if ((dp = opendir(baseDir.c_str())) == NULL) 
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
                if (is_dir(baseDir + dirp->d_name) == true) 
                {
                    path = baseDir + dirp->d_name + "/";
                    cout << path << endl;
                    queue.push(path);
                    queue_directories(baseDir + dirp->d_name, queue);
                }
            }
        }
        closedir(dp);
    }
}

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
        cout << "files in: " << path << "\n";
        while ((dirp = readdir(dp)) != NULL) 
        {
            if (dirp->d_name != string(".") && dirp->d_name != string("..")) 
            {
                if (is_dir(path + dirp->d_name) == false) 
                {
                    file_name =  dirp->d_name;
                    string ext (file_name.end()-3, file_name.end());
                    if(ext.compare("tst") == 0)
                    {
                        cout << file_name << "\n";
                        queue.push(file_name);
                    }
                }
            }
        }
        closedir(dp);
    }
}
