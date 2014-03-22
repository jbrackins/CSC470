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

using namespace std;


void genTstCases()
{
   bool validnumToGen = false, validfilesToGen = false;
   char likeToGen;
   char typeToGen;
   int numToGen;
   int filesToGen;
   
   while( likeToGen != 'y' && likeToGen != 'n' )
   {
      cout << "Would you like to generate test cases? (y/n): ";
      cin >> likeToGen;
      
      cin.clear();
      cin.ignore( 500, '\n' );
      
      
      likeToGen = tolower( likeToGen );
      
      if( likeToGen != 'y' && likeToGen != 'n' )
      {
         cout << "Please enter a valid response. (y/n)" << endl;
      }
   }

   if( likeToGen == 'n' )
      return;   
   cout << "Valid response received!" << endl;
   
   while( !validfilesToGen )
   {
      cout << "How many files would you like to generate? (1-100): ";
      cin >> filesToGen;
      
      while( cin.fail() )
      {
         cin.clear();
         cin.ignore( 500, '\n' );
         cout << "Enter a number, please (1-100): ";
         cin >> filesToGen;
      }
      
      if( filesToGen > 100 || filesToGen < 1 )
      {
         cout << "Please enter a valid number of files. (1-100)" << endl;
      }
      else
         validfilesToGen = true;
   }
   
   cout << "Valid number of files received: " << filesToGen << endl;
   
   while( !validnumToGen )
   {
      cout << "How many numbers would you like to generate? (0-200): ";
      cin >> numToGen;
      
      while( cin.fail() )
      {
         cin.clear();
         cin.ignore( 500, '\n' );
         cout << "Enter a number, please (1-200): ";
         cin >> numToGen;
      }

      
      if( numToGen > 200 || numToGen < 1 )
      {
         cout << "Please enter a valid number. (1-200)" << endl;
      }
      else
         validnumToGen = true;
   }
   
   cout << "Valid Number received: " << numToGen << endl;
   
   while( typeToGen != 'i' && typeToGen != 'f' )
   {
      cout << "Would you like to generate ints or floats? (i/f): ";
      cin >> typeToGen;
      
      cin.clear();
      cin.ignore( 500, '\n' );
      
      
      typeToGen = tolower( typeToGen );
      
      if( typeToGen != 'i' && typeToGen != 'f' )
      {
         cout << "Please enter a valid response. (i/f)" << endl;
      }
   }  
   
   for( int i = 1; i <= filesToGen; i++ )
   {
      stringstream temp;
      ofstream fout;
      
      temp << "test" << i << ".tst";
      
      fout.open(temp.str().c_str());
      
      for( int j = 0; j < numToGen; j++ )
      {
         if( typeToGen == 'f' )
            fout << ((float)rand()/(float)(RAND_MAX)) * 2000 << endl;
         else
            fout << rand() % 2000 << endl;
      }
      
      fout.close();
   }
}
#endif
