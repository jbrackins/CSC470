/**************************************************************************//**
* @file test_run.hpp
*
* @brief Declaration of functions used to grade cpp files
*
* @authors Julian Brackins, Jonathan Dixon, Hafiza Farzami
******************************************************************************/

#ifndef TEST_RUN_CPP_INCLUDED
#define TEST_RUN_CPP_INCLDED

#include <iostream>
#include <iomanip>
#include <cstdlib>

#include <stdio.h>
#include <cstring>
#include <cmath>

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

#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>

struct subs
{
    std::string first;
    std::string last;
};

int Event_REDIRECT(const char *commandline);
int runtests(std::string  prog, std::string specifictestcase);
int filesequal(std::string  file1name, std::string file2name);
void cleanup();
void progbar(int kill_pid, int runtime, std::string progname);
bool compStrs1( std::string s1, std::string s2 );
bool compStrs2( std::string s1, std::string s2 );
int prezErrorCount( std::string file1, std::string file2 ); 
subs subStrings( std::string s, char delim );
bool roundNums( std::string s1, std::string s2 );
int markError( std::istringstream &first, std::istringstream &last );
std::string trim( std::string s );
void tester();

#endif
