#include "test_menu.hpp"
#include "test_string.hpp"
#include "main.hpp"
#include "test_dir.hpp"
#include "test_ui.hpp"
#include "test_gen.hpp"
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

/**************************************************************************//**
* @author Julian Brackins
*
* @par Description:
* This function reads the specification file, determines the number of 
******************************************************************************/
void read_spec_file()
{
    struct menu_option option[25];
    int i, j, k = 0;

    int total_options = 0;
    ifstream input;
    string line[25];
    stringstream strstream;
    char * temp;
    bool loop;

    int amountToGenerate, filesToMake;
    ofstream fout;

    char dir[1024];
    getcwd(dir, sizeof(dir));
    string loc (dir);
    string file;

    SPECFILE = "";

    i = 0;

    cout << "Please enter name of the specifications file" << endl;
    prompt(); 
    cin >> TEMPSPEC;
    cin.ignore(10000, '\n');

    find_spec_file(loc, 0);
    if( SPECFILE.length() < 1 )
    {
        cout << TEMPSPEC << " is not a valid specifications file" << endl;
        TEMPSPEC = "";
        SPECFILE = "";
        chdir(HOME_DIR.c_str());
        main_menu();
    }

    input.open(SPECFILE.c_str());
    if(!input)
    {
        cout << "error opening " << SPECFILE << endl;
        exit(0);
    }
    /*Go through each line to figure out how many
      options exist in the spec file.*/
    while( getline( input, line[total_options] ) ) 
        total_options++;


    while( i < total_options ) 
    {
        /*Associate each option structure's number variable
         with an option number from the spec file*/
        option[i].number = strtok( (char*)line[i].c_str(), " ");
        loop = true;

        /*Set iterator to 0*/
        j = 0;
        do
        {
            /*Tokenize the data types that the option reads in
              remember, there can be as many data types for each
              option as the spec file indicates, or none at all!
              this code should handle any situation, and keeps track
              of how many arguments a given option has*/
            temp = strtok(NULL, " ");
            if(temp != NULL )
                option[i].type[j] = temp;
            else
            {
                option[i].type[j] = "";
                loop = false;
            }
            j++;
        }while(loop);
        option[i].args = j-1;  
        i++;
    }

    generatemenutestcasesmenu(amountToGenerate, filesToMake);

    for (int i = 0 ; i < filesToMake; i +=1)
    {
        // make string of file name
        strstream.str("");
        strstream << i;
        file = "./tests/GeneratedTestCase" + strstream.str() + ".tst";
        fout.open(file.c_str());

        // populate 
        srand(time(NULL));
        int x = 0;
        //Minimum generation
        for(x = 0; x < total_options+2; x++)
        {
            if (x != total_options) //ignore "exit" option
                option_generator(x, option, total_options, fout);
        }

        //Extemporaneous Generation
        for(x = 0; x < amountToGenerate; x++)
        {
            int r = (rand()%(total_options)+1);

            if (r != total_options) //ignore "exit" option
                option_generator(r, option, total_options, fout);
            else
                x--;                //don't count if "exit" had generated
        }
        //Generate the "exit" option last
        option_generator(total_options, option, total_options, fout);
        fout.close();
    }

}

void option_generator(int opt, struct menu_option option[], int arr_size, ofstream &fout)
{
    /*This function takes an array of menu options, matches the
      option.number with the corresponding option number from the spec
      file, and generates an appropriate test case according to that spec*/
    fout << opt << " ";
    for(int i = 0; i < arr_size; i++)
    {
        if(atoi(option[i].number) == opt)
        {
            for(int j = 0; j < option[i].args; j++)
            {
                double test_case_in = random_generator(option[i].type[j]);
                fout << test_case_in << " ";
                srand(test_case_in);
            }    
        }
    }
    fout << endl;
}




/**************************************************************************//**
* @author Julian Brackins
*
* @par Description:
* Returns either an integer value or double value, depending on what the
* variable "kind" contains. Note that this function "technically" returns
* doubles regardless, but if the kind variable is designated as "int", the
* value returned is an integer, so there is no floating point involved.
******************************************************************************/
double random_generator(string kind)
{
    double number = ((float)rand()/(float)(RAND_MAX)) * 2000;// / RAND_MAX;
    int inumber = rand() % 2000;
    if (kind == "int")
        return inumber;
    else
        return number;
    sleep(2);
}