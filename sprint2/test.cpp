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

#include "test.h"
#include "test_crit.h"
#include "test_dir.h"
#include "test_gen.h"
#include "test_string.h"

/**************************************************************************//**
 * @authors Julian Brackins, Benjamin Sherman, Anthony Morast, James Tillma
 *
 * @par Description: The Main function calls genTstCases to promt the user if
 * they would like to create any test cases, genTstCases to put all test
 * cases into a vector and to put all .cpp files into a separate vector, 
 * compile_file loop to go through to each .cpp file in the cpp file vector
 * to compile each one, and gradeSolution to run the testing suite.  
 *
 * @param[in] argc - number of commandline arguments.
 * @param[in] argv - an array of strings, each string is a commandline
 * argument.
 *
 * @returns 0 Program successfully executed.
 *****************************************************************************/
int main( int argc, char* argv[] )
{
    /*Prompt for test case generation*/
    genTstCases();
    /*getTstCases() will put each .tst file in a vector
      AND put each .cpp file (except for test.cpp) into a separate vector*/
    getTstCases();

    /*compile all the .cpp files*/
    for( int i = 0; i < ( int )cppLocations.size(); i++ )
       compile_file( cppLocations[ i ] );

    /*run the test suite!*/
    gradeSolution(tstLocations);

    cout << "Testing Complete" << endl;

    return 0;
}
