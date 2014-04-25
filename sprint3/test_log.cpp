#include "test_log.hpp"
#include "main.hpp"
using namespace std;

/*********************************GLOBALS************************************/
extern vector<string> STUDENTVECTOR;
extern vector<report> INDIVIDUALREPORTS;
extern vector<string> TESTCASES;
extern string GOLDCPP;
extern int TOTALPASSED;
/****************************************************************************/



/************************Generate_Performance_Report***************************/
// QQQ!!! Alex: built to write in the specifics of success and failures per cpp
/******************************************************************************/
string Generate_Performance_Report(string file, int score, int total)
{
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

    
  return report + ":  " + temp.str();
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

void writeindividualreport(string program, string testcase, int success, int curr)
{
  string temp;
  string file = program + ".log";
  //ofstream fout(file.c_str(), fstream ::app); // append
  if (success == 1) // if passed
  {
    temp = "passed: " + testcase;
    INDIVIDUALREPORTS[curr].reports.push_back(temp);
    //fout << "passed: " << testcase << endl;
  }

  else if (success == -1 || success == 0)
  {
    temp = "failed: " + testcase;
    INDIVIDUALREPORTS[curr].reports.push_back(temp);
    //fout << "failed: " << testcase << endl;
  }
  else if (success == -999)
  {
    temp = "infinite loop: " + testcase;
    INDIVIDUALREPORTS[curr].reports.push_back(temp);
    //fout << "infinite loop: " << testcase << endl;
  }
  //fout.close();
}

/*****************************createReports***********************************/
// Jon: Writes the .log file for a specific student
/*****************************************************************************/
void createReports()
{
   string tempout, tempin, temp;
   string linein;
   string path;
   ofstream fout;
   ifstream fin;
   int lastDir;

   for( int i = 0; i < INDIVIDUALREPORTS.size(); i++ )
   {
      path = INDIVIDUALREPORTS[i].filename.substr(0, INDIVIDUALREPORTS[i].filename.rfind("/"));
     
      lastDir =  path.rfind("/");
      path = path.substr(lastDir + 1);
      
      chdir(path.c_str());
      
      temp = INDIVIDUALREPORTS[i].filename;
      lastDir = temp.rfind("/");
      temp = temp.substr(lastDir + 1);
      
      tempout = temp + ".log";
      fout.open(tempout.c_str());
      
      if(fout)
      {
         for( int j = 0; j < INDIVIDUALREPORTS[i].reports.size(); j++ )
            fout << INDIVIDUALREPORTS[i].reports[j] << endl;
            
         tempin = temp + ".covs";
         fin.open(tempin.c_str());
         
         if( fin )
         {
            getline( fin, linein );
            getline( fin, linein );
            
            fout << linein << endl;
         }
         else
            cout << "Could not open .covs file." << endl;
      }
      else
      {
         char temp[500];
         cout << "Could not create .log file: " << temp << endl;
      }
      
      path = "..";
      chdir(path.c_str());
      
      fout.close();
      fin.close();
   }
}
