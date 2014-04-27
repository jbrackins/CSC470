/**************************************************************************//**
* @file test_ui.hpp
*
* @brief Declaration of user interface
*
* @author Julian Brackins
******************************************************************************/

#ifndef TEST_UI_CPP_INCLUDED
#define TEST_UI_CPP_INCLDED

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



#include <sys/stat.h>    //Handling directory traversal
#include <sys/types.h>   //

#define MAX_OPTIONS 3

///////////////////////////////////////////////////////////////////////////////
////                       FUNCTION PROTOTYPES
///////////////////////////////////////////////////////////////////////////////



void main_menu();
int get_choice( );
void menu_header();
void test_case_header1();
void test_case_header2();
std::string test_case_menu1();
void test_case_menu2();
void set_max_menu( );
std::string grade_program_menu();
void grade_program_header();
void set_max_header();
void print_max_time();
void dir_list();
bool is_dir(std::string dir);
void prompt();
#endif