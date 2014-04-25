#include "test_gen.hpp"
using namespace std;


/*********************************GLOBALS************************************/
extern vector<string> STUDENTVECTOR;
extern vector<string> TESTCASES;
extern string GOLDCPP;
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

    //make welcome menu
    cout << "\nWelcome to the test-case generator!\n" << endl;
    //cout << "\033[1;34mbold Press 'x' and enter at any time to leave.\033[0m\n";

    while(1)
    {
        // inquire about cleaning old tests or overwrite?
        cout << "\nRemove old generated tests (y) or just overwrite as needed (n)?" << endl;
        cin >> input;
        transform( input.begin(), input.end(), input.begin(), ::tolower);
        if (!input.compare("y") || !input.compare("yes"))
        {
            cout << "\n\tClearing..." << endl;
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
        cout << "What type of data would you like?  Ints or Doubles? (i/d)"  << endl;
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
        cout << "How many test cases would you like? (Enter a numeric value)"  << endl;
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
        cout << "Would you like a specific amount of items to test? (y/n)"  << endl;
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
            cout << "More or less than a specific value? (more/less)"  << endl;
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
        cout << "What value should I work with? (Enter a numeric value)"  << endl;
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
        cout << "range of values? (y/n)" << endl;
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
        cout << "What minimum value should I work with? (Enter a numeric value)"  << endl;
        cin >> input;
        if (!input.compare("x") || !input.compare("X"))
        {
            cout << "Exiting.  Please run again." << endl;
            exit(0); // change of heart
        }
        min = atof(input.c_str());

        cout << "What max value should I work with? (Enter a numeric value)"  << endl;
        cin >> input;
        if (!input.compare("x") || !input.compare("X"))
        {
            cout << "Exiting.  Please run again." << endl;
            exit(0); // change of heart
        }
        max = atof(input.c_str());
    }

}

/****************************pregenerateclean********************************/
// QQQ!!! Alex : removes old generated test cases
/****************************************************************************/
void pregenerateclean()
{
    system("rm ./tests/GeneratedTestCase*");
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
        + GOLDCPP;
    system(cmd.c_str());
    string programName = GOLDCPP.substr(GOLDCPP.rfind("/") + 1);
    programName = programName.substr(0,programName.find(".cpp"));

    // look at all test cases
    for (int i = 0 ; i < TESTCASES.size() ; i +=1)
    {
        // if it's a generated test case
        if (TESTCASES[i].find("GeneratedTestCase") != -1)
        {
            cmd = "./" + programName 
                + " < " + TESTCASES[i].substr(2) + " > " 
                + " " + TESTCASES[i].substr(2,TESTCASES[i].rfind(".tst") -2)
                + ".ans";
            system(cmd.c_str());
        }
    }
}