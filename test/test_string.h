#ifndef __TEST_STRING_H_INCLUDED__
#define __TEST_STRING_H_INCLUDED__

#include "header.h"

string getDateTime();
string getFileStream(string file);

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
string getFileStream(string file)
{
    ifstream fin;
    string strStream = "";
    fin.open(file.c_str());
    if(!fin)
        return "";
    char stream[3000] = "", temp[3000] = "";
    strcpy(stream, "\0");
    fin.getline(temp, 512, '\n');
    while(!fin.eof())
    {
        strcat(stream, "\n\t\t");
        strcat(stream, temp);
        fin.getline(temp, 512, '\n');
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
    char buffer[256] = "";
    string dateTime;
    char hrMnSec[9] = "";
    string m, d, y;
    time_t curTime = time(NULL);
    struct tm *curDate = localtime(&curTime);
    sprintf(buffer, "%d", curDate->tm_mon + 1);
    m = buffer;
    sprintf(buffer, "%d", curDate->tm_mday);
    d = buffer;
    sprintf(buffer, "%d", curDate->tm_year - 100);
    y = buffer;
    dateTime = m + "/" + d + "/" + y;
    strftime(hrMnSec, 9, "%H:%M:%S", localtime(&curTime));
    dateTime += "  " + (string)hrMnSec;

    return dateTime;
}

#endif
