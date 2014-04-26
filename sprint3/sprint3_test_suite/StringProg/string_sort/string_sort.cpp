/* Prog1.cpp
*
* Jonathan Dixon
* Julian Brackins
*
* CSC 372
*/

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <iomanip>
#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <fstream>
#include <ctime>
#include <algorithm>


using namespace std;

struct word
{
    int64_t number;
    long double val;
    string word;
    string word_30;
};

bool mysort( const word &a, const word &b ){ return( a.val < b.val ); }

int64_t charTo64bitNum(string a);
void read_strings( vector<word> &words, ifstream& fin );
time_t bucket_sort( vector<word> &words, ofstream& fout );
void insertion_sort( vector<word> &list );

int main()
{
    vector<word> words;
    int i;
    const char *temp;
    ifstream fin;
    ofstream fout;
    time_t start, finish;
    float total = 0;
    string tempstr;
    word tempword;


    while (true)
    {
    cin >> tempstr;
    if (cin . fail())
      break;
    tempword.word = tempstr;
    words.push_back( tempword );
    }

    for( i = 0; i < words.size(); i++ )
    {
        words[i].number = 0;

        tempstr = words[i].word;

        if(tempstr.size() < 8)
            tempstr.resize(8, 'a');
        else
            tempstr.resize(8);

        temp = tempstr.c_str();

        words[i].number = charTo64bitNum(temp);
        words[i].val = (words[i].number) / pow(2, 64) / 18 * 100 - 2;
    }
    sort( words.begin(), words.end(), mysort );

    for( i = 0; i < words.size(); i++ )
    {
        cout << words[i].word << endl;
    }

    return 0;
}

int64_t charTo64bitNum(string a)
{
    int64_t n = 0;

    n = ((int64_t(a[0]) << 56) & 0xFF00000000000000U)
     | ((int64_t(a[1]) << 48) & 0x00FF000000000000U)
     | ((int64_t(a[2]) << 40) & 0x0000FF0000000000U)
     | ((int64_t(a[3]) << 32) & 0x000000FF00000000U)
     | ((a[4] << 24) & 0x00000000FF000000U)
     | ((a[5] << 16) & 0x0000000000FF0000U)
     | ((a[6] <<  8) & 0x000000000000FF00U)
     | ( a[7]        & 0x00000000000000FFU);

    return n;

}

void read_strings( vector<word> &words, ifstream& fin )
{
    string tempstr;
    word tempword;

    while( fin >> tempstr )
    {
        tempword.word = tempstr;
        words.push_back( tempword );
    }
}
