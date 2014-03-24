/**************************************************************************//**
* @file test_dir.h
*
* @brief This file contains the necessary code to generate random test and 
* answer cases. It will generate a user-specified amount of files, and numbers.
* these numbers will be either ints or floats. This is also specified by the
* user. Once the test cases are created, a function will compile the provided 
* .cpp file that is assumed to be correct, and use it to make all of the .ans
* files that correspond to the test cases.
*
* @author Jonathan Dixon
******************************************************************************/
#ifndef __TEST_GEN_H_INCLUDED__
#define __TEST_GEN_H_INCLUDED__

#include "header.h"
/****************************************************
 *
 *              test_gen.h
 *
 *    The purpose of this file is to see if the
 *  user would like to generate test cases, and
 *  actually generate said test cases.
 *
 ***************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;


void make_ans( int filesToGen );
string find_goldencpp( );

/**************************************************************************//**
* @author Jonathan Dixon
*
* @par Description:
* This function will get the user's input to see how many
* files they would like to generate, what type of numbers they
* want in the file, and how many numbers they would like in 
* the generated files. It also does error checking on the user
* input.
******************************************************************************/
void genTstCases()
{
   bool validnumToGen = false, validfilesToGen = false;
   char likeToGen;
   char typeToGen;
   int numToGen;
   int filesToGen;
   
   //seed random number generator
   srand(time(0));
   
   //kind of a pretty looking menu
   cout << "::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
   cout << ":         TEST CASE GENERATION PHASE           :" << endl;
   cout << "::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
   
   //get user input
   cout << "Would you like to generate test cases? (y/n): ";
   cin >> likeToGen;
   
   //clear anything after the initial character
   cin.clear();
   cin.ignore( 500, '\n' );
   
   
   likeToGen = tolower( likeToGen );
   
   //check for validity
   while( likeToGen != 'y' && likeToGen != 'n' )
   {
      cout << "*** Please enter a valid response. (y/n): ";
      cin >> likeToGen;
   }

   if( likeToGen == 'n' )
      return;   
         
   //find out if they want ints or floats   
   cout << "Would you like to generate ints or floats? (i/f): ";
   cin >> typeToGen;
   
   //clear after the first letter
   cin.clear();
   cin.ignore( 500, '\n' );
   
   typeToGen = tolower( typeToGen );
   
   //check for validity
   while( typeToGen != 'i' && typeToGen != 'f' )
   {
      cout << "*** Please enter a valid response. (i/f): " << endl;
      cin >> typeToGen;
   }

   //get how many files should be generated     
   while( !validfilesToGen )
   {
      cout << "How many files would you like to generate? (1-100): ";
      cin >> filesToGen;
      
      //make sure they enter an int
      while( cin.fail() )
      {
         //if a char was entered, this clears input, gets a new one
         cin.clear();
         cin.ignore( 500, '\n' );
         cout << "*** Enter a number, please (1-100): ";
         cin >> filesToGen;
      }
      
      //check for a valid number of files
      if( filesToGen > 100 || filesToGen < 1 )
      {
         cout << "*** Please enter a valid number of files. (1-100)" << endl;
      }
      else
         validfilesToGen = true;
   }
      
   //get how many numbers to generate
   while( !validnumToGen )
   {
      cout << "How many numbers would you like to generate? (0-200): ";
      cin >> numToGen;
      
      //make sure they enter an int
      while( cin.fail() )
      {
         //if a char was entered, clear input, get new input
         cin.clear();
         cin.ignore( 500, '\n' );
         cout << "*** Enter a number, please (1-200): ";
         cin >> numToGen;
      }

      //make sure number is in the correct range
      if( numToGen > 200 || numToGen < 1 )
      {
         cout << "*** Please enter a valid number. (1-200)" << endl;
      }
      else
         validnumToGen = true;
   }
   
   //now, it is important to create these files in the 'tests' subdirectory
   //if the directory is successfully created, move into it
   if( !system("mkdir tests &>/dev/null") )
   {
      cout << "\"tests\" directory created!" << endl;
      chdir( "tests" );
   }   
   //if the directory already exists, move into it, and clear the old test cases
   else
   {
      cout << "\"tests\" directory exists!" << endl;
      chdir( "tests" );
      system( "rm -f *" );
   }   
   
   //loop once for each file to be made
   for( int i = 1; i <= filesToGen; i++ )
   {
      stringstream temp;
      ofstream fout;
      
      //assemble the filename
      temp << "test" << i << ".tst";
      
      //open the file
      fout.open(temp.str().c_str());
      
      //generate all of the random numbers
      for( int j = 0; j < numToGen; j++ )
      {
         if( typeToGen == 'f' )
            fout << ((float)rand()/(float)(RAND_MAX)) * 2000 << endl;
         else
            fout << rand() % 2000 << endl;
      }
      
      //close file output
      fout.close();
   }
   
   cout << "::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
   cout << ":       TEST CASE GENERATION SUCCESSFUL        :" << endl;
   cout << "::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
   
   //move back to the parent directory
   chdir( ".." );
   
   //make all of the answers to the test cases
   make_ans( filesToGen );
}


/**************************************************************************//**
* @author Jonathan Dixon
*
* @par Description:
* This function will compile the correct cpp file provided within the test 
* suite, and run it against all of the newly generated test cases to create
* some useful .ans files that other programs may be graded against.
*
* @param[in] filesToGen - number of .tst files that have been generated
******************************************************************************/
void make_ans( int filesToGen )
{
   char buffer[PATH_MAX];
   DIR *a_file;
   struct dirent *dir_handle;
   string ext;
   string path;
   string name;
   string command;
   
   //get cwd into a character buffer
   getcwd( buffer, sizeof(buffer) );
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
         if( name.find_last_of(".") != string::npos && name != "test.cpp" )
            ext = name.substr( name.find_last_of(".") );
         else
            ext = "";
         
         //make sure we're looking at a cpp file
         if( 8 == (int)dir_handle->d_type && ext == ".cpp" )
         {
            //finish constructing the path
            path += ( "/" + name );

            //assemble the command to compile the .cpp
            command = "g++ ";
            command += path;
            command += " -o key";
            system( command.c_str() );
         }
      }while( ( dir_handle = readdir( a_file ) ) != NULL );
   }
   
   //for each file we have generated
   for( int i = 1; i <= filesToGen; i++ )
   {
      //run the correct program, piping from the input file to a .ans file
      stringstream runcommand;
      runcommand << "./key < tests/test" << i << ".tst > tests/test" << i << ".ans";
      
      system( runcommand.str().c_str() );
   }
   system("rm -f key");
   
}
#endif
