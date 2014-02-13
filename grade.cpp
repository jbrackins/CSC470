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
 *      g++ -o <name> <name>.cpp -g or make 
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
#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>

/*************************************************************************//**
*********************************NAMESPACE************************************
******************************************************************************/

using namespace std;

/*************************************************************************//**
********************************FUNCTION PROTOTYPES***************************
******************************************************************************/

void compile_file(char* cpp_file);
int run_file(char* cpp_file, int case_num);
string add_extension(char* input);
string get_extension(char* input);
void change_dir(char* cpp_file);
int count_case();
string case_name(int case_num, string ext);
void test_loop(char* cpp_file);
int result_compare(int case_num);
void usage();


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
    change_dir(argv[1]);
    //compile_file(argv[1]);    
    //run_file(argv[1]);
    //count_case();
    test_loop(argv[1]);

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

void compile_file(char* cpp_file)
{
    string filename(cpp_file);
    string buffer("g++ -o");

    buffer += " " + filename + " " + add_extension(cpp_file);

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

int run_file(char* cpp_file, int case_num)
{
    int total = 0;
    string case_tst(case_name(case_num, "tst"));
    //string case_ans(case_name(case_num, "ans"));
    string case_out(case_name(case_num, "out"));
    //cout << "case suite: " << case_tst << " " << case_ans << "\n";

    string filename(cpp_file);
    string buffer1("./");
    string buffer2(" < ");
    string buffer3(" > ");
    string file(cpp_file);
    buffer1 += filename + buffer2 + case_tst + buffer3 + case_out;
    
    //cout << buffer1 << endl;
    system(buffer1.c_str());

    return result_compare(case_num);
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

string add_extension(char* input)
{
    string newstring(input);
    newstring.append(".cpp");  
    return newstring;
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

string get_extension(char* input)
{
    string newstring(input);
    unsigned found = newstring.find_last_of(".");
    string extension( newstring.substr(found+1) );
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

void change_dir(char* cpp_file)
{
    char directory[1024];

    if(chdir(cpp_file) == 0) 
    {
        getcwd(directory, sizeof(directory));
        printf("In %s\n", directory);
    }
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

    //printf("There's %d file(s) in the directory.\n", count);

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

string case_name(int case_num, string ext)
{
    char buffer [20];
    int n;
    n = sprintf (buffer, "%d", case_num);
    
    string temp(buffer);
    string new_case("case_");
    
    new_case += temp;
    if ( ext.compare("tst") == 0)
        new_case += ".tst";
    else if ( ext.compare("ans") == 0)
        new_case += ".ans";
    else if ( ext.compare("out") == 0)
        new_case += ".out";
    else if ( ext.compare("tmp") == 0)
        new_case += ".tmp";
    else
        cout << "Please indicate an extension in second parameter...\n";
    return new_case;
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
void test_loop(char* cpp_file)
{
    int test_cases;
    int i;
    int total = 0;
    test_cases = count_case();

    for(i = 0; i < test_cases; i++)
    {
        total += run_file(cpp_file, i);
    }

    cout << "\n\n\n\n\n\n\n" << total << "/" << test_cases << " test cases passed\n";
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
int result_compare(int case_num)
{
    int length;
    ifstream fin;

    string case_out(case_name(case_num, "out"));
    string case_ans(case_name(case_num, "ans"));
    string case_tmp(case_name(case_num, "tmp"));
    
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
    cout << "exit             : exit Automated Grading System\n\n";
}
