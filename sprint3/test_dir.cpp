#include "test_dir.hpp"
#include "main.hpp"
using namespace std;



/*********************************GLOBALS************************************/
extern vector<string> STUDENTVECTOR;
extern vector<report> INDIVIDUALREPORTS;
extern vector<string> TESTCASES;
extern string GOLDCPP;
extern int TOTALPASSED;
/****************************************************************************/

/******************************find_students********************************/
// QQQ!!! Alex : built to directory crawl and find all student files and 
// avoid duplicates and the golden cpp (praesumo presumo)
/****************************************************************************/
void find_students(string directory, int level)
{
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
                int length = temp.length();
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
                        && level == 0)
                    {
                        GOLDCPP = directory + '/' + temp;
                    }
                }
                else
                {
                    if (GOLDCPP.empty()
                        && ((temp.substr(length-4) == ".cpp")
                        || temp.substr(length-2) == ".C")
                        && level == 0)
                    {
                        GOLDCPP = directory + '/' + temp;
                    }
                    find_students(directory + '/' + temp, level + 1);
                }
            }
        }
    }
    closedir(dir);
}

/********************************* find_tsts **********************************/
// Locates all .tst files to be ran against the program to be tested
/******************************************************************************/ 
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
/******************************* END find_tsts ********************************/

