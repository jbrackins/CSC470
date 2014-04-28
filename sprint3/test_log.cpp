/**************************************************************************//**
* @file test_log.cpp
*
* @brief 
*
* @authors Jonathan Dixon, Julian Brackins, Hafiza Farzami, Alex Wulff
******************************************************************************/

#include "test_log.hpp"
#include "main.hpp"
#include "test_string.hpp"
using namespace std;

/*********************************GLOBALS************************************/
extern vector<string> STUDENTVECTOR;
extern vector<report> INDIVIDUALREPORTS;
extern vector<string> TESTCASES;
extern int TOTALPASSED;
/****************************************************************************/

/**************************************************************************//**
 * @authors Alex Wulff, Jonathan Dixon, Julian Brackins
 *
 * @par Description: The following function generates performance report for
 * individual students.
 *
 * @param[in] file - the file
 * @param[in] score - the student's score
 * @param[in] total - total possible score
 *
 * @returns report - the result
 *
 *****************************************************************************/
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

 /**************************************************************************//**
 * @author Alex Wulff
 *
 * @par Description: Writes all of the data to the final .log file.
 *
 *****************************************************************************/  
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
  //string outfilename (buffer); //QQQ!!! Alex : just log and time //+ logprogname+"_"+buffer+".log";
  
  string outfilename = log_filename("Summary.file");

  //opening final output file
  ofstream fout;
  fout.open(outfilename.c_str());

  fout << "Test Summary:\nDate: " << timestamp() << endl;

  
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


 /**************************************************************************//**
 * @author Alex Wulff
 *
 * @par Description: This functions takes care of the individual file reports.
 *
 *****************************************************************************/
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

 /**************************************************************************//**
 * @authors Alex Wulff, Jonathan Dixon, Hafiza Farzami
 *
 * @par Description: This function creates individual log files. It also outputs
 * the result from code coverage and profiling into the student log file. 
 *
 * @param[in] none 
 *
 * @returns none - void function
 *
 *****************************************************************************/
void createReports()
{
   string tempout, tempin, temp;
   string linein;
   string path;
   ofstream fout;
   ifstream fin;
   ifstream gfin;
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
      
      //tempout = temp + ".log";
      tempout = log_filename( temp );
      fout.open(tempout.c_str());
      
      if(fout)
      {
         for( int j = 0; j < INDIVIDUALREPORTS[i].reports.size(); j++ )
            fout << INDIVIDUALREPORTS[i].reports[j] << endl;
            
         tempin = temp + ".covs";

         fin.open(tempin.c_str());
         //cout << "attempting to open " << tempin << " file " << endl;
         if( fin )
         {
            getline( fin, linein );
            getline( fin, linein );
            
            fout << linein << endl;
         }
	fin.close();
	fout << endl;
         //else
          //cout << "Could not open .covs file." << endl;
	 temp = temp.substr(0,temp.find("."));
	 tempin = temp + ".gprof.txt";
	
	gfin.open( tempin.c_str() );
	if( gfin )
	{
 		while( getline( gfin, linein ) )
			fout << linein << endl;
	}

      }
      else
      {
         char temp[500];
         //cout << "Could not create .log file: " << temp << endl;
      }
      
      path = "..";
      chdir(path.c_str());
      
      gfin.close();
      fout.close();
      fin.close();
   }
}
