/**************************************************************************//**
* @file test_run.cpp
*
* @brief 
*
* @authors Julian Brackins, Jonathan Dixon, Hafiza Farzami
******************************************************************************/

#include "test_run.hpp"
#include "test_string.hpp"
#include "test_log.hpp"
#include "test_dir.hpp"
using namespace std;

/*********************************GLOBALS************************************/
extern vector<string> STUDENTVECTOR;
extern vector<string> TESTCASES;
extern string GOLDCPP;
extern int TOTALPASSED;
extern int loop_time;      //time tester will allow a program to run
/****************************************************************************/

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Redirect Implementation. This function handles both redirecting the output
 * of a Unix command to a file, and redirecting the contents of a file as the
 * input of a Unix command. The function identifies whether the redirect is an
 * output (>) or an input (<) to the command and tokenizes the command line. 
 * A child process is forked and redirects the i/o to the appropriate location.
 * This function has been imported from my dsh.c program in Operating Systems.
 * Keeping this in mind, there have been some heavy modifications to this 
 * function so that it accomodates the needs for this sprint 3 testing suite.
 *
 * @param[in] commandline - input line containing command and redirection file
 *
 * @returns 0 - successfully exit program.
 *
 *****************************************************************************/
int Event_REDIRECT(const char *commandline)
{
    int   num_args;
    char *args[100];

    int   num_pbar;
    char *pbar[100];

     
    int   childpid1, childpid2;
    int   status = 0; 

    int fptout, fptin;
    int   wait_pid;

    char  line[512];
    char progname[512];
    
    /*Tokenize command*/
    num_args = 0;
    args[num_args] = strtok((char*)commandline, " <>\n");

    while (args[num_args] != NULL) 
    { 
        num_args++; 
        args[num_args] = strtok(NULL, " <>\n"); 
    }   

    childpid1 = fork();
    if (childpid1 == 0)
    {
        /*Handle input redirection*/
        if ((fptin = open(args[1], O_RDONLY)) == -1)
        {
            printf("Unable to open %s for reading.\n", args[2]);
            exit(-1);
        }
        close(0);       /*supress stdin*/ 
        dup(fptin);      /*redirect input*/ 
        close(fptin);    /*supress file descriptor*/

        /*Handle output redirection*/

        if ((fptout = creat(args[2], 0644)) == -1)
        {
            printf("Unable to open %s for writing.\n", args[1]);
            exit(-1);
        }

        close(1);       /*supress stdout*/
        dup(fptout);   /*redirect output*/
        close(fptout);    /*supress file descriptor*/

        //execvp(args[0],args);
        execl(args[0], args[0], 0);
        perror("Exec failed: "); 
        exit(5); 
    }

    strcpy(progname, args[0]);


    childpid2 = fork();
    if (childpid2 == 0)
    {
        progbar(childpid1, loop_time, progname);
        exit(5);
    }
    //printf("progbar is %d\n",childpid2);

    wait_pid = waitpid(childpid1, NULL, 0);
    printf("\n\n"); //Just space things out a bit
    //printf("\n\n\n\nwait = %d\n",wait_pid);
    pid_t result = waitpid(childpid2, &status, WNOHANG);

    if(result == 0)
    {
        kill(childpid2, 9); //Kill the progress bar wherever it's at
    }
    else if (wait_pid == childpid1)
    {
        printf("%s failed to complete in %d seconds...\n", progname, loop_time); 
        return -999;
    }
    return 1;
}

/********************************** runtests **********************************/
// Runs all of the .tst test cases against the program one at a time
//  and returns the results of that particlar test, stored in a string

// QQQ!!! Alex : modified here to compile and execute each test with each 
// specified test case as part of the "foreach" loop in main.
/******************************************************************************/
//string runtests(string progname, string specifictestcase)
/**************************************************************************//**
 * @authors xxxxxxx
 *
 * @par Description:
 *
 * @param[in] xxx - xxxxxxxx
 *
 * @returns xxx -
 *
 *****************************************************************************/
int runtests(string prog, string specifictestcase)
{ 
    string testresult;

    // compile each
    string prog_cpp = prog;
    string progname = prog_cpp.substr(0,prog_cpp.find("."));
    string progcomp = "g++ -pg -fprofile-arcs -ftest-coverage -o " + progname  + " " + prog_cpp;
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

//    cout << "Compiling: " << progcomp << endl;
//    system( progcomp.c_str() );

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
    //system(progrun.c_str());
    int infinite_loop = Event_REDIRECT(progrun.c_str());

    if(infinite_loop < 0)
    {
        return infinite_loop;
    }
    string nodir = progname;

    nodir.erase(0, nodir.find_last_of("/") + 1);
    string gcovrun = "gcov " + nodir + ".gcno" + " > " + progname + ".covs";
     
    ifstream gmonExists("gmon.sum");
    if( !gmonExists )
    {
        gmonExists.close();
        system("mv gmon.out gmon.sum");
    }
    else
        gmonExists.close();
    
    //system( "mv gmon.out gmon.sum" );
 
    ifstream outExists("gmon.out");
    if( outExists)
    {
        outExists.close();
    	system( ("gprof -s " + progname + " gmon.out gmon.sum").c_str() );
    }
    else
        outExists.close();

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
        if (prezErrorCount( testcaseans, tempfile ) > 0 ) 
            return 2;
        else
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
/**************************************************************************//**
 * @authors xxxxxxx
 *
 * @par Description:
 *
 * @param[in] xxx - xxxxxxxx
 *
 * @returns xxx -
 *
 *****************************************************************************/ 
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
    if (!file2)
    {
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
/**************************************************************************//**
 * @authors xxxxxxx
 *
 * @par Description:
 *
 * @param[in] xxx - xxxxxxxx
 *
 * @returns xxx -
 *
 *****************************************************************************/
void cleanup()
{
    // remove temp files
    char buffer[1024];
    getcwd(buffer,sizeof(buffer));
    string location (buffer);
    string remover;
    location =  "rm " + location + "/temp.txt &>/dev/null";
    system(location.c_str());
    int i =0;
    for(i = 0; i < STUDENTVECTOR.size(); i++)
    {
        remover = "rm " + remove_extension( STUDENTVECTOR[i]) + " -f ";
        //cout << "now we're deleting: " << remover << endl;
        system(remover.c_str());
    }
    STUDENTVECTOR.erase(STUDENTVECTOR.begin(), STUDENTVECTOR.end());
    TESTCASES.erase(TESTCASES.begin(), TESTCASES.end());  


    system( "rm *.gcno *.gcov *.gcda *.covs *.gprof -f &>/dev/null" );
    //system( "rm */*.covs &>/dev/null");
}

/**************************************************************************//**
 * @authors xxxxxxx
 *
 * @par Description:
 *
 * @param[in] xxx - xxxxxxxx
 *
 * @returns xxx -
 *
 *****************************************************************************/
void progbar(int kill_pid, int runtime, string progname)
{

    // //Initialize default parameters
    // int runtime = 60;           //argv1
    // int kill_pid = -123;        //argv2
    // string progname("program"); //argv3

    //Initializations
    float next = 0.05;
    int remaining = 0;
    string progbar("");
    int time = 0;

    //set header
    int len = progname.find_last_of("/");
    progname = progname.substr(len+1, progname.length() - len-1);
    printf("\nTesting %s for %d seconds...\n", progname.c_str(), runtime);
    printf("\n\n\n");

    cout.flush();

    while(time < runtime + 1)
    {   
        /*Return two spaces
          Print Elapsed Time
          Print Remaining Time
          Flush to stdio
          Update progress bar if needed
          Sleep for 1 second*/
        
        remaining = runtime - time;
        printf("\033[F\033[F");
        printf("Elapsed   Time: %d       \n",time);
        printf("Remaining Time: %d       \n",remaining);
        cout.flush();
        printf("[                    ]");
        printf("\r[");
        
        //increment time
        time++;
        
        //update progress bar based on %time remaining
        while( ((float)time / (float)runtime) >= next && next <= 1.00)
        {
            progbar += "=";
            next += 0.05;
        }
        cout << progbar;
        cout.flush();
        if (time < runtime + 1)
            sleep(1);
    }
    cout << endl;
    printf("\033[F[====================]         \n");

    if( kill_pid > 0 )      //This will be < 0 if in standalone mode
        kill(kill_pid, 9);

}

/******************************************************************************
* Author: Hafiza Farzami
* Description: The following function takes in a string and gets rid of the 
* white spaces in it.
* 
* param[in] s - the input string
*
* returns   s - the output string without white spaces
******************************************************************************/
string trim( string s )
{
      s.erase( remove( s.begin(),s.end(),' ' ), s.end());

    return s;
}

/******************************************************************************
* Author: Hafiza Farzami
* Description: The following function takes in a string and a delimiter. It
* breaks the string into two part at the delimiter.
* 
* param[in] s - the string 
* param[in] delim - the delimiter
*
* returns   substrings - the structure containing two parts of the original
*               string
******************************************************************************/
subs subStrings( string s, char delim )
{
    subs substrings;
    int pos = s.find_first_of( delim );
    substrings.first = s.substr( 0, pos ),
        substrings.last = s.substr( pos + 1 );
    trim( substrings.first );
    trim( substrings.last );

    return substrings;
}

/******************************************************************************
* Author: Hafiza Farzami
* Description: The following function takes in two strings to compare them.
* If the strings are of the same size and their first and last letters match,
* the function returns true, else false.
* 
* param[in] s1 - first string 
* param[in] s2 - second string to compare to s1
*
* returns   true - if the strings are "equal"   
*       false - if the strings are not equal
******************************************************************************/
bool compStrs1( string s1, string s2 )
{
    auto x = s1.size();
    auto y = s2.size();

    return (( x != y ) || ( s1[0] != s2[0] ) || ( s1[x - 1] != s2[y - 1] ));    
}


/******************************************************************************
* Author: Hafiza Farzami
* Description: The following function takes in two strings and checks if they
* are anagrams
* 
* param[in] s1 - first string 
* param[in] s2 - second string to compare to s1
*
* returns   true - if the strings are anagrams
*       false - if the strings are not anagrams
******************************************************************************/
bool compStrs2( string s1, string s2 )
{
    sort( s1.begin(), s1.end() );
    sort( s2.begin(), s2.end() );

    return ( s1 == s2 );
}

/******************************************************************************
* Author: Hafiza Farzami
* Description: The following function takes in two strings to compare them.
* If the strings are of the same size and their first and last letters match,
* the function returns true, else false.
* 
* param[in] s1 - first string 
* param[in] s2 - second string to compare to s1
*
* returns   true - if the strings are "equal"   
*       false - if the strings are not equal
******************************************************************************/
bool roundNums( string s1, string s2 )
{
    
    //If the student answer is of lower precision
    if ( s1.size() > s2.size() )
        return false;

    /*If the student's answer is of higher precision, then round to the same
    number of precision as the key's answer*/
    else
    {
        //Break the numbers into whole and decimal parts
        subs solution = subStrings( s1, '.' ); 
        subs diff = subStrings( s2, '.' ); 
        auto x = diff.last.size();

        //Round until the student answer is the same size as the key 
        while( x != solution.last.size() )
        {
            int y = ( diff.last[ x - 1 ] - '0' );

            if( y > 4 && ( diff.last[ x - 2 ] - '0' ) < 9 )
                diff.last[ x - 2 ] += 1;
            
            diff.last.pop_back();
            x--;
        }

        //If the rounded number does not match the key, then return false
        if(( solution.first != diff.first ) || ( solution.last != diff.last ))
            return false;

        return true;
    }
}

/******************************************************************************
* Author: Hafiza Farzami
* Description: The following function counts the number of errors in a given 
* line.
* 
* param[in] first - string stream from the diff file (the key part)
* param[in] last - string stream from the diff file (the student part)
*
* returns   error - the number of errors in a given string stream
******************************************************************************/
int markError( istringstream &first, istringstream &last )
{
    int error = 0;
    int counter = 1;
    string s1, s2;
    while( first >> s1 && last >> s2 )
    {
        if( s1 != s2 )
        {
            if( counter % 2 != 0 )
            {
                if(( compStrs1( s1, s2 ) || compStrs2( s1, s2 )) != 0 )
                    error++;
                else
                    return 0;
            }
            else
            {
                if( roundNums( s1, s2 ) != 0 )
                    error++;
            }
        }
        counter++;
    }
    return error;   
}

/******************************************************************************
* Author: Hafiza Farzami
* Description: The following function makes the diff call on the key and stude-
* nt files. The difference is stored in 'a.out'. The difference is then read in
* and the errors are detected and counted.
* 
* param[in] file1 - name of the key file (as a string)
* param[in] file2 - name of the student file (as a string)
*
* returns   errors - number of errors per file
******************************************************************************/
int prezErrorCount( string file1, string file2 ) 
{
    ifstream difference( "a.out" );
    system(("diff -b -y -i --suppress-common-lines " + file1 + " " + file2 + " > a.out" ).c_str());
    string line;
    subs dif;
    int errors = 0;
    
    while( getline( difference, line ) )
    {
        dif = subStrings( line, '|' ); 
        istringstream desc( dif.first );
            istringstream val( dif.last );
        
        if (markError( desc, val ) > 0)
            errors ++;
        else
            return 0;
    }   

    difference.close();
    return errors;
}

/**************************************************************************//**
 * @authors xxxxxxx
 *
 * @par Description: Originally Lounge Against The Machine's sprint 2 main,
 * reworked into a function for modularity purposes.
 *
 * @param[in] xxx - xxxxxxxx
 *
 * @returns xxx -
 *
 *****************************************************************************/
void tester()
{

    string progname, prog_cpp, progcomp, progdir, nodir, tempdir;
    

    //holds each test and result on a separate line
    vector<string> finaloutfilecontents;
    finaloutfilecontents.clear();
    TOTALPASSED = 0;
    //test for proper program usage from command line
    // QQQ!!! Alex : make gold cpp = ""
    GOLDCPP.clear();

    //fill strings with proper names

    // QQQ!!! Alex: moved to runtests to run on each test 
    /*  prog_cpp = argv[1];
    progname = prog_cpp.substr(0,prog_cpp.find("."));
    progcomp = "g++ -o " + progname  + " " + prog_cpp;
    size_t found = prog_cpp.find_last_of("/\\");// QQQ!!! Alex : why not just ints?
    progdir = progname.substr(0,found+1);

    //compile program to be tested
    system(progcomp.c_str());*/

    char dir[1024];
    getcwd(dir, sizeof(dir));
    string loc (dir);

    TESTCASES = find_tsts(progdir);

    find_students(loc, 0);
    //QQQ!!! Alex: inserting here for new functionality
    string ans;
    // QQQ!!! Alex : gathers all of the .tst files in current and sub directories of the program
    // being tested
    // vector<string> testcases;
    TESTCASES = find_tsts(progdir);

    // QQQ!!! Alex: get the testcases
    find_students(loc, 0);

    // QQQ!!! Alex : while more .tst files need ran, continue running the tests against the
    //program
    int score = 0;
    vector<string> performance;
    string currentProg;


    // QQQ!!! Alex : foreach program (edited to end of main)
    for (int h = 0; h < STUDENTVECTOR.size(); h+=1)
    {
        score = 0;
        // and for each test case
        for(int i=0;i<TESTCASES.size();i++)
        {
            int result = runtests(STUDENTVECTOR[h], TESTCASES.at(i));
            string current = TESTCASES.at(i);
            // failure on critical test
            if (result == 0 && current.substr(current.length() - 8)
                            .find("crit.tst") != -1 )
            {
                score = -1;
                // output the failure
                writeindividualreport(STUDENTVECTOR[h], TESTCASES.at(i), result, h);
                break; // stop tests
            }
            if (result == -999 )  //infinite loop
            {
                score = -1;
                writeindividualreport(STUDENTVECTOR[h], TESTCASES.at(i), result, h);
                break; //stop tests
            }
            if (result > 1)
            {
                score += 1;
                TOTALPASSED +=1;
            }
            writeindividualreport(STUDENTVECTOR[h], TESTCASES.at(i), result, h);

		progname = STUDENTVECTOR[h].substr(0,STUDENTVECTOR[h].find("."));
		tempdir = progname.substr( 0, progname.rfind( "/" ) );
		nodir = progname;
		nodir.erase(0, nodir.find_last_of("/") + 1);
		
		string gprofrun = "gprof -p -b " + progname + " gmon.sum > " + tempdir + "/" + nodir + ".gprof";
		system( gprofrun.c_str() );
                system( "rm gmon.out gmon.sum -f" );
        }
        // QQQ!!! Alex : get report on this program

        currentProg = Generate_Performance_Report(STUDENTVECTOR[h], score, TESTCASES.size());
        finaloutfilecontents.push_back(currentProg);
    }

    createReports();
    //writing all of the results to the .out file
    writefinaloutfile(finaloutfilecontents);//QQQ!!! Alex : progname, finaloutfilecontents);  

    // clean up globals
    cleanup();
    //deleting the temp file
    //remove("temp.txt");

    //exit program    
}
