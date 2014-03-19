#include <iostream>
#include <stdlib.h>
#include <cstring>

using namespace std;


int main (int argc, char* argv[])
  {
  char command[80];
  char append_str[] = "g++ "; //g++ compiler call

  strcpy (command, argv[argc-1]); //get file to execute from the command line
  strcat(append_str,command); //append to compiler call 

  system(append_str); // call g++ pogramname
  system("./a.out"); // execute program 


  return 0;
  }
