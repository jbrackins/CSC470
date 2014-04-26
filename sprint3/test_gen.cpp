#include "test_gen.hpp"
#include "test_run.hpp"
#include "test_dir.hpp"
#include "main.hpp"
#include "test_ui.hpp"
using namespace std;


/*********************************GLOBALS************************************/
extern vector<string> STUDENTVECTOR;
extern vector<string> TESTCASES;
extern string GOLDCPP;
extern string SPECFILE;
extern string TEMPSPEC;
extern string TEMPGCPP;
extern string HOME_DIR;
extern int TOTALPASSED;
/****************************************************************************/
/********************************Defines*************************************/
int MININT = -2147483647;
/****************************************************************************/
/******************************generatetestcases*****************************/
//QQQ!!! Alex : testcase builder starts here
/****************************************************************************/
void generatetestcases()
{
    bool doubles, lesserThanAmount, greaterThanAmount;
    double min, max;
    long long inserts;
    int amountToGenerate, filesToMake;
    ofstream fout;
    string file;
    stringstream temp;
    generatetestcasesmenu(doubles, lesserThanAmount, greaterThanAmount, min, max, amountToGenerate, filesToMake);
    double inValue;
    unsigned short drandSeed = 128;

    string progname;
    string prog_cpp;
    string progcomp;
    string progdir;
    char dir[1024];
    getcwd(dir, sizeof(dir));
    string loc (dir);

    // if max and min are both max (none selected, use 0,1 as it leaves rand)

    // seed random
    srand (time(NULL));
    seed48(&drandSeed);

    // if doubles
    if (doubles)
    {
        // make each file
        for (int i = 0 ; i < filesToMake; i +=1)
        {
            // make string of file name
            temp.str("");
            temp << i;
            file = "./tests/GeneratedTestCase" + temp.str() + ".tst";
            fout.open(file.c_str());

            // populate 
            if (lesserThanAmount)
            {
                inserts = rand() % amountToGenerate;
                // if 0, run again
                if (inserts == 0)
                {
                    inserts = rand() % amountToGenerate;
                }
            }
            else if (greaterThanAmount)
            {
                inserts = rand() % (amountToGenerate * 5) + amountToGenerate;
                // if amount... run again
                if (inserts == amountToGenerate)
                {
                    inserts = rand() % (amountToGenerate * 5) + amountToGenerate;
                }
            }
            else
            {
                inserts = amountToGenerate;
            }
            for (int j = 0; j < inserts; j +=1)
            {
                // threshold     offset to min   by random fraction   times the difference
                if (max != 1)
                {
                    inValue = (min + (rand() % (int)max) + 1) * drand48();
                }
                else
                {
                    inValue = (MININT * rand()) + (rand() + rand()) * drand48();
                }
                fout << fixed;
                fout << inValue << endl;
            }
            fout.close();
        }
    }

    else
    {
        // make for ints
        for (int i = 0 ; i < filesToMake; i +=1)
        {
            // make string of file name
            temp.str("");
            temp << i;
            file = "./tests/GeneratedTestCase" + temp.str() + ".tst";
            fout.open(file.c_str());

            // populate 
            if (lesserThanAmount)
            {
                inserts = rand() % amountToGenerate;
                // if 0, run again
                if (inserts == 0)
                {
                    inserts = rand() % amountToGenerate;
                }
            }
            else if (greaterThanAmount)
            {
                inserts = rand() % (amountToGenerate * 5 + amountToGenerate);
                // if amount... run again
                if (inserts == amountToGenerate)
                {
                    inserts = rand() % (amountToGenerate * 5 + amountToGenerate);
                }
            }
            else
            {
                inserts = amountToGenerate;
            }
            // works for ints too
            for (int j = 0; j < inserts; j +=1)
            {
                // threshold  offset to min   by random fraction   times the difference
                //int inValue = (int) (min + ((double) rand() / RAND_MAX) * (max - min));
                if (max != 1 && min != 0)
                {
                    inValue = (int (min) + rand()) % int(max) + 1;
                }
                else
                {
                    inValue = MININT + rand() + rand(); // Max at randmax, min at LONG_MIN
                }        
                fout << (int) inValue << endl;
            }
            fout.close();
        }

    }

    set_goldencpp();
    // find all tests and use generated tests to make ans
    TESTCASES = find_tsts(progdir);
    
    find_students(loc, 0);
    if( GOLDCPP.length() < 1 )
    {
        cout << TEMPGCPP << " is not a valid golden .cpp file" << endl;
        TEMPGCPP = "";
        GOLDCPP = "";
        chdir(HOME_DIR.c_str());
        main_menu();
    }
    generateanswers();
    // clean  
    cleanup();

    cout << "\nTest generation completed. Press enter to continue.\n\n";


}

/******************************generatetestcases*****************************/
//QQQ!!! Alex : testcase builder starts here
/****************************************************************************/
void generatestringtestcases()
{
    int filesToMake;
   
    string file;
    stringstream temp;

    char * str;
    int length = 0, stringsToGen, maxLen;
    ofstream rand_out;

    string progname;
    string prog_cpp;
    string progcomp;
    string progdir;
    char dir[1024];
    getcwd(dir, sizeof(dir));
    string loc (dir);


    generatestringtestcasesmenu(stringsToGen, maxLen, filesToMake);

    // if max and min are both max (none selected, use 0,1 as it leaves rand)

    // seed random
    srand (time(NULL));


    // make each file
    for (int i = 0 ; i < filesToMake; i +=1)
    {
        // make string of file name
        temp.str("");
        temp << i;
        file = "./tests/GeneratedTestCase" + temp.str() + ".tst";
        rand_out.open(file.c_str());

        for( long int j = 0; j < stringsToGen; j++ )
        {
            length = rand() % maxLen + 1;
            //cout << length << endl;
            gen_random(str, length);

            rand_out << str << endl;
            //length ++;
        }

        rand_out.close();
    }

    
    set_goldencpp();
    // find all tests and use generated tests to make ans
    TESTCASES = find_tsts(progdir);
    
    find_students(loc, 0);
    if( GOLDCPP.length() < 1 )
    {
        cout << TEMPGCPP << " is not a valid golden .cpp file" << endl;
        TEMPGCPP = "";
        GOLDCPP = "";
        chdir(HOME_DIR.c_str());
        main_menu();
    }
    generateanswers();
    // clean  
    cleanup();
    cout << "\nTest generation completed. Press enter to continue.\n\n";
}

void gen_random(char *s, const int len) 
{
    static const char alpha[] = "abcdefghijklmnopqrstuvwxyz1234567890";

    for (int i = 0; i < len; ++i) {
        s[i] = alpha[rand() % (sizeof(alpha) - 1)];
    }

    s[len] = 0;
}

/****************************generatetestcasemenu****************************/
//QQQ!!! Alex : testcase builder menu is here... long...
/****************************************************************************/
void generatetestcasesmenu(bool &doubles, bool &lesserThanAmount, 
                           bool &greaterThanAmount, double &min, double &max, 
                           int &amountToGenerate, int &filesToMake)
{
    string input = "";
    bool range;

    // defaults for min and max
    min = 0;
    max = 1;

    //Make sure directory exists. redirect to dev/null so terminal
    //doesn't notify you that it already exists (should usually exist)...
    system("mkdir ./tests/ &>/dev/null");
    //make welcome menu
    cout << "\nGenerating numeric test cases.\n" << endl;
    //cout << "\033[1;34mbold Press 'x' and enter at any time to leave.\033[0m\n";

    while(1)
    {
        // inquire about cleaning old tests or overwrite?
        cout << "\nRemove old generated tests (y) or just overwrite as needed (n)?" << endl;
        prompt(); 
        cin >> input;
        transform( input.begin(), input.end(), input.begin(), ::tolower);
        if (!input.compare("y") || !input.compare("yes"))
        {
            cout << "\nClearing..." << endl;
            pregenerateclean();
            break;
        }
        else if (!input.compare("n") || !input.compare("no"))
        {
            break;
        }
        cout << "I didn't understand.  Please try again." << endl;
    }

    // start by asking about type
    while(1)
    {
        cout << "\nWhat type of data would you like?  Ints or Doubles? (i/d)"  << endl;
        prompt(); 
        cin >> input;
        transform( input.begin(), input.end(), input.begin(), ::tolower); 
        if (!input.compare("int") || !input.compare("ints") || !input.compare("i"))
        {
            doubles = false;
            break;
        }   
        else if (!input.compare("double") || !input.compare("doubles") 
            || !input.compare("d"))
            {
            doubles = true;
            break;
        }
        else if (!input.compare("x"))
        {
            cout << "Exiting.  Please run again." << endl;
            exit(0); // change of heart
        }
        else
        {
            cout << "\nI did not understand.  Please re-enter." << endl;
        }
    }

    // count of test cases?
    while(1)
    {
        cout << "\nHow many test cases would you like? (Enter a numeric value)"  << endl;
        prompt(); 
        cin >> input;
        filesToMake = atoi(input.c_str());
        if (filesToMake >= 0)
        { 
            break;
        }
        else if (!input.compare("x"))
        {
            cout << "Exiting.  Please run again." << endl;
            exit(0); // change of heart
        }
        else
        {
            cout << "\nPlease re-enter as a positive number or 'x' to cancel." << endl;
        }
    }

    // specific amount to work with?
    while(1)
    {
        cout << "\nWould you like a specific amount of items to test? (y/n)"  << endl;
        prompt(); 
        cin >> input;
        transform( input.begin(), input.end(), input.begin(), ::tolower);
        if (!input.compare("y") || !input.compare("yes"))
        {
            lesserThanAmount = greaterThanAmount = false;
            break;
        }
        else if (!input.compare("n") || !input.compare("no"))
        {
            lesserThanAmount = greaterThanAmount = true;
            break;
        }
        else if (!input.compare("x"))
        {
            cout << "Exiting.  Please run again." << endl;
            exit(0); // change of heart
        }
        else
        {
            cout << "\nPlease re-enter." << endl;
        }
    }

    // if not
    if (lesserThanAmount)
    {
        while(1)
        {
            cout << "\nMore or less than a specific value? (more/less)"  << endl;
            prompt(); 
            cin >> input;
            transform( input.begin(), input.end(), input.begin(), ::tolower);
            if (!input.compare("<") || !input.compare("less"))
            {
                greaterThanAmount = false;
                break;
            }
            else if (!input.compare(">") || !input.compare("more"))
            {
                lesserThanAmount = false;
                break;
            }
            else if (!input.compare("x"))
            {
                cout << "Exiting.  Please run again." << endl;
                exit(0); // change of heart
            }
            else
            {
                cout << "\nPlease re-enter." << endl;
            }
        }
    }

    // value of items in tests
    while(1)
    {
        cout << "\nWhat value should I work with? (Enter a numeric value)"  << endl;
        prompt(); 
        cin >> input;
        amountToGenerate = atoi(input.c_str());
        if (amountToGenerate > 0)
        {
            break;
        }
        else if (!input.compare("x") || !input.compare("X"))
        {
            cout << "Exiting.  Please run again." << endl;
            exit(0); // change of heart
        }
        else
        {
            cout << "\nPlease re-enter value greater than 0." << endl;
        }
    }

    //range
    do
    {
        cout << "\nManually set Range of values? (y/n)" << endl;
        prompt(); 
        cin >> input;
        transform( input.begin(), input.end(), input.begin(), ::tolower);
        if (input.compare("n") == 0 || input.compare("no") == 0 )
        {
            range = false;
            break;
        }
        else if (!input.compare("x") || !input.compare("X"))
        {
            cout << "Exiting.  Please run again." << endl;
            exit(0); // change of heart
        }
        else if (input.compare("y") == 0 || input.compare("yes") == 0 )
        {
            range = true;
            break;
        }
    }
    while (1);

    if (range)
    {
        cout << "\nSet minimum value. (Enter a numeric value)"  << endl;
        prompt(); 
        cin >> input;
        if (!input.compare("x") || !input.compare("X"))
        {
            cout << "Exiting.  Please run again." << endl;
            exit(0); // change of heart
        }
        min = atof(input.c_str());

        cout << "\nSet maximum value. (Enter a numeric value)"  << endl;
        prompt(); 
        cin >> input;
        if (!input.compare("x") || !input.compare("X"))
        {
            cout << "Exiting.  Please run again." << endl;
            exit(0); // change of heart
        }
        max = atof(input.c_str());
    }

}

/****************************generatetestcasemenu****************************/
//QQQ!!! Alex : testcase builder menu is here... long...
/****************************************************************************/
void generatestringtestcasesmenu(int &stringsToGen, int &maxLen, int &filesToMake)
{
    string input = "";
    // defaults for min and max

    //Make sure directory exists. redirect to dev/null so terminal
    //doesn't notify you that it already exists (should usually exist)...
    system("mkdir ./tests/ &>/dev/null");

    //make welcome menu
    cout << "\nGenerating Alpha-numeric String test cases.\n" << endl;
    //cout << "\033[1;34mbold Press 'x' and enter at any time to leave.\033[0m\n";


    while(1)
    {
        // inquire about cleaning old tests or overwrite?
        cout << "\nRemove old generated tests (y) or just overwrite as needed (n)?" << endl;
        prompt(); 
        cin >> input;
        transform( input.begin(), input.end(), input.begin(), ::tolower);
        if (!input.compare("y") || !input.compare("yes"))
        {
            cout << "\nClearing..." << endl;
            pregenerateclean();
            break;
        }
        else if (!input.compare("n") || !input.compare("no"))
        {
            break;
        }
        cout << "I didn't understand.  Please try again." << endl;
    }

    // count of test cases?
    while(1)
    {
        cout << "\nHow many test cases would you like? (Enter a numeric value)"  << endl;
        prompt(); 
        cin >> input;
        filesToMake = atoi(input.c_str());
        if (filesToMake >= 0)
        { 
            break;
        }
        else if (!input.compare("x"))
        {
            cout << "Exiting.  Please run again." << endl;
            exit(0); // change of heart
        }
        else
        {
            cout << "\nPlease re-enter as a positive number or 'x' to cancel." << endl;
        }
    }

    // value of items in tests
    while(1)
    {
        cout << "\nHow many strings would you like\n"; 
        cout << "to generate per file? (Enter a numeric value)"  << endl;
        prompt(); 
        cin >> input;
        stringsToGen = atoi(input.c_str());
        if (stringsToGen > 0)
        {
            break;
        }
        else if (!input.compare("x") || !input.compare("X"))
        {
            cout << "Exiting.  Please run again." << endl;
            exit(0); // change of heart
        }
        else
        {
            cout << "\nPlease re-enter value greater than 0." << endl;
        }
    }

    // max string length
    while(1)
    {
        cout << "\nWhat is the max length for a string?\n"; 
        cout << "(Enter a numeric value)"  << endl;
        prompt(); 
        cin >> input;
        maxLen = atoi(input.c_str());
        if (maxLen > 0)
        {
            break;
        }
        else if (!input.compare("x") || !input.compare("X"))
        {
            cout << "Exiting.  Please run again." << endl;
            exit(0); // change of heart
        }
        else
        {
            cout << "\nPlease re-enter value greater than 0." << endl;
        }
    }
}

void generatemenutestcasesmenu(int &amountToGenerate, int &filesToMake)
{
    string input = "";
    bool range;

    //Make sure directory exists. redirect to dev/null so terminal
    //doesn't notify you that it already exists (should usually exist)...
    system("mkdir ./tests/ &>/dev/null");


    //make welcome menu
    cout << "\nGenerating menu-based test cases using the specfile:\n";
    cout << SPECFILE << endl;
    //cout << "\033[1;34mbold Press 'x' and enter at any time to leave.\033[0m\n";

    while(1)
    {
        // inquire about cleaning old tests or overwrite?
        cout << "\nRemove old generated tests (y) or just overwrite as needed (n)?" << endl;
        prompt(); 
        cin >> input;
        transform( input.begin(), input.end(), input.begin(), ::tolower);
        if (!input.compare("y") || !input.compare("yes"))
        {
            cout << "\nClearing..." << endl;
            pregenerateclean();
            break;
        }
        else if (!input.compare("n") || !input.compare("no"))
        {
            break;
        }
        cout << "I didn't understand.  Please try again." << endl;
    }

    // count of test cases?
    while(1)
    {
        cout << "\nHow many test cases would you like? (Enter a numeric value)"  << endl;
        prompt();
        cin >> input;
        filesToMake = atoi(input.c_str());
        if (filesToMake >= 0)
        { 
            break;
        }
        else if (!input.compare("x"))
        {
            cout << "Exiting.  Please run again." << endl;
            exit(0); // change of heart
        }
        else
        {
            cout << "\nPlease re-enter as a positive number or 'x' to cancel." << endl;
        }
    }

    amountToGenerate = 0;
    while(1)
    {
        // inquire about cleaning old tests or overwrite?
        cout << "\nChoose Minimum inputs per test case or Manually set\n";
        cout << "A) Minimum inputs (Tests every option once)\n";
        cout << "B) Robust  inputs (Tests minimum + additional inputs)\n";
        prompt(); 
        cin >> input;
        transform( input.begin(), input.end(), input.begin(), ::tolower);
        if (!input.compare("a") || !input.compare("minimum"))
        {
            break;
        }
        else if (!input.compare("b") || !input.compare("robust"))
        {
                // value of items in tests
            while(1)
            {
                cout << "\nHow many additional option inputs ";
                cout << "should there be?\n (Enter a numeric value)"  << endl;
                prompt(); 
                cin >> input;
                amountToGenerate = atoi(input.c_str());
                if (amountToGenerate > 0)
                {
                    break;
                }
                else if (!input.compare("x") || !input.compare("X"))
                {
                    cout << "Exiting.  Please run again." << endl;
                    exit(0); // change of heart
                }
                else
                {
                    cout << "\nPlease re-enter value greater than 0." << endl;
                }
            }
            break;
        }
        cout << "\nI didn't understand.  Please try again." << endl;
    }

}
/****************************pregenerateclean********************************/
// QQQ!!! Alex : removes old generated test cases
/****************************************************************************/
void pregenerateclean()
{
    system("rm ./tests/GeneratedTestCase* &>/dev/null");
}

/*******************************generateanswers******************************/
// QQQ!!! Alex : needed to generate answers to new tests using the golden cpp.
/****************************************************************************/

void generateanswers()
{
    // compile golden cpp
    string cmd = "g++ -o " 
        + GOLDCPP.substr(0,GOLDCPP.rfind(".cpp")) 
        + " " 
        + GOLDCPP 
        + " &>/dev/null";
    system(cmd.c_str());
    //string //programName = GOLDCPP.substr(GOLDCPP.rfind("/") + 1);
    string programName = GOLDCPP.substr(0,GOLDCPP.find(".cpp"));

    // look at all test cases
    for (int i = 0 ; i < TESTCASES.size() ; i +=1)
    {
        // if it's a generated test case
        if (TESTCASES[i].find("GeneratedTestCase") != -1)
        {
            cmd = programName 
                + " &>/dev/null < " + TESTCASES[i].substr(2) + " > " 
                + " " + TESTCASES[i].substr(2,TESTCASES[i].rfind(".tst") -2)
                + ".ans";
            system(cmd.c_str());
        }
    }
}

void set_goldencpp()
{
    char buffer[100];
    cin.ignore(10000, '\n');
    cout << "Enter Golden cpp file name. This file is needed\n";
    cout << "to properly generate ans files for the test cases\n";
    cout << ">> ";
    

    //read in commands, break up arguments into tokens
    fgets(buffer,100, stdin);

    string temp1(buffer);
    string temp2(temp1.begin(), temp1.end()-1);
    TEMPGCPP = temp2;
    //cin.ignore(10000, '\n');
}