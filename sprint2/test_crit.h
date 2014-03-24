/**************************************************************************//**
* @file test_crit.h
*
* @brief This file contains lines of code used for identifying the critical
* test cases. The isCritTest function was authored by Hafiza Farzami and is
* used to identify whether the current .tst file contains the substring "_crit"
* in it, indicating critical test status. The find_goldencpp function was
* authored by Julian Brackins but borrows heavily from the make_ans function
* created by Jonathan Dixon. This function returns the string containing the
* "golden" cpp file. When generating the Summary file for the class, it should
* be noted that the golden cpp's results should be ommitted from this file.
* The golden cpp will always be correct on 100% of the test cases.
*
* @author Hafiza Farzami, Julian Brackins
******************************************************************************/
#ifndef __TEST_CRIT_H_INCLUDED__
#define __TEST_CRIT_H_INCLUDED__

#include "header.h"

///////////////////////////////////////////////////////////////////////////////
////                       FUNCTION PROTOTYPES
///////////////////////////////////////////////////////////////////////////////

bool isCritTest( string test_case );
string find_goldencpp();

/**************************************************************************//**
 * @author Hafiza Farzami
 *
 * @par Description: The following function detects whether a given test file is
 * critical or not. 
 * 
 * @param[ in ] 	test_case - the given test case's name 
 * 
 * @returns 	true - if critical test
 * @returns 	false - otherwise
 *****************************************************************************/
bool isCritTest( string test_case )
{
    cout << test_case << endl;
    size_t found = test_case.find( "_crit" );

	if( found!= string::npos )
	    return true;
    else
        return false;
}

/**************************************************************************//**
* @author Julian Brackins, Jon Dixon
*
* @par Description:
* Modified from Jon's make_ans function to simply locate and return the 
* name of the "golden" cpp file. This function is quickly run just to 
* recognize which .cpp file is the golden one simply so it is ignored from
* the summary file's output.
*
******************************************************************************/
string find_goldencpp( )
{
   char buffer[ PATH_MAX ];
   DIR *a_file;
   struct dirent *dir_handle;
   string ext;
   string path;
   string name;
   string command;
   
   //get cwd into a character buffer
   getcwd( buffer, sizeof( buffer ) );
   a_file = opendir( buffer );
   dir_handle = readdir( a_file );
   ext = dir_handle->d_name;
   name = dir_handle->d_name;
   
   //make sure directory handle is not null
   if( dir_handle != NULL )
   {
      do //search for .cpp files
      {
         //set the file path equal to the buffer, and name to the directory name
         path = buffer;
         name = dir_handle->d_name;
         
         //here, we exclude test.cpp, because we don't want to compile our own code
         if( name.find_last_of( "." ) != string::npos && name != "test.cpp" )
            ext = name.substr( name.find_last_of( "." ) );
         else
            ext = "";
         
         //make sure we're looking at a cpp file
         if( 8 == ( int )dir_handle->d_type && ext == ".cpp" )
         {
            //finish constructing the path
            path += ( "/" + name );
            return path;
         }
      }while( ( dir_handle = readdir( a_file ) ) != NULL );
   }   
}

#endif
