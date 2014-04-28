/**************************************************************************//**
* @file test_ui.cpp
*
* @brief 
*
* @author Julian Brackins
******************************************************************************/

#include "test_ui.hpp"
#include "test_gen.hpp"
#include "test_run.hpp"
#include "test_dir.hpp"
#include "test_menu.hpp"
#include "test_string.hpp"
#include "main.hpp"

using namespace std;

/*********************************GLOBALS************************************/
extern vector<report> INDIVIDUALREPORTS;
extern vector<string> TESTCASES;
extern vector<string> LOGVECTOR;
extern string HOME_DIR;
extern int loop_time;      //time tester will allow a program to run
/****************************************************************************/

/***************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Displays User interface for program
 *
 * @param[] none
 *
 *
 ******************************************************************************/
void main_menu()
{
    int choice = 0;
    string run;
    while(1)
    {
        menu_header();
        choice = get_choice( );
        if ( choice == 1 )
        {
            run = grade_program_menu();

            if(run.compare("1") == 0)
                main_menu();
            else
            {
                if( chdir(run.c_str()) == 0 )
                    tester();
                else
                    cout << run << " is not a directory...\n";
                chdir(HOME_DIR.c_str());
            }
                
        }
        else if ( choice == 2 )
        {
            run = test_case_menu1();

            if(run.compare("1") == 0)
                main_menu();
            else
            {
                if( chdir(run.c_str()) == 0 )
                    test_case_menu2();
                else
                    cout << run << " is not a directory...\n";
                chdir(HOME_DIR.c_str());
            }
        }
        else if ( choice == 3 )
            set_max_menu( );
        else if ( choice == 4 )
        {
            view_logfile_menu2();
        }
        else if ( choice == 5 )
            exit(0);
        else
            cout << "Please enter a valid selection from the menu,\n";
    }
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
string test_case_menu1()
{
    string input;
    string arg;
    char* command;
    char* filename;
    char buffer[100];

   
    do
    {
        test_case_header1();
        prompt();             //prompt

        //read in commands, break up arguments into tokens
        fgets(buffer,100, stdin);
        command = strtok(buffer," \n");
        filename = strtok(NULL, " \n");

        input = command;
        
        if(input.compare("1") == 0)
        {
            chdir(HOME_DIR.c_str());
            main_menu();
        }
            
        else
            return input;
    }while(command != NULL);
     //Check to see if NULL command was sent from console
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
void test_case_menu2()
{
    int choice = 0;
    while(1)
    {
        test_case_header2();
        choice = get_choice( );
        if ( choice == 1 )
        {
            generatetestcases();
            cin.ignore(10000, '\n');
            chdir(HOME_DIR.c_str());
            main_menu();
        }
        else if ( choice == 2 )
        {
            generatestringtestcases();
            cin.ignore(10000, '\n');
            chdir(HOME_DIR.c_str());
            main_menu();
        }
        else if ( choice == 3 )
        {
            read_spec_file();
            cin.ignore(10000, '\n');
            chdir(HOME_DIR.c_str());
            main_menu();
        }
        else if ( choice == 4 )
        {
            chdir(HOME_DIR.c_str());
            main_menu();
        }
        else
            cout << "Please enter a valid selection from the menu,\n";
    }
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
string grade_program_menu()
{
    string input;
    string arg;
    char* command;
    char* filename;
    char buffer[100];
   
    /*Prompt user to enter the name of the program they
      wish to grade.*/
    do
    {
        grade_program_header();
        prompt();             //prompt

        //read in commands, break up arguments into tokens
        fgets(buffer,100, stdin);
        command = strtok(buffer," \n");
        filename = strtok(NULL, " \n");

        input = command;
        
        if(input.compare("1") == 0)
        {
            chdir(HOME_DIR.c_str());
            main_menu();
        }
        else
            return input;
    }while(command != NULL);
     //Check to see if NULL command was sent from console
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
string view_logfile_menu()
{
    string input;
    string arg;
    char* command;
    char* filename;
    char buffer[100];
   
    /*Prompt user to enter the name of the program they
      wish to grade.*/
    do
    {
        view_logfile_header1();
        prompt();             //prompt

        //read in commands, break up arguments into tokens
        fgets(buffer,100, stdin);
        command = strtok(buffer," \n");
        filename = strtok(NULL, " \n");

        input = command;
        
        if(input.compare("1") == 0)
        {
            chdir(HOME_DIR.c_str());
            main_menu();
        }
        else
            return input;
    }while(command != NULL);
     //Check to see if NULL command was sent from console
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
string view_student_menu()
{
    string input;
    string arg;
    char* command;
    char* filename;
    char buffer[100];
   
    /*Prompt user to enter the name of the program they
      wish to grade.*/
    do
    {
        view_logfile_header2();
        prompt();             //prompt

        //read in commands, break up arguments into tokens
        fgets(buffer,100, stdin);
        command = strtok(buffer," \n");
        filename = strtok(NULL, " \n");

        input = command;
        
        return input;
    }while(command != NULL);
     //Check to see if NULL command was sent from console
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
void set_max_menu( )
{
    // intitializing variable
    int choice = 0;
    // output menu
    set_max_header();

    while(1)
    {
        prompt();         // input the user's choice
        cin >> choice;
        if(choice <= 0)
            cout << "Maximum Test Time must be greater than 0" << endl;
        else
        {
            loop_time = choice;
            cout << "Maximum Test Time is ";
            cout << loop_time << "." << endl;
            cin.ignore(10000, '\n');
            break;
        }
    }  
}

/***************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Prints menu and retrieves user's choice
 *
 * @param[] none
 *
 * @returns choice selected by the user
 *
 ******************************************************************************/
int get_choice( )
{
    int choice = 0;

    string input;
    string arg;
    char* command;
    char* filename;
    char buffer[100];

    prompt();              
    //read in commands, break up arguments into tokens
    fgets(buffer,100, stdin);
    command = strtok(buffer," \n");
    filename = strtok(NULL, " \n");

    /*Tokenizing occurs to handle if somebody tries
     to be clever and break the console by adding
     too many values to terminal at a time*/
    //Check to see if NULL command was sent from console
    if(command != NULL)
    {
        input = command;
        
        if(input.compare("1") == 0)
            return 1;
        else if(input.compare("2") == 0)
            return 2;
        else if(input.compare("3") == 0)
            return 3;
        else if(input.compare("4") == 0)
            return 4;
        else if(input.compare("5") == 0)
            return 5;
        else if(input.compare("6") == 0)
            return 6;
    }
    return 0;
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
void test_case_header1()
{
    cout << "=====================AUTOMATED TESTING SUITE v.3=====================\n";
    cout << "=                                                                   =\n";
    cout << "=                                                                   =\n";
    cout << "=   Please enter the name of the program you wish to generate       =\n";
    cout << "=   test cases for:                                                 =\n";
    cout << "=                                                                   =\n";
    dir_list();
    cout << "=   Enter '1' to go back to main menu                               =\n";
    cout << "=                                                                   =\n";
    cout << "=                                                                   =\n";
    cout << "=====================================================================\n";
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
void test_case_header2()
{
    cout << "=========================GENERATE TEST CASES=========================\n";
    cout << "=                                                                   =\n";
    cout << "=                                                                   =\n";
    cout << "=   Please Select the types of test cases                           =\n";
    cout << "=   you would like to generate:                                     =\n";
    cout << "=                                                                   =\n";
    cout << "=   1) Numeric Test Cases (Ints & Doubles)                          =\n";
    cout << "=   2) Alpha-numeric Test Cases (Strings containing 'a-z' + '0-9')  =\n";
    cout << "=   3) Menu-Driven Test Cases (Requires Specification File)         =\n";
    cout << "=   4) Go Back...                                                   =\n";
    cout << "=                                                                   =\n";
    cout << "=                                                                   =\n";
    cout << "=====================================================================\n";
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
void menu_header()
{
    cout << "=====================AUTOMATED TESTING SUITE v.3=====================\n";
    cout << "=                                                                   =\n";
    cout << "=                                                                   =\n";
    cout << "=   Please Make a selection:                                        =\n";
    cout << "=                                                                   =\n";
    cout << "=   1) Grade a Program                                              =\n";
    cout << "=   2) Generate Test Cases                                          =\n";
    cout << "=   3) Set Maximum Test Time                                        =\n";
    cout << "=   4) View Log Files                                               =\n";
    cout << "=   5) Exit Testing Suite                                           =\n";
    cout << "=                                                                   =\n";
    cout << "=                                                                   =\n";
    cout << "=====================================================================\n";
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
void grade_program_header()
{
    cout << "============================GRADE PROGRAM============================\n";
    cout << "=                                                                   =\n";
    cout << "=                                                                   =\n";
    cout << "=   Please enter the name of the program you wish to grade:         =\n";
    cout << "=                                                                   =\n";
    dir_list();
    cout << "=   Enter '1' to go back to main menu                               =\n";
    cout << "=                                                                   =\n";
    cout << "=                                                                   =\n";
    cout << "=====================================================================\n";
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
void set_max_header()
{

    cout << "========================SET MAXIMUM TEST TIME========================\n";
    cout << "=                                                                   =\n";
    cout << "=                                                                   =\n";
    cout << "=   Please set a new value for the maximum test time in seconds.    =\n";
    cout << "=   Programs that do not complete within this time are graded       =\n";
    cout << "=   with a 'critical failure' score.                                =\n";
    cout << "=                                                                   =\n";
    cout << "=   Current Maximum Test Time:                                      =\n";
    print_max_time();
    cout << "=                                                                   =\n";
    cout << "=                                                                   =\n";
    cout << "=====================================================================\n";
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
void view_logfile_header1()
{
    cout << "============================VIEW LOGFILES============================\n";
    cout << "=                                                                   =\n";
    cout << "=                                                                   =\n";
    cout << "=   Please enter the name of the program you wish                   =\n";
    cout << "=   to view logs for:                                               =\n";
    cout << "=                                                                   =\n";
    dir_list();
    cout << "=   Enter '1' to go back to main menu                               =\n";
    cout << "=                                                                   =\n";
    cout << "=                                                                   =\n";
    cout << "=====================================================================\n";
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
void view_logfile_header2()
{
    cout << "==========================VIEW STUDENT LOGS==========================\n";
    cout << "=                                                                   =\n";
    cout << "=                                                                   =\n";
    cout << "=   Select a Student directory from the following:                  =\n";
    cout << "=                                                                   =\n";
    dir_list();
    cout << "=   Enter '1' to go back to main menu                               =\n";
    cout << "=                                                                   =\n";
    cout << "=                                                                   =\n";
    cout << "=====================================================================\n";
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
void view_logfile_menu2()
{
    string input = "";
    string run = "";
    int choice;
    bool summfile, studentfile, logfile, covfile, proffile;
    cout << "Viewing log files for " << get_pathname() << endl;
    string gohome = get_pathname();
    int i;
    while(1)
    {
        cout << "==========================VIEW STUDENT LOGS==========================\n";
        cout << "=                                                                   =\n";
        cout << "=                                                                   =\n";
        cout << "=   Please select a log file type you wish to view:                 =\n";
        cout << "=                                                                   =\n";
        cout << "=   1) View Summary Files containing class grades                   =\n";
        cout << "=   2) View Individual Log Files for a student (.log or .covs)      =\n";
        cout << "=   3) Go Back...                                                   =\n";
        cout << "=                                                                   =\n";
        cout << "=                                                                   =\n";
        cout << "=====================================================================\n";

        prompt();
        cin >> input;
        choice = atoi(input.c_str());

        if ( choice == 1 )
        {
            cin.ignore(10000, '\n');
            summfile = true;
            studentfile = false;
            break;
        }
        else if ( choice == 2 )
        {
            cin.ignore(10000, '\n');
            summfile = false;
            studentfile = true;
            break;
        }
        else if ( choice == 3 )
        {
            cin.ignore(10000, '\n');
            chdir(gohome.c_str());
            view_logfile_menu();
        }
        cout << "I didn't understand.  Please try again." << endl;
    }


    while(1)
    {
        run = view_logfile_menu();

        if(run.compare("1") == 0)
        {
            cin.ignore(10000, '\n');
            chdir(HOME_DIR.c_str());
            main_menu();
        }
        else if( chdir(run.c_str()) != 0 )
            cout << run << " is not a directory...\n";
        else
            break;
    }
  

    int loop = 1;
    if(studentfile)
    {
        while(loop)
        {
            run = view_student_menu();

            if(run.compare("1") == 0)
            {
                cin.ignore(10000, '\n');
                chdir(gohome.c_str());
                view_logfile_menu();
            }
            else
            {
                if( chdir(run.c_str()) == 0 )
                    loop = 0;
                else
                    cout << run << " is not a directory...\n";
            }      
        }
    }
                
    if(studentfile)
    {
        while(1)
        {
            //Header for 2) Student Files
            cout << "==========================VIEW STUDENT LOGS==========================\n";
            cout << "=                                                                   =\n";
            cout << "=                                                                   =\n";
            cout << "=   What type of Student Files do you wish to view?                 =\n";
            cout << "=                                                                   =\n";
            cout << "=   1) Log files containing grades and test results                 =\n";
            cout << "=   2) Code Coverage files                                          =\n";
            cout << "=   3) Gprof files containing function efficiency                   =\n";
            cout << "=   4) Display All (.log, .gprof, .covs)                            =\n";
            cout << "=   5) Go Back...                                                   =\n";
            cout << "=                                                                   =\n";
            cout << "=                                                                   =\n";
            cout << "=====================================================================\n";

            prompt();
            cin >> input;
            choice = atoi(input.c_str());

            if ( choice == 1 )
            {
                logfile = true;
                covfile = false;
                proffile = false;
                break;
            }
            else if ( choice == 2 )
            {
                logfile = false;
                covfile = true;
                proffile = false;
                break;
            }
            else if ( choice == 3 )
            {
                logfile = false;
                covfile = false;
                proffile = true;
                break;
            }
            else if ( choice == 4 )
            {
                logfile = true;
                covfile = true;
                proffile = true;
                break;
            }
            else if ( choice == 5 )
            {
                cin.ignore(10000, '\n');
                chdir(gohome.c_str());
                view_logfile_menu();
            }
            cout << "I didn't understand.  Please try again." << endl;
        }
    }

    collect_logs(summfile, logfile, covfile, proffile);


    filelist:

    if(summfile)
        cout << "\nSummary";
    else if(logfile)
        cout << "\nLog";
    else if(covfile)
        cout << "\nGCov";
    cout << " Files:" << endl;

    for(i = 0; i < LOGVECTOR.size(); i++)
        cout << (i + 1) << ") " << LOGVECTOR[i] << endl;
    cout << (LOGVECTOR.size() + 1) << ") " << "Return to Main Menu..." << endl;
    //cin.ignore(10000, '\n');

    string kitty = "";
    int viewfile;
    while(1)
    {
        prompt(); 
        cin >> input;
        viewfile = atoi(input.c_str());
        if (viewfile == (LOGVECTOR.size()+1))
            goto end;
        else if ( viewfile > (LOGVECTOR.size()+1) || viewfile < 1 )
            cout << "\nPlease enter a correct value to open a file." << endl;
        else if (viewfile > 0)
            break;
    }

    cout << endl;
    
    kitty = "cat " + LOGVECTOR[viewfile -1];
    cout << "\n=========================================================\n";
    cout << "Opening File " << LOGVECTOR[viewfile -1] << "..." << endl;
    system(kitty.c_str());
    cout << "\n=========================================================\n";
    cout << endl;
    goto filelist;
    end:
    cin.ignore(10000, '\n');
    chdir(gohome.c_str());
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
void print_max_time()
{
    int i;
    char str[15];
    sprintf(str, "%d", loop_time);
    string max_loop(str);
    cout << "=    " << max_loop << " second(s)";

    for(i = 0; i < 53 - max_loop.length(); i++)
        cout << " ";
    cout  << "=\n";
}

/**************************************************************************//**
* @author Julian Brackins
*
* @par Description:
* Prints a list of all folders in the current directory. This is useful for
* the ./grade user, as it lists all directories that could contain programs
* to test.
* A modified version of queue_directories(), sans the recursion.
* 
* @returns none
*
*****************************************************************************/
void dir_list()
{
    int i;
    DIR *dp;
    struct dirent *dirp;
    
    string file_name;

    char buffer[ 1024 ];
    string path;

    getcwd( buffer, sizeof( buffer ) );
    
    path = buffer;
    path += "/";

    if ((dp = opendir(path.c_str())) == NULL) 
    {
        cout << "Error opening directory...\n";
        exit(0);
    } 
    else 
    {
        while ((dirp = readdir(dp)) != NULL) 
        {
            if (dirp->d_name != string(".") && dirp->d_name != string("..")) 
            {
                if (is_dir(path + dirp->d_name) == true) 
                {
                    file_name =  dirp->d_name;
                    cout << "=   " << file_name;
                    for(i = 0; i < 64 - file_name.length(); i++)
                    {
                        cout << " ";
                    }
                    cout  << "=\n";
                }
            }
        }
        closedir(dp);
    }
}

 /**************************************************************************//**
  * @author Julian Brackins
  *
  * @par Description:
  * Prints usage statement
  *
  * @returns none
  *
  *****************************************************************************/
bool is_dir(string dir)
{
    struct stat fileInfo;
    stat(dir.c_str(), &fileInfo);
    if (S_ISDIR(fileInfo.st_mode))
        return true;
    else 
        return false;
}

void collect_logs(bool summ, bool log, bool cov, bool prof)
{
    LOGVECTOR.clear();    

    string ls = "ls | more";
    FILE * f = popen( ls.c_str(), "r" );

    const int BUFSIZE = 1000;
    char buf[ BUFSIZE ];
    string temp = "";
    int length;
    int i = 0;

    string str ("Summary");
    // different member versions of find in the same order as above:
    size_t found;

    while( fgets( buf, BUFSIZE,  f ) ) 
    {
        temp = buf;
        temp.replace(temp.end()-1, temp.end(),"");
        found = temp.find(str);

        length = temp.length();
        if ( log && length > 4 && (temp.substr(length-4) == ".log") )
            LOGVECTOR.push_back(temp.c_str());
        else if ( cov && length > 5 && (temp.substr(length-5) == ".covs") )
            LOGVECTOR.push_back(temp.c_str());
        else if ( summ && found != std::string::npos )
            LOGVECTOR.push_back(temp.c_str());
        else if ( prof && length > 6 && (temp.substr(length-6) == ".gprof") )
            LOGVECTOR.push_back(temp.c_str());
    }
    pclose( f );
    sort(LOGVECTOR.begin(),LOGVECTOR.end());
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
void prompt() {cout << ">> ";}