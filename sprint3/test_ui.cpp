#include "test_ui.hpp"
using namespace std;



int main()
{
    loop_time = 60;

    //dir_list();
    main_menu();

    return 0;
}

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
    while(1)
    {
        menu_header();
        choice = get_choice( );
        if ( choice == 1 )
            grade_program_menu();
        else if ( choice == 2 )
        {
            test_case_menu();
        }
        else if ( choice == 3 )
            set_max_menu( );
        else if ( choice == 4 )
            exit(0);
        else
            cout << "Please enter a valid selection from the menu,\n";
    }
}

void test_case_menu()
{
    int choice = 0;
    while(1)
    {
        test_case_header();
        choice = get_choice( );
        if ( choice == 1 )
        {

        }
        else if ( choice == 2 )
        {

        }
        else if ( choice == 3 )
        {

        }
        else if ( choice == 4 )
            main_menu();
        else
            cout << "Please enter a valid selection from the menu,\n";
    }
}

string grade_program_menu()
{
    string input;
    string arg;
    char* command;
    char* filename;
    char buffer[100];

   
    do
    {
        grade_program_header();
        cout << ">> ";             //prompt

        //read in commands, break up arguments into tokens
        fgets(buffer,100, stdin);
        command = strtok(buffer," \n");
        filename = strtok(NULL, " \n");

        input = command;
        
        if(input.compare("1") == 0)
            main_menu();
        else
            return input;
    }while(command != NULL);
     //Check to see if NULL command was sent from console
}

void set_max_menu( )
{
    // intitializing variable
    int choice = 0;
    // output menu
    set_max_header();

    while(1)
    {
        cout << ">> ";
        // input the user's choice
        cin >> choice;
        if(choice <= 0)
            cout << "Maximum Test Time must be greater than 0" << endl;
        else
        {
            loop_time = choice;
            cout << "Maximum Test Time is ";
            cout << loop_time << "." << endl;
            cin.clear();
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
    // intitializing variable
    int choice = 0;
    // output menu
    // input the user's choice

    string input;
    string arg;
    char* command;
    char* filename;
    char buffer[100];

    cout << ">> ";             //prompt

    //read in commands, break up arguments into tokens
    fgets(buffer,100, stdin);
    command = strtok(buffer," \n");
    filename = strtok(NULL, " \n");

    //Check to see if NULL command was sent from console
    if(command != NULL)
    {
        input = command;
        
        //test <filename>
        //handle improper commands here as well
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
        // else if(input.compare("1") == 0)
        //     return 1;
    }
    return 0;
}


void test_case_header()
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
    cout << "=   4) Exit Testing Suite                                           =\n";
    cout << "=                                                                   =\n";
    cout << "=                                                                   =\n";
    cout << "=====================================================================\n";
}

void grade_program_header()
{
    cout << "=====================AUTOMATED TESTING SUITE v.3=====================\n";
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

