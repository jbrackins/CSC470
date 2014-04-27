/**************************************************************************//**
* @file test_log.hpp
*
* @brief Declaration of log file generation functions
*
* @authors Jonathan Dixon, Julian Brackins, Hafiza Farzami, Alex Wulff
******************************************************************************/

#ifndef TEST_LOG_CPP_INCLUDED
#define TEST_LOG_CPP_INCLDED

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
std::string Generate_Performance_Report(std::string  file, int score, int total);
void writefinaloutfile(std::vector<std::string> finaloutfilecontents);
void writeindividualreport(std::string  program, std::string  testcase, int success, int curr);
void createReports();

#endif
