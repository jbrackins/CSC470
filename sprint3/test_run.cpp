
#include "test_run.hpp"
using namespace std;

/*********************************GLOBALS************************************/
extern vector<string> STUDENTVECTOR;
extern vector<string> TESTCASES;
extern string GOLDCPP;
extern int TOTALPASSED;
/****************************************************************************/

/********************************** runtests **********************************/
// Runs all of the .tst test cases against the program one at a time
//  and returns the results of that particlar test, stored in a string

// QQQ!!! Alex : modified here to compile and execute each test with each 
// specified test case as part of the "foreach" loop in main.
/******************************************************************************/
//string runtests(string progname, string specifictestcase)
int runtests(string prog, string specifictestcase)
{ 
  string testresult;
  
  // compile each
  string prog_cpp = prog;
  string progname = prog_cpp.substr(0,prog_cpp.find("."));
  string progcomp = "g++ -fprofile-arcs -ftest-coverage -o " + progname  + " " + prog_cpp;
  size_t found = prog_cpp.find_last_of("/\\");

  // QQQ!!! Alex : to save time, only compile if needed.
  ifstream fileExists(progname.c_str());
  if (!fileExists)
  {
    fileExists.close();
    //compile program to be tested
    system(progcomp.c_str());
  }
  else
  {
    fileExists.close();
  }
  //temporary file used to compare results
  string tempfile = "temp.txt";

  string answerFile = specifictestcase.substr(0,specifictestcase.rfind(".tst"));
  answerFile += ".ans";
  // QQQ!!! Alex : verify there is an answer file
  fileExists.open(answerFile.c_str());
  if (!fileExists)
  {
    fileExists.close();
    // Per customer conversation, don't fail a test with no answer
    return 0;
  }
  fileExists.close();
  /*building the string to run the program, adds the appropriate .tst file for
   input to the program and the temp#.txt file as the output of the program 
   being tested*/
  string progrun = progname+" < "+specifictestcase+" > "+tempfile;
  
  //running the program
  system(progrun.c_str());
  
  string nodir = progname;
  
  nodir.erase(0, nodir.find_last_of("/") + 1);
  string gcovrun = "gcov " + nodir + ".gcno" + " > " + nodir + ".cpp.covs";
  system(gcovrun.c_str());
  
  //gcovrun = "rm " + nodir + ".cpp.gcov " + nodir + ".gcda " + nodir + ".gcno -f";
  //system(gcovrun.c_str());
  
  //building string for the .ans file name to compare against
  string testcaseans = specifictestcase;
  testcaseans.replace(testcaseans.end()-4, testcaseans.end(),".ans"); 
    
  //comparing answer to the correct answer and storing the results
  int nodifference = filesequal(testcaseans, tempfile);
  if(nodifference == 0)
  {
    // QQQ!!! Alex : changing... testresult = "Result: pass    Case: " + specifictestcase; 
    return 1;
  }
  else if(nodifference ==1)
  {
    // QQQ!!! Alex : changing... testresult = "Result: fail    Case: " + specifictestcase;
    return 0;
  }
  else
  {
    // QQQ!!! Alex : changing... testresult = "files did not open for comparison";
    return -1;
  }
      
  // QQQ!!! Alex : changing... return testresult;
}
/******************************* END runtests *********************************/

/********************************* filesequal *********************************/
// compares two files and returns 1 if not equal, 0 if equal

// QQQ!!! Alex : this was causing huge performance hits. Reworked to a dif check
/******************************************************************************/ 
int filesequal(string file1name, string file2name)  // QQQ!!! Alex: used as boolean,
// so change return type or make clear that return is 0 for false (based on name)
{
  ifstream file1, file2;

  //opening the two files to compare and ensuring they open properly
  file1.open( file1name.c_str(), ios::in ); // QQQ!!! Alex: doesn't infile usualy
  file2.open( file2name.c_str(), ios::in ); // defualt to in ios?
  if (!file1)
  {
    cout << "Couldn't open the file  " << file1name <<endl;
    file2.close();
    return 2;
  }
  if (!file2){
    file1.close();
    cout << "Couldn't open the file " << file2name << endl;
    return 2;
  }
    
  //read the two files into two string vectors
  vector<string> string1, string2;
  int i = 0;
  while(file1.good())  // QQQ!!! Alex : change this to diff? or leave at io heavy?
  {
    string1.push_back("");
    getline(file1,string1.at(i)); 
    i++;
  }
  i = 0;
  while(file2.good())
  {
    string2.push_back("");
    getline(file2,string2.at(i)); 
    i++;
  }

  //close the two files being compared
  file1.close();
  file2.close();
    
  //first testing if the files had same amount of lines
  if(string1.size() == string2.size())
  {
    //if both had same amount of lines, test actual contents of each line
    for(int i=0;i<string1.size();i++)
    {
      //removing the VERY frustrating occasional \r in the string
      string1.at(i) = string1.at(i).substr(0,string1.at(i).find("\r"));
      string2.at(i) = string2.at(i).substr(0,string2.at(i).find("\r"));
 
      //compare the contents of the two lines.  if equal, return 0, else 1
      if(strcmp(string1.at(i).c_str(),string2.at(i).c_str()) == 0)
      {
        //move on to next string comparison
      }
      else 
      {
        return 1;
      }
    }
    return 0;
  }
  else
  {
    return 1; //files had different amount of lines, thus not equal
  }
}
/******************************* END filesequal *******************************/


/***********************************cleanup**********************************/
// QQQ!!! Alex : cleans up the globals
/****************************************************************************/
void cleanup()
{
  // remove temp files
  char buffer[1024];
  getcwd(buffer,sizeof(buffer));
  string location (buffer);
  string remove;
  
  location =  "rm " + location + "/temp.txt";
  system(location.c_str());
  
  for( int i = 0; i < STUDENTVECTOR.size(); i++ )
  {
      remove = "rm " + remove_extension( STUDENTVECTOR[i] ) + " -f";
      system( remove.c_str() );
  }
  STUDENTVECTOR.erase(STUDENTVECTOR.begin(), STUDENTVECTOR.end());
  TESTCASES.erase(TESTCASES.begin(), TESTCASES.end());  
  
  system( "rm *.gcno *.gcov *.gcda *.covs -f" );
}


