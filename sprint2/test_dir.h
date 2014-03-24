#ifndef __TEST_DIR_H_INCLUDED__
#define __TEST_DIR_H_INCLUDED__

#include "header.h"
#include "test.h"

void drct_recur( char * buffer );
void get_folders( char * buffer );
void get_files( char * buffer );
void getTstCases();
void getCppFiles();
bool compareFileNames( string a, string b );

/**************************************************************************//**
 * @author Benjamin Sherman
 *
 * @par Description:
 * This function calls "get_folders" and "get_files". It
 * returns on completion of the these two functions.  It gets called
 * again in "get_folders" if a folder is found under the directory path
 * contained in the variable "buffer".
 *
 * @param[in] buffer - contains a file/folder directory path.
 *****************************************************************************/
void drct_recur (char * buffer)
{
    get_folders ( buffer );
    get_files (  buffer );
}

/**************************************************************************//**
 * @author Benjamin Sherman
 *
 * @par Description:
 I This function will loop through the folders and files
 * contained within the directory ignoring all of the files and stepping
 * into all of the folders by calling it's self.  This function will keep
 * calling it's self only if it finds a folder in the first directory or any
 * subdirectory after that.
 *
 * @param[in] buffer - contains a file/folder directory path.
 *****************************************************************************/
void get_folders( char * buffer )
{
    DIR *a_folder;
    struct dirent *dir_handle;
    vector<string> paths;
    bool subdir = false;
    int attrib;
    char path[ PATH_MAX ] = "";
    strcat( path, "~" );
    strcat( path, buffer );
    a_folder = opendir( buffer );
    if ( a_folder == NULL ) // call directory
    {
        return;
    }

    dir_handle = readdir( a_folder );
    if ( dir_handle == NULL )
    {
        return;
    }
    strcpy( path, buffer );
    // search for and step into folders
    do
    {
        attrib = ( int )dir_handle->d_type;
        if ( attrib == 4 && strcmp( dir_handle->d_name, "." ) != 0
             && strcmp( dir_handle->d_name, ".." ) != 0)
        {
            // set to true when we find and step into a folder
            subdir = true;
            char name[ PATH_MAX ];
            strcpy( name, dir_handle->d_name );
            strcat( path, "/" );
            strcat( path, dir_handle->d_name );
            paths.push_back( path );
        }

        if ( subdir )
        {
            strcat( path, "/.." );
            getcwd( path, sizeof( path ));
        }
        // reset test variable that determines 
        // if we found and processed a folder
        subdir = false;
        // reset path
        strcpy( path, buffer );
    } while ( ( dir_handle = readdir( a_folder ) )!= NULL );

    while( !paths.empty() )
    {   
    	string temp =  paths.back();
        paths.pop_back();
        char pth[ PATH_MAX ];
        strcpy( pth, temp.c_str() );
        drct_recur( pth );
    }

    closedir( a_folder );
}

/**************************************************************************//**
 * @author Julian Brackins, Benjamin Sherman
 *
 * @par Description:
 * This function will loop through the folders and files
 * contained within the directory ignoring all of the folders. It will check
 * if each file in a directory has a "tst" extension. If a file does have
 * a "tst" extension, the function will append that file's directory address
 * to the global vector<string> tstLocations.
 *
 * @param[in] buffer - contains a file/folder directory path.
 *****************************************************************************/
void get_files( char * buffer )
{
    DIR *a_file;
    struct dirent *dir_handle;

    a_file = opendir( buffer );
    dir_handle = readdir( a_file );
    string ext = dir_handle->d_name;
    string path;
    string name = dir_handle->d_name;

    if ( dir_handle != NULL )
    {
        do // search for files with "tst" extension
        {
            path = buffer;
            name = dir_handle->d_name;
            /*Check to see if the file has an extension BUT special case
              so that test.cpp file is not added to the compiled file stack.*/
            if( name.find_last_of( "." ) != string::npos && name != "test.cpp" )
                ext = name.substr( name.find_last_of( "." ) );
            else 
                ext = "";
            if ( 8 == ( int )dir_handle->d_type 
                && ( ext == ".tst"  || ext == ".ans" || ext == ".cpp" ) )
            {
                path += ( "/" + name );
                if( ext == ".tst" )
	                tstLocations.push_back( path );
                else if( ext == ".ans" )
		        ansLocations.push_back( path );
                else if(ext == ".cpp")
		        cppLocations.push_back( path );
            }

        }
        while ( ( dir_handle = readdir( a_file ) ) != NULL );
    }

    closedir( a_file );
}

/**************************************************************************//**
 * @author Julian Brackins, Benjamin Sherman
 *
 * @par Description: This is the main function. It calls the function that
 * recursively traverses the user
 * specified directory.
 *
 * @returns 0 Program successfully executed.
 *****************************************************************************/
void getTstCases()
{
    char path[ PATH_MAX ] = "";
    bool ansFound;
    string tst, ans;
    getcwd( path, sizeof( path ) );

    drct_recur( path );

    // check that a tst file has a matching ans file
    for( int i = 0; i < ( int )tstLocations.size(); i++ )
    {
	ansFound = false;
	tst = tstLocations[ i ].substr( 0, tstLocations[ i ].find_last_of( "." ) );
        tst = tst.substr( tst.find_last_of( "/" ) + 1 );
    	for( int j = 0; j < ( int )ansLocations.size(); j++ )
	{
            ans = ansLocations[ j ].substr( 0, ansLocations[ j ].find_last_of( "." ) );
            ans = ans.substr( ans.find_last_of( "/" ) + 1 );
            if( tst == ans )
                ansFound = true;
	}
        // discard tst file if no matching ans file found
        if( !ansFound )
            tstLocations.erase( tstLocations.begin() + i );
    }

    sort( tstLocations.begin(), tstLocations.end(), compareFileNames );
    sort( ansLocations.begin(), ansLocations.end(), compareFileNames );


}

/**************************************************************************//**
 * @author Julian Brackins, Benjamin Sherman
 *
 * @par Description: This is the main function. It calls the function that
 * recursively traverses the user
 * specified directory.
 *
 * @returns 0 Program successfully executed.
 *****************************************************************************/
void getCppFiles()
{
    char path[ PATH_MAX ] = "";
    bool ansFound;
    string tst, ans;
    getcwd( path, sizeof( path ) );

    drct_recur( path );

    // check that a tst file has a matching ans file
    for( int i = 0; i < ( int )tstLocations.size(); i++ )
    {
	ansFound = false;
	tst = tstLocations[ i ].substr( 0, tstLocations[ i ].find_last_of( "." ) );
        tst = tst.substr( tst.find_last_of( "/" ) + 1 );
    	for( int j = 0; j < ( int )ansLocations.size(); j++ )
	{
            ans = ansLocations[ j ].substr( 0, ansLocations[ j ].find_last_of( "." ) );
            ans = ans.substr( ans.find_last_of( "/" ) + 1 );
            if( tst == ans )
                ansFound = true;
	}
        // discard tst file if no matching ans file found
        if( !ansFound )
            tstLocations.erase( tstLocations.begin() + i );
    }

    sort( tstLocations.begin(), tstLocations.end(), compareFileNames );
    sort( ansLocations.begin(), ansLocations.end(), compareFileNames );

}

//Needs header

///////////////
bool compareFileNames( string a, string b )
{
    string fileA = a.substr( a.find_last_of( '/' ) + 1 );
    string fileB = b.substr( b.find_last_of( '/' ) + 1 );
    if( fileA > fileB )
        return true;
    else
        return false;
}

#endif
