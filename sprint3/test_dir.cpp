/**************************************************************************//**
* @file test_dir.cpp
*
* @brief 
*
* @authors Julian Brackins, Alex Wulff
******************************************************************************/

#include "test_dir.hpp"
#include "main.hpp"
using namespace std;

/*********************************GLOBALS************************************/
extern vector<string> STUDENTVECTOR;
extern vector<report> INDIVIDUALREPORTS;
extern string GOLDCPP;
extern string SPECFILE;
extern string TEMPSPEC;
extern string TEMPGCPP;
/****************************************************************************/

/**************************************************************************//**
 * @authors Alex Wulff, Julian Brackins, Jonathan Dixon
 *
 * @par Description: Built to directory crawl and find all student files and 
 * avoid duplicates and the golden cpp . Modified to handle golden
 * cpp detection more effectively.
 *
 * @param[in] directory - the directory to look for students
 * @param[in] level - the level of the directory
 *
 * @returns none - void function
 *
 *****************************************************************************/
void find_students(string directory, int level)
{
    int length;
    int i;
    report tempreport;
    string temp(directory);
    DIR *dir = opendir(temp.c_str()); // open the current directory
    struct dirent *entry;
    if (!dir)
    {
        // not a directory
        return;
    }
    while (entry = readdir(dir)) // notice the single '='
    {
        temp = entry->d_name;
        if (temp == TEMPGCPP)
        {
            GOLDCPP = directory + '/' + temp;
        }
        if ( temp != "." && temp != ".." )
        {
            if ( temp[temp.size() - 1] != '~' )
            {
                length = temp.length();
                if ( (length > 4 && (temp.substr(length-4) == ".cpp") 
                    || temp.substr(length-2) == ".C")
                    && level > 0 )
                {
                    // because I'm getting duplicates
                    string insert = directory + '/' + temp;
                    if (find(STUDENTVECTOR.begin(), 
                        STUDENTVECTOR.end(), 
                        insert) == STUDENTVECTOR.end() 
                        && level != 0) // if not found
                    {
                        STUDENTVECTOR.push_back(insert);
                        
                        tempreport.filename = insert;
                        INDIVIDUALREPORTS.push_back(tempreport);
                        
                    }
                    else if (find(STUDENTVECTOR.begin(),
                        STUDENTVECTOR.end(),
                        insert) == STUDENTVECTOR.end() 
                        && GOLDCPP.empty() 
                        && temp == TEMPGCPP)
                    {
                        GOLDCPP = directory + '/' + temp;
                    }
                }
                else
                {
                    if (temp == TEMPGCPP)
                    {
                        GOLDCPP = directory + '/' + temp;
                        // cout << "golden cpp is " << GOLDCPP << endl;
                    }
                    find_students(directory + '/' + temp, level + 1);
                }
            }
        }
    }
    closedir(dir);
}

/**************************************************************************//**
 * @authors Alex Wulff, Julian Brackins, Jonathan Dixon
 *
 * @par Description: Locates all .tst files to be ran against the program to be 
 * tested
 *
 * @param[in] progdir - program directory
 *
 * @returns tstfilelist - list of tst files
 *
 *****************************************************************************/ 
vector<string> find_tsts(string progdir)
{
    vector<string> tstfilelist;
    tstfilelist.clear();    

    string popencommand = "find "+progdir+" -name '*.tst'";
    FILE * f = popen( popencommand.c_str(), "r" );

    const int BUFSIZE = 1000;
    char buf[ BUFSIZE ];
    int i = 0;
    while( fgets( buf, BUFSIZE,  f ) ) 
    {
        tstfilelist.push_back(buf);
    }
    pclose( f );

    //removing that frustrating invisible character at the end of the strings
    for(int i=0;i<tstfilelist.size();i++)
    {
        tstfilelist.at(i).replace(tstfilelist.at(i).end()-1,
        tstfilelist.at(i).end(),"");
    }

    // QQQ!!! Alex: iterate over tstfilelist and put all crit.tst in the 
    // front of list
    for(int i=0;i<tstfilelist.size();i++)
    {
        string temp = tstfilelist.at(i);
        if (!temp.substr(temp.length() - 8).compare("crit.tst"))
        {
            tstfilelist.erase(tstfilelist.begin() + i);
            tstfilelist.insert(tstfilelist.begin(), temp);
        }
    }

    return tstfilelist;
}

/**************************************************************************//**
 * @authors Alex Wulff, Jonathan Dixon, Julian Brackins 
 *
 * @par Description: This function locates the spec file.
 *
 * @param[in] directory - a given directory
 * @param[in] level - the level spec file can be
 * 
 * @returns none - void function
 *
 *****************************************************************************/
void find_spec_file(string directory, int level)
{
    int length;
    int i;
    report tempreport;
    string temp(directory);
    DIR *dir = opendir(temp.c_str()); // open the current directory
    struct dirent *entry;
    if (!dir)
    {
        // not a directory
        return;
    }
    while (entry = readdir(dir)) // notice the single '='
    {
        temp = entry->d_name;
        if ( temp != "." && temp != ".." )
        {
            if ( temp[temp.size() - 1] != '~' )
            {
                length = temp.length();
                if ( temp == TEMPSPEC && length > 5 && temp.substr(length-5) == ".spec" )
                {
                    SPECFILE = directory + '/' + temp;
                }
                else
                {
                    find_spec_file(directory + '/' + temp, level + 1);
                }
            }
        }
    }
    closedir(dir);
}
