/**************************************************************************//**
* @file test_string.h
*
* @brief An extensize suite of string manipulation functions needed for file
* names, logfile generation, extension handling, and various other operations.
*
* @authors Julian Brackins, Jonathan Dixon, Hafiza Farzami
******************************************************************************/
#ifndef TEST_STRING_CPP_INCLUDED
#define TEST_STRING_CPP_INCLDED

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
#include <stdlib.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
////                       FUNCTION PROTOTYPES
///////////////////////////////////////////////////////////////////////////////

std::string getDateTime();
std::string getFileStream( std::string file );
std::string add_extension( std::string input );
std::string remove_extension( std::string input );
std::string get_extension( std::string input );
std::string get_filepath( std::string input );
std::string get_pathname();
std::string case_name( std::string test_case, std::string ext );
std::string timestamp();
std::string str_replace( std::string str, char a, char b );
std::string log_filename( std::string cpp_file );
double grade_percent( int right, int total );
std::string grade_letter( double grade_percent );
std::string get_student_name( std::string cpp_file );


#endif