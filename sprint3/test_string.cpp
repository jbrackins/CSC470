/**************************************************************************//**
* @file test_string.cpp
*
* @brief An extensize suite of string manipulation functions needed for file
* names, logfile generation, extension handling, and various other operations.
*
* @authors Julian Brackins, Benjamin Sherman
******************************************************************************/

#include "test_string.hpp"
using namespace std;


/**************************************************************************//**
 * @author Benjamin Sherman
 *
 * @par Description: This function reads a file and stores its contents as a
 * stirng.
 *
 * @param[in] file - name of file to open.
 *
 * @returns strStream - string that represents the contents of a file.
 *****************************************************************************/
string getFileStream( string file )
{
    ifstream fin;
    string strStream = "";
    fin.open( file.c_str() );
    if( !fin )
        return "";
    char stream[ 3000 ] = "", temp[ 3000 ] = "";
    strcpy( stream, "\0" );
    fin.getline( temp, 512, '\n' );
    while( !fin.eof() )
    {
        strcat( stream, "\n\t\t" );
        strcat( stream, temp );
        fin.getline( temp, 512, '\n' );
    }
    fin.close();
    strStream = stream;
    return strStream;
}
/**************************************************************************//**
 * @author Benjamin Sherman
 *
 * @par Description: This function gets the current date and time and
 * formats it to a nice human readable string.
 *
 * @returns dateTime - date and time as a string.
 *****************************************************************************/
string getDateTime()
{
    char buffer[ 256 ] = "";
    string dateTime;
    char hrMnSec[ 9 ] = "";
    string m, d, y;
    time_t curTime = time( NULL );
    struct tm *curDate = localtime( &curTime );
    sprintf( buffer, "%d", curDate->tm_mon + 1 );
    m = buffer;
    sprintf( buffer, "%d", curDate->tm_mday );
    d = buffer;
    sprintf( buffer, "%d", curDate->tm_year - 100 );
    y = buffer;
    dateTime = m + "/" + d + "/" + y;
    strftime( hrMnSec, 9, "%H:%M:%S", localtime(&curTime) );
    dateTime += "  " + ( string )hrMnSec;

    return dateTime;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * This function is needed to handle the addition of the .cpp extension on file
 * names. This is important, for example, when compiling the file, as you need
 * the full name of the file (example.cpp) as well as the name of the file sans
 * extension (example)
 *
 * @param[in] input - string containing file name
 *
 * @returns newstring - string similar to parameter input with .cpp extension
 *
 *****************************************************************************/
string add_extension( string input )
{
    input.append( ".cpp" );  
    return input;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * This function is needed to handle the addition of the .cpp extension on file
 * names. This is important, for example, when compiling the file, as you need
 * the full name of the file (example.cpp) as well as the name of the file sans
 * extension (example)
 *
 * @param[in] input - string containing file name
 *
 * @returns newstring - string similar to parameter input with .cpp extension
 *
 *****************************************************************************/
string remove_extension( string input )
{
    unsigned found = input.find_last_of( "." );
    string extension( input.substr( 0, found ) );
    return extension;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * This function is needed to detect the extension on a given file. The
 * extension on the given file is returned as a string.
 * Used for detecting whether files in a directory contain a .tst extension,
 * therefore indicating that the file is a test case.
 *
 * @param[in] input - string containing file name and extension
 *
 * @returns extension - file extension
 *
 *****************************************************************************/
string get_extension( string input )
{
    unsigned found = input.find_last_of( "." );
    string extension( input.substr( found + 1 ) );
    return extension;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * This function is needed to detect the path of a given file. The
 * directory containing the passed in file will be returned.
 *
 * @param[in] input - string containing file name and extension
 *
 * @returns extension - file extension
 *
 *****************************************************************************/
string get_filepath( string input )
{
    unsigned found = input.find_last_of( "/" );
    string extension( input.substr( 0, found + 1 ) );
    return extension;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Returns a string with the current working directory. Useful not only in
 * testing, as the directory traversal can be confusing, but is also needed to
 * pass in pathnames as parameters for other functions in the program.
 *
 * 
 * @returns path - string containing the current working directory
 *
 *****************************************************************************/
string get_pathname()
{
    char buffer[ 1024 ];
    string path;

    getcwd( buffer, sizeof( buffer ) );
    //printf("In %s\n", buffer);
    path = buffer;

    return path;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * String mutation to create a file of the same name, but with a different
 * extension.
 *
 * @param[in] test_case - string containing file name and extension
 * @param[in] ext - new file name extension
 *
 * @returns temp - new string with extension the same as the ext param.
 *
 *****************************************************************************/
string case_name( string test_case, string ext )
{
    char buffer[ 20 ];
    int n;
    string temp( test_case.begin(), test_case.end() - 4 );

    //get a new extension (brought in by second parameter)
    if ( ext.compare( "tst" ) == 0 )
        temp += ".tst";
    else if ( ext.compare( "ans" ) == 0 )
        temp += ".ans";
    else if ( ext.compare( "out" ) == 0 )
        temp += ".out";
    else if ( ext.compare( "tmp" ) == 0 )
        temp += ".tmp";
    else if ( ext.compare( "spec" ) == 0 )
        temp += ".spec";
    else if ( ext.compare( "log" ) == 0 )
        {
            //HANDLE TIMESTAMP
            temp += ".log";
        }
    else
        cout << "Please indicate an extension in second parameter...\n";
    return temp;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Construct a string with the current date and time.
 *
 * @returns ymdt - date string with year_month_date_time format
 *
 *****************************************************************************/
string timestamp() 
{
    time_t now = time( 0 );
    struct tm tstruct;
    char buffer[ 80 ];
    tstruct = *localtime( &now );
    
    strftime( buffer, sizeof( buffer ), "%Y_%m_%d_%X", &tstruct );
    
    string ymdt( str_replace( buffer, ':', '_' ) );
    return ymdt;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Replaces every character in a string that matches the first parameter (a)
 * with the second parameter character (b)
 *
 * @param[in] a - character to be replaced
 * @param[in] b - character to replace a
 *
 * @returns str - new string with replaced characters
 *
 *****************************************************************************/
string str_replace( string str, char a, char b ) 
{
    for( int i = 0; i < str.length(); ++i ) 
    {
        if( str[ i ] == a )
        str[ i ] = b;
    }
    return str;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * A function that creates a string containing the log file name with the
 * appropriate timestamp extension.
 *
 * @param[in] cpp_file - file name
 *
 * @returns log_str += "_" + timestamp() + ".log" - .log file with timestamp
 *
 *****************************************************************************/
string log_filename( string cpp_file ) 
{
    cpp_file = remove_extension( cpp_file );
    string log_str( cpp_file );
    return log_str += "_" + timestamp() + ".log";
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * A function that creates a string containing the summary file name with the
 * appropriate timestamp extension.
 *
 * @param[in] cpp_file - file name
 *
 * @returns log_str += "_" + timestamp() + ".log" - .log file with timestamp
 *
 *****************************************************************************/
string summary_filename() 
{
    return "Summary_" + timestamp() + ".log";
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * A small function to calculate the percentage of test cases passed.
 *
 * @param[in] right - number of test cases passed
 * @param[in] total - total number of test cases
 *
 * @returns float( ( float(right) / float(total) ) * 100 ) - % of passed test
 *
 *****************************************************************************/
double grade_percent(int right, int total) 
{
    return float( ( float( right ) / float( total ) ) * 100 );
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * A double containing the percentage of test cases correct is brought into
 * this function and a grade letter is assigned.
 *
 * @param[in] grade_percent - percent of test cases passed
 *
 * @returns letter - Letter grade
 *
 *****************************************************************************/
string grade_letter(double grade_percent) 
{
    string letter;

    if( grade_percent >= 90.0 )
        letter = "A"; 
    else if( grade_percent >= 80.0 )
        letter = "B";  
    else if( grade_percent >= 70.0 )
        letter = "C"; 
    else if( grade_percent >= 60.0 )
        letter = "D"; 
    else
        letter = "F";     
    return letter;
}

/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Construct a string with the student's name. It even capitalizes the first
 * and last name of the student. The name is generated based on the cpp_file
 * brought into this function, as it is understood the name of the student
 * will be the cpp file name.
 *
 * @param[in] cpp_file - file name
 *
 * @returns name - string containing student's name
 *
 *****************************************************************************/
string get_student_name( string cpp_file ) 
{
    unsigned found = cpp_file.find_last_of( "/" );
    string name( cpp_file.substr( found + 1 ) );
    replace( name.begin(), name.end(), '_', ' ');
    name[ 0 ] = toupper( name[ 0 ] );
    found = name.find_first_of( " " );
    name[ ( int )found + 1 ] = toupper( name[ ( int )found + 1 ] );

    return name;
}