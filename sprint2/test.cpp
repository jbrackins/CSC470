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
* @bugs On line
* @usage This program is designed to run on a linux system with g++.
* It is run as such: ./grade <student_source_code>.cpp
******************************************************************************/

#include "test.h"
#include "test_crit.h"
#include "test_dir.h"
#include "test_gen.h"
#include "test_string.h"

/**************************************************************************//**
 * @authors Julian Brackins, Benjamin Sherman, Anthony Morast, James Tillma
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
    genTstCases();
    getTstCases();

    for(int i = 0; i < (int)cppLocations.size(); i++)
       compile_file(cppLocations[i]);
    gradeSolution(tstLocations, argv[argc -1]);

    cout << "Testing Complete" << endl;
    return 0;
}
