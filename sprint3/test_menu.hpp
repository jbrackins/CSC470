/**************************************************************************//**
* @file test_string.h
*
* @brief An extensize suite of string manipulation functions needed for file
* names, logfile generation, extension handling, and various other operations.
*
* @authors Julian Brackins, Jonathan Dixon, Hafiza Farzami
******************************************************************************/
#ifndef TEST_MENU_CPP_INCLUDED
#define TEST_MENU_CPP_INCLDED

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


struct menu_option 
{
  char *number;
  int args;
  std::string type[123];
} ;


///////////////////////////////////////////////////////////////////////////////
////                       FUNCTION PROTOTYPES
///////////////////////////////////////////////////////////////////////////////

void read_spec_file();
void find_spec_file();
void option_generator(int opt, struct menu_option option[],int arr_size);
double random_generator(std::string kind);

#endif