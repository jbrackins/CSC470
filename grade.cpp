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
   Feb xx, xxxx    Whatever.
   @endverbatim
 *
 *****************************************************************************/

/*************************************************************************//**
*********************************INCLUDES*************************************
******************************************************************************/
 
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h> 

/*************************************************************************//**
*********************************NAMESPACE************************************
******************************************************************************/

using namespace std;

/*************************************************************************//**
********************************FUNCTION PROTOTYPES***************************
******************************************************************************/

void compile_file(char* cpp_file);
void run_file(char* cpp_file);
string no_extension(char* input);

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Whatever
 *
 * @param[in] argc - # of arguments.
 * @param[in] argv - argument vector.
 *
 * @returns 0 - Whatever
 *
 *****************************************************************************/

int main(int argc, char ** argv)
{
    compile_file(argv[1]);    
    run_file(argv[1]);
    return 0;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Whatever
 *
 * @param[in] argc - # of arguments.
 * @param[in] argv - argument vector.
 *
 * @returns 0 - Whatever
 *
 *****************************************************************************/

void compile_file(char* cpp_file)
{
    string buffer("g++ -o");
    string file(cpp_file);
    buffer += " " + no_extension(cpp_file) + " " + file;

    system(buffer.c_str());
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Whatever
 *
 * @param[in] argc - # of arguments.
 * @param[in] argv - argument vector.
 *
 * @returns 0 - Whatever
 *
 *****************************************************************************/

void run_file(char* cpp_file)
{
    string buffer1("./");
    string buffer2("");       //ADD NECESSARY PIPELINING
    string file(cpp_file);
    buffer1 += no_extension(cpp_file) + buffer2;

    system(buffer1.c_str());
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Whatever
 *
 * @param[in] argc - # of arguments.
 * @param[in] argv - argument vector.
 *
 * @returns 0 - Whatever
 *
 *****************************************************************************/

string no_extension(char* input)
{
    string buffer(input);
    buffer.erase( buffer.find_first_of(".") );
    return buffer;
}
