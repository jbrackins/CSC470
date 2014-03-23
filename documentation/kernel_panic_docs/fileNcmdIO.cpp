#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include <vector>

using namespace std;


/**************************************************************************//**
 * @author Benjamin Sherman
 *
 * @par Description: This function searches through the sourcecode specified
 * from the commandline arguments for key txt "ofstream" and "ifstream". If
 * at least one of each is found the function returns true to indicate that
 * the source code to be graded uses file IO.
 *
 * @returns true - source code from commandline argument uses fiel IO.
 * @returns false - source code from commandline argument uses keyboard input.
 *****************************************************************************/
bool searchFoutFin(ifstream &fin)
{
    string line;
    char read[200];
    int outCount = 0;
    int inCount = 0;
    fin.getline(read, 200, '\n');
    while(!fin.eof())
    {
        line = read;
        if(line.find("ofstream", 0) != string::npos)
            outCount += 1;
        if(line.find("ifstream", 0) != string::npos)
            inCount += 1;

        fin.getline(read, 200, '\n');

    }
    cout << "ofstream count: " << outCount << endl;
    cout << "ifstream count: " << inCount << endl;
    if(outCount > 0 && inCount > 0)
        return true;
    return false;
}



/**************************************************************************//**
 * @author Benjamin Sherman
 *
 * @par Description: This is the main function. It calls the function that
 * recursively traverses the user
 * specified directory.
 *
 * @returns errorCount - number of output solutions from the commandline
 * specified source code that do not match the provided solutions from
 * the corresponding ".ans" files.
 *****************************************************************************/
int testOutput(string solution)
{
    vector<string> output, answers;
    ifstream fin, tst;
    fin.open("output.txt");
    fin.open(solution.c_str());
    char outRead[512], tstRead[512];
    string outLine, tstLine;
    int errorCount = 0;

    if(!fin || !tst)
        return 0;
    fin.getline(outRead,512, '\n');
    tst.getline(tstRead, 512, '\n');
    bool evenLineRead = true;
    while(!fin.eof())
    {
        outLine = outRead;
        tstLine = tstRead;
        if(evenLineRead)
        {
            if(outLine != tstLine)
                errorCount += 1;
        }
        fin.getline(outRead, 512, '\n');
        tst.getline( tstRead, 512, '\n');

    }
    return errorCount;
}



/**************************************************************************//**
 * @author Benjamin Sherman
 *
 * @par Description: This function tests a students program with fileIO.
 *****************************************************************************/
void fileIO(string source, vector<string> ans, vector<string> tst)
{
    string baseStr = "g++ -o source ";
    string cmd;
    for(int i = 0; i < (int)tst.size(); i++)
    {
        cmd = "cp" + tst[i] + " infile.txt";

        cmd = baseStr + source;
        system(cmd.c_str());
        cmd = "./" + source;
        system(cmd.c_str());
        testOutput(ans[i]);

    }
}
/**************************************************************************//**
 * @author Benjamin Sherman
 *
 * @par Description: This will handle source codes that uses commandline
 * input and output.
 *****************************************************************************/
void cmdLineIO()
{

}


/**************************************************************************//**
 * @author Benjamin Sherman
 *
 * @par Description: This is the main function. It checks that the commandline
 * arguments are correct and opens the source code file.
 * @returns 0 Program successfully executed.
 *****************************************************************************/
int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        cout << "Usage: grade <sourceCode.cpp>" << endl;
        //return -1;
    }
    //string sourceCode = argv[1];
    ifstream fin;
    fin.open(argv[1]);
    if(!fin)
        return -2;
    if(searchFoutFin(fin))
        cout << "This source code uses file IO" << endl;
    else cout << "This source code uses keyboard IO" << endl;
    return 0;
}
