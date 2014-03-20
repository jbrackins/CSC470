#ifndef __TEST_H_INCLUDED__
#define __TEST_H_INCLUDED__


#include "header.h"
#include "test_crit.h"
#include "test_dir.h"
#include "test_gen.h"
#include "test_string.h"



///////////////////////////////////////////////////////////////////////////////
////                       FUNCTION PROTOTYPES
///////////////////////////////////////////////////////////////////////////////

int compile_file(string cpp_file);
int delete_file(string cpp_file);
bool testOutput(string solution);
void gradeSolution(vector<string> tst, char arg[]);


/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Using C++ String manipulation, a g++ compile command is sent to the
 * terminal in order to compile the file brought in by the argument
 * cpp_file.
 *
 * The compile line is as follows
 * compile_file(example.cpp);
 * "g++ -o example example.cpp"
 *
 * @param[in] cpp_file - name of .cpp file to be compiled by program
 *
 * @returns system(buffer.c_str()) - 0 if compile worked, 1024 if failed
 *
 *****************************************************************************/
int compile_file(string cpp_file)
{
    string buffer("g++ -o");
    buffer += " " + remove_extension(cpp_file) + " " + cpp_file;
    return system(buffer.c_str());
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Using C++ String manipulation, a g++ compile command is sent to the
 * terminal in order to compile the file brought in by the argument
 * cpp_file.
 *
 * The compile line is as follows
 * compile_file(example.cpp);
 * "g++ -o example example.cpp"
 *
 * @param[in] cpp_file - name of .cpp file to be compiled by program
 *
 * @returns system(buffer.c_str()) - 0 if compile worked, 1024 if failed
 *
 *****************************************************************************/
int delete_file(string cpp_file)
{
    string buffer("rm -f");
    buffer += " " + remove_extension(cpp_file);
    return system(buffer.c_str());
}

/**************************************************************************//**
 * @authors Benjamin Sherman, Anthony Morast, James Tillma
 *
 * @par Description: This function is the compilation of some of the code
 * James and Anthony pushed to github on 2/9/14. It uses popen to process
 * all the system commands so that we can get the system command output
 * and ignore the system command output in the terminal.
 *****************************************************************************/
void gradeSolution(vector<string> tst, char arg[100])
{
    string source = "";
    string cp;

    string tab = "\t";
    string passStr = "\t\npass ";
    string failStr = "\t\nfail ";
    string input, result, sol, caseName, cppFile;
    string logFileContents = "";
    string logStr = ".log";
    string cppStr = ".cpp";

    char buffer[20] = "";
    ofstream logFile;
    int pass = 0, fail = 0;
    char append_str[] = "g++ "; //g++ compiler call
    // get file to execute from the command line
    source = arg;
    //source = source.substr(source.find_last_of('/') + 1);
    //source = source.substr(0,source.find_last_of('.') + 1);
    source += logStr;

    logFile.open(source.c_str(), ios_base::app);
    cppFile = arg;
    cppFile += cppStr;
    //cppFile = cppFile.substr(cppFile.find_last_of('/') + 1);
    strcat(append_str, cppFile.c_str()); //append to compiler call

    if(!logFile) return;
    for(int i = 0; i < (int)tst.size(); i++)
    {
        cp = "cp " + tst[i] + " infile.txt";

        FILE *f = popen(cp.c_str(), "r");
        f = popen(append_str, "r"); // call g++ pogramname
        pclose(f);

        // execute program
        f = popen("./a.out  < infile.txt > outfile.txt 2> /dev/null", "r"); 
        pclose(f);
        input = getFileStream(tst[i]);
        result  =  getFileStream("outfile.txt");
        sol =  getFileStream(ansLocations[i]);

        caseName = tst[i].substr(tst[i].find_last_of('/') + 1);
        caseName = caseName.substr(0, caseName.find_last_of('.'));

	string temp = getDateTime();

        if(testOutput(ansLocations[i]))
        {
            logFileContents += tab + temp + passStr + caseName;
            pass += 1;
        }
        else
        {
            logFileContents += tab + temp + failStr + caseName;
            fail += 1;
        }

        logFileContents += "\n\t\tInput:" + input + "\n\t\tAnswer:"
            + result + "\n\tSolution:" +  sol + "\n";
    }

    result = "";
    sprintf(buffer, "%d", pass);
    result += buffer;
    result +=  " passed\t";
    sprintf(buffer, "%d", fail);
    result += buffer;
    result += " failed\n";
    sprintf(buffer, "%d", int(100*((double)pass/(double)tst.size())));
    result += buffer;
    result += "% passed \n";
    logFileContents.insert(0, result);
    logFile << logFileContents;
    logFile.close();
}

/**************************************************************************//**
 * @author Benjamin Sherman
 *
 * @par Description: This function calls the diff function, if there is
 * no output from the diff function, the solution is correct and it returns
 * true
 *
 * @returns true - solution is correct
 * @returns false - solution is incorrect
 *****************************************************************************/
bool testOutput(string solution)
{
    string temp = "diff " + solution + " outfile.txt";
    char result[100] = "";
    strcpy(result, "");

    FILE *f    = popen(temp.c_str(), "r");
    fgets(result, 100, f);

    //cout << result << endl;
    pclose(f);
    if(!strcmp(result, "\0"))
        return true;
    return false;
}





#endif
