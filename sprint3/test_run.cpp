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
#include "test_err.hpp"
#include "main.hpp"
using namespace std;

/*********************************GLOBALS************************************/
extern vector<string> STUDENTVECTOR;
extern vector<string> TESTCASES;
extern string GOLDCPP;
extern int TOTALPASSED;
extern vector<report> INDIVIDUALREPORTS;
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

/**************************************************************************//**
 * @authors Alex Wulff, Jonathan Dixon, Hafiza Farzami, Julian Brackins
 *
 * @par Description: Runs all of the .tst test cases against the program one 
 * at a time and returns the results of that particlar test, stored in a string
 *
 * @param[in] prog - cpp file
 * @param[in] specifictestcase - the specific test case
 *
 * @returns 1 - files not equal
 *	    0 - files equal
 * 	    -1 - file did not open for comparison	
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
 
    ifstream outExists("gmon.out");
    if( outExists)
    {
        outExists.close();
    	system( ("gprof -s " + progname + " gmon.out gmon.sum").c_str() );
    }
    else
        outExists.close();

    system(gcovrun.c_str());

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
        if(prezErrorCount( testcaseans, tempfile ) > 0)
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

/**************************************************************************//**
 * @authors Alex Wulff, Julian Brackins, Jonathan Dixon, Hafiza Farzami
 *
 * @par Description: This function compares two files and returns 1 if not equal
 * , 0 if equal
 *
 * @param[in] file1name - the first file
 * @param[in] file2name - the second file, compared to file1name
 *
 * @returns 0 - if files are equal
 * 	    1 - otherwise
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

/**************************************************************************//**
 * @authors Alex Wulff
 *
 * @par Description: The 'cleanup()' function cleans up all the globals
 *
 * @param[in] none 
 *
 * @returns none - void function
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

    INDIVIDUALREPORTS.erase(INDIVIDUALREPORTS.begin(), INDIVIDUALREPORTS.end());
    system( "rm *.gcno *.gcov *.gcda *.covs *.gprof -f &>/dev/null" );
    //system( "rm */*.covs &>/dev/null");
}

/**************************************************************************//**
 * @authors Julian Brackins
 *
 * @par Description: This function kills the process after the given amount
 * of time (runtime).
 *
 * @param[in] kill_pid - process id
 * @param[in] runtime - program runtime
 * @param[in] progname - name of the program
 *
 * @returns none - void function
 *
 *****************************************************************************/
void progbar(int kill_pid, int runtime, string progname)
{

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


/**************************************************************************//**
 * @authors Alex Wulff, Jonathan Dixon, Hafiza Farzami, Julian Brackins
 *
 * @par Description: Originally Lounge Against The Machine's sprint 2 main,
 * reworked into a function for modularity purposes.
 *
 * @param[in] noen
 *
 * @returns none - void function
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

    char dir[1024];
    getcwd(dir, sizeof(dir));
    string loc (dir);

    TESTCASES = find_tsts(progdir);

    int q = 0;
    find_students(loc, 0);

    //QQQ!!! Alex: inserting here for new functionality
    string ans;
    // QQQ!!! Alex : gathers all of the .tst files in current and sub directories of the program
    // being tested
    // vector<string> testcases;
    //TESTCASES = find_tsts(progdir);

    // QQQ!!! Alex: get the testcases
    //find_students(loc, 0);

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
            if (result > 0)
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
}
