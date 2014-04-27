/**************************************************************************//**
* @file test_dir.hpp
*
* @brief Declaration of directory traversal functions
*
* @authors Julian Brackins, Alex Wulff
******************************************************************************/

#ifndef TEST_DIR_CPP_INCLUDED
#define TEST_DIR_CPP_INCLDED

#include <iostream>
#include <iomanip>
#include <cstdlib>

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
void find_students(std::string directory, int level);
std::vector<std::string> find_tsts(std::string progdir);
void find_spec_file(std::string directory, int level);

#endif