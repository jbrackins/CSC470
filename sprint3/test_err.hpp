/**************************************************************************//**
* @file presError.hpp
*
* @brief Declaration of functions used to check presentation error
*
* @author Hafiza Farzami
******************************************************************************/

#ifndef PRESERROR_CPP_INCLUDED
#define PRESERROR_CPP_INCLDED

#include <iostream>
#include <cmath>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <sstream>
#include <algorithm>

struct subs
{
    std::string first;
    std::string last;
};

bool compStrs1( std::string s1, std::string s2 );
bool compStrs2( std::string s1, std::string s2 );
int prezErrorCount( std::string file1, std::string file2 ); 
subs subStrings( std::string s, char delim );
bool roundNums( std::string s1, std::string s2 );
int markError( std::istringstream &first, std::istringstream &last );
std::string trim( std::string s );

#endif