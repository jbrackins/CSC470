// Doxygen Header:
/**************************************************************************//**
* @file main.cpp
*
* @brief This file contains the main function which calls the three sorts.
*
* @mainpage Directory searcher
*
* @section course_section Course Information
*
* @author Benjamin Sherman
*
* @date Februaty 16th, 2014
*
* @par Instructor:
* Dr. Logar
*
* @par Course:
* Benjamin Sherman: CSC 470
*
* @section Program Program 2 Information
*
* @details This program will traverse the file directory the executable is in.
* It will then search all the file, subfolders, and subfolder's files for any
* file that has an extension of "tst".
******************************************************************************/
#include <iostream>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <vector>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
////                       FUNCTION PROTOTYPES
///////////////////////////////////////////////////////////////////////////////
void drct_recur ( char * buffer);
void get_folders (char * buffer);
void get_files (char * buffer);

vector<string> tstLocations;
/**************************************************************************//**
 * @author Benjamin Sherman
 *
 * @par Description: This is the main function. It calls the function that
 * recursively traverses the user
 * specified directory.
 *
 * @returns 0 Program successfully executed.
 *****************************************************************************/
int main ()
{
    char path[PATH_MAX];
    getcwd(path, sizeof(path));

    drct_recur ( path);

    // print out files found with "tst" extension
    for(int i = 0; i < (int)tstLocations.size(); i++)
    {
        cout << tstLocations[i] << endl;
    }

    return 0;
}

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
    get_folders ( buffer);
    get_files (  buffer);
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
void get_folders (char * buffer)
{
    DIR *a_folder;
    struct dirent *dir_handle;
    vector<string> paths;
    bool subdir = false;
    int attrib;
    char path[PATH_MAX];
    strcat(path, "~");
    strcat(path, buffer);
    a_folder = opendir(buffer);
    if ( a_folder == NULL ) // call directory
    {
        //cout << buffer << endl;
        //cout << "opendir failed" << endl;
        return;
    }

    dir_handle = readdir(a_folder);
    if ( dir_handle == NULL )
    {
        // cout << buffer << endl;
        //cout << "readdir failed << endl" << endl;
        return;
    }
    strcpy(path, buffer);

    // search for and step into folders
    do
    {
        attrib = (int)dir_handle->d_type;
        if ( attrib == 4 && strcmp( dir_handle->d_name, "." ) != 0
             && strcmp(dir_handle->d_name, "..") != 0)
        {
            subdir = true; // set to true when we find and step into a folder
            char name[PATH_MAX];
            strcpy(name, dir_handle->d_name);
            strcat(path, "/");
            strcat(path, dir_handle->d_name);
            paths.push_back(path);
        }

        if (subdir)
        {
            strcat(path, "/..");
            chdir("..");
        }
        subdir = false; // reset test variable that determines if we found and processed a folder

    }
    while ( (dir_handle = readdir(a_folder))!= NULL );

    while(!paths.empty())
    {   string temp =  paths.back();
        paths.pop_back();
        char pth[PATH_MAX];
        strcpy(pth, temp.c_str());
        drct_recur(pth);
    }

    closedir(a_folder);
}

/**************************************************************************//**
 * @author Benjamin Sherman
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
void get_files (char * buffer)
{
    DIR *a_file;
    struct dirent *dir_handle;

    a_file = opendir(buffer);
    dir_handle = readdir(a_file);
    string ext = dir_handle->d_name;
    string path = buffer;
    string name = dir_handle->d_name;

    if ( dir_handle != NULL )
    {
        do // search for files with "tst" extension
        {
            name = dir_handle->d_name;
            ext = name.substr(name.find_last_of(".") + 1);
            if ( 8 == (int)dir_handle->d_type && ext == "tst" )
            {
                path += ("/" + name);
                tstLocations.push_back(path);
            }

        }
        while ( (dir_handle = readdir(a_file)) != NULL);
    }

    closedir(a_file);
}
