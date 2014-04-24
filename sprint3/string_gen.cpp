#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <fstream>


using namespace std;

void gen_random(char *s, const int len) {
    static const char alpha[] = "abcdefghijklmnopqrstuvwxyz1234567890";

    for (int i = 0; i < len; ++i) {
        s[i] = alpha[rand() % (sizeof(alpha) - 1)];
    }

    s[len] = 0;
}

int main()
{
    char * string;
    int length = 0, stringsToGen, maxLen;
    srand (time(NULL));
    ofstream rand_out;
    rand_out.open ("strings.tst");
    if (!rand_out)
    {
        cout << "UGH" << endl;
        return 0;
    }

    cout << "How many strings would you like to generate?" << endl;
    cin >> stringsToGen;
    
    cout << "What is the max length for a string?" << endl;
    cin >> maxLen;

    for( long int i = 0; i < stringsToGen; i++ )
    {
        length = rand() % maxLen + 1;
        //cout << length << endl;
        gen_random(string, length);

        rand_out << string << endl;
        //length ++;
    }
    rand_out.close();
    return 0;
}

