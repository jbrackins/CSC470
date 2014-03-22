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

int run_file(string cpp_file, string test_case);
int result_compare(string test_file);

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
 * A command is sent to the system to delete the cpp file's executable.
 *
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
 * @authors Julian Brackins, Benjamin Sherman, Anthony Morast, James Tillma
 *
 * @par Description: This function is the compilation of some of the code
 * James and Anthony pushed to github on 2/9/14. It uses popen to process
 * all the system commands so that we can get the system command output
 * and ignore the system command output in the terminal.
 * SPRINT 2 UPDATE:
 * Julian Brackins: I've modified this solution algorithm heavily, changing
 * Kernel Panic's system of appending the log files to one big file to instead
 * log individual files.
 *
 * New Solution Algorithm: 
 * >For Loop based on all .cpp files in directory:
 *     >Create Log File for current student
 *     >For Loop based on elements in tst file vector:
 *         >Run File using current .tst file
 *         >If File Passed:
 *             >Indicate that student passed test case
 *             >Increment Number of Successes
 *         >If File Failed:
 *             >If .tst file was a critical test                      <NOT IMPLEMENTED YET
 *                 >Indicate Critical Failure                         <NOT IMPLEMENTED YET
 *             >Indicate that student failed test case
 *     >Output Summary of Student's results to their log file
 *     >Output Student's name and score to Summary File               <NOT IMPLEMENTED YET
 *
 *
 *****************************************************************************/
void gradeSolution(vector<string> tst, char arg[100])
{
    //string source = "";
    //string cp;

    int total, test_cases_total;
    string tab = "\t";
    string passStr = "\t\npass ";
    string failStr = "\t\nfail ";
    string input, result, sol, caseName, cppFile, clear;
    string logFileContents = "";
    string logStr = ".log";
    string cppStr = ".cpp";

    char buffer[20] = "";
    ofstream logFile[256];
    int pass = 0, fail = 0;

    int pass_fail = 0;
    /*Data type for critical failure maybe?*/
    int crit_fail = 0;

    for(int i = 0; i < (int)cppLocations.size(); i++)
    {
        total = 0;
        test_cases_total = 0;
        string log_name(log_filename(remove_extension(cppLocations[i])));
        logFile[i].open(log_name.c_str());
        for(int j = 0; j < (int)tst.size(); j++)
        {


            /*Check to see if cpp file passed the current
              test in the list. If successful, tally the
              success.*/
            pass_fail = run_file(cppLocations[i], tst[j]);

            logFile[i] << tst[j] << ": ";
            if(pass_fail == 1)
            {
                total += 1;
                logFile[i] << "PASSED\n";
            }
            else
            {
                /*CHECK IF tst[i] IS A CRIT TEST
                  if It is, then set crit_fail to 1*/
                logFile[i] << "FAILED\n";
            }
            test_cases_total++;

        }     
   
    //output grade to log file
    logFile[i] << "\n" << total << "/" << test_cases_total << " test cases passed\n";
    double grade = grade_percent(total, test_cases_total);
    logFile[i] << "percentage: " << grade << "%\n";
    logFile[i] << "     grade: " << grade_letter(grade) << "\n";


    }



}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Using C++ String manipulation, a command is sent to the terminal in 
 * order to run the file brought in by the argument cpp_file
 * String buffers are used to handle piping both for inputting
 * An integer value is returned from this function.
 * A 0 indicates the program failed the test case.
 * A 1 indicates the program has identical results to the test case.
 *
 * The run line sent to system() is as follows
 * run_file(example, case_x.tst);
 * <full_path>/./example < case_x.tst > case_x.out 
 *
 * @param[in] cpp_file - name of program file to be run
 * @param[in] test_case - string with test case file name
 *
 * @returns result_compare(test_case) - 0 if test fails, 1 if test succeeds
 *
 *****************************************************************************/
int run_file(string cpp_file, string test_case) //case_num
{
    //create .out file name
    string case_out(case_name(test_case, "out"));

    //set up piping buffers
    string buffer1("");
    string buffer2(" &>/dev/null < ");
    string buffer3(" > ");

    // "try using | "
    //construct run command, then send to system
    //./<filename> &> /dev/null  < case_x.tst > case_x.out
    buffer1 += remove_extension(cpp_file);
    buffer1 += buffer2;
    buffer1 += test_case;
    buffer1 += buffer3;
    buffer1 += case_out;
    //cout << "BUFFER1: " << buffer1 << endl;
    system(buffer1.c_str());

    //0 = Fail, 1 = Pass
    return result_compare(test_case);
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * The result_compare() function is designed to determine whether or not the
 * program passes or fails a test case. in the run_file() command, the results
 * of the test are piped into a .out file with the same name as the .tst file
 * used for testing input. A file with the same name but a .ans extension will
 * contain the expected result from the given test case.
 * By this logic, a successful test case run will result in a .out file that is
 * identical to the .ans file. This function runs the diff command on the two
 * files to determine if the files are identical. If the two files match, the
 * program passed the test case, and a 1 is returned. If the files do not match,
 * a 0 is returned.
 * The results of the diff command are actually piped into a .tmp file. This
 * temporary file will be empty if the files are identical, and will contain
 * the differences between the two files if they are not identical. The file
 * is opened to determine if it has any contents, and if not, the .out and .ans
 * files can be confirmed to be identical.
 *
 * @param[in] test_file - test file name
 *
 * @returns 1 - Empty .tmp file, test passed.
 * @returns 0 - diff command yielded results, test failed.
 *
 *****************************************************************************/
int result_compare(string test_file)
{
    int length;
    ifstream fin;

    string case_out(case_name(test_file, "out"));
    string case_ans(case_name(test_file, "ans"));
    string case_tmp(case_name(test_file, "tmp"));   //create temp file
    
    //perform diff command
    string buffer("diff ");
    buffer += case_out + " " + case_ans + " > " + case_tmp;
    system(buffer.c_str());    
    
    fin.open(case_tmp.c_str(), ios::binary);    //open file
    fin.seekg(0, ios::end);                     //cursor at EOF
    length = fin.tellg();                       //find cursor position
    fin.close();

    //remove tmp file
    buffer = "rm " + case_tmp;
    system(buffer.c_str());



    if ( length == 0 ) //File is empty, no diff between .ans and .tmp
        return 1;
    else
        return 0;
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
    string temp = "diff " + solution + " " + case_name(solution, "out");
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
