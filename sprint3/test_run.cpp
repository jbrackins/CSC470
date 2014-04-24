
#include "test_run.hpp"
#include "test_string.hpp"
using namespace std;

/*********************************GLOBALS************************************/
extern vector<string> STUDENTVECTOR;
extern vector<string> TESTCASES;
extern string GOLDCPP;
extern int TOTALPASSED;
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
 *
 * This function has been imported from my dsh.c program in Operating Systems!
 * Why rewrite a redirect function if ya already got one, am I right?
 *
 * Keeping this in mind, there have been some heavy modifications to this so
 * that it accomodates the needs for this sprint 3 testing suite.
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
    char  childpid1_buff[10];
    char  * childpid1_str;
    int temp_pid;

    int run_time = 6;
    char  time_buff[10];
    char  * time_str;
    int temp_time;

    int   status = 0; 

    char* temp;

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
    //printf("program is %d\n",childpid1);
    

    temp_pid = snprintf(childpid1_buff, sizeof(childpid1_buff), "%ld", childpid1);
    childpid1_str = childpid1_buff;

    temp_time = snprintf(time_buff, sizeof(time_buff), "%ld", run_time);
    time_str = time_buff;

    strcpy(progname, args[0]);
    strcpy(line,"./progbar ");
    strcat(line, time_str); 
    strcat(line, " ");
    strcat(line, childpid1_str);  
    strcat(line, " ");  
    strcat(line, progname);

    num_pbar = 0;
    pbar[num_pbar] = strtok(line, " ");
    while (pbar[num_pbar] != NULL)
    {
        num_pbar++;
        pbar[num_pbar] = strtok(NULL, " ");
    }
    num_pbar--;

    childpid2 = fork();
    if (childpid2 == 0)
    {
        execvp(pbar[0], pbar);
        perror("Exec failed:");
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
        printf("%s failed to complete in %d seconds...\n", progname, run_time); 
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
    //system(progrun.c_str());
    int infinite_loop = Event_REDIRECT(progrun.c_str());

    if(infinite_loop < 0)
    {
        return infinite_loop;
    }
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
void cleanup()
{
    // remove temp files
    char buffer[1024];
    getcwd(buffer,sizeof(buffer));
    string location (buffer);
    location =  "rm " + location + "/temp.txt";
    system(location.c_str());
    STUDENTVECTOR.erase(STUDENTVECTOR.begin(), STUDENTVECTOR.end());
    TESTCASES.erase(TESTCASES.begin(), TESTCASES.end());  

    system( "rm *.gcno *.gcov *.gcda *.covs -f" );
}
