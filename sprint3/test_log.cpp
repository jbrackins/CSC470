

#include "test_log.hpp"
using namespace std;

/*********************************GLOBALS************************************/
extern vector<string> STUDENTVECTOR;
extern vector<string> TESTCASES;
extern string GOLDCPP;
extern int TOTALPASSED;
/****************************************************************************/



/************************Generate_Performance_Report***************************/
// QQQ!!! Alex: built to write in the specifics of success and failures per cpp
/******************************************************************************/
string Generate_Performance_Report(string file, int score, int total)
{
  fstream fin;
  string tempstr;
  int lastDir = file.rfind("/");
  string report = file.substr(lastDir + 1);
  if (score == -1)
  {
    return report + ":  FAILED";
  }
  
  stringstream temp("");
  double percent = ((double) score / total) * 100;
  temp << percent;
  
  tempstr = report + ".covs";
  fin.open( tempstr.c_str() );
  if( fin )
  {
    getline( fin, tempstr );
    getline( fin, tempstr );
  }
  else
    cout << "cannot open .covs file" << endl;
    
  fin.close();
  return report + ":  " + temp.str() + "%\n\t" + tempstr;
}

/***************************** writefinaloutfile ******************************/
// Writes all of the data to the final .log file
/******************************************************************************/   
void writefinaloutfile(vector<string> finaloutfilecontents)//QQQ!!! Alex : commented out new processing method
//                               string progname, vector<string> finaloutfilecontents)
{  
  //getting current date and time for filename
  time_t rawtime;
  struct tm * timeinfo;
  char buffer [16];
  time (&rawtime);
  timeinfo = localtime (&rawtime);
  strftime (buffer,16,"%m_%d_%H:%M:%S",timeinfo);
  //string to hold the final output file name
  string outfilename (buffer); //QQQ!!! Alex : just log and time //+ logprogname+"_"+buffer+".log";
  
  outfilename = "log " + outfilename;

  //opening final output file
  ofstream fout;
  fout.open(outfilename.c_str());

  fout << "\nTest Summary:\n\n";

  
  //writing the contents to the output file
  for(int i=0;i<finaloutfilecontents.size();i++)
  {      
    fout << finaloutfilecontents.at(i) << endl;
  }
  
  //printing out the final summary of the tests to the output file
  fout <<  
  "     Total # of tests ran:    " << 
  TESTCASES.size()*STUDENTVECTOR.size() << 
  "\n     Total # of tests passed: " << TOTALPASSED <<
  "\n              Percent passed: " << 
  (((float)TOTALPASSED)/(TESTCASES.size()*STUDENTVECTOR.size())) * 100 << 
  "%" << endl;
  
  
  //closing the output file
  fout.close();
}
/*************************** END writefinaloutfile ****************************/

/******************************writeindividualreport*************************/
// QQQ!!! Alex : writes the specifics of each program's performance with a 
// given test
/****************************************************************************/

void writeindividualreport(string program, string testcase, int success)
{
  string file = program + ".log";
  ofstream fout(file.c_str(), fstream ::app); // append
  if (success > 0) // if passed
  {
    fout << "passed: " << testcase << endl;
  }
  else
  {
    fout << "failed: " << testcase << endl;
  }
  fout.close();
}
