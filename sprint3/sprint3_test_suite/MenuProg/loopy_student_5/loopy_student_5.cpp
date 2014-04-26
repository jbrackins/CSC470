#include <stdio.h>
#include <stdio.h>
#include <iostream>
using namespace std;
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include<signal.h>

#include <ctime>

#define NEVER -100
int main()
{
    int t = 0;
    printf("Infinite loop...\n");
    
    while(1)
    {
        t++;
        //begin = end;
        printf("%d",t);
        cout.flush();
        for (int j = 0; j < 3; j++)
        {   
            sleep(1);
            printf(".");
            cout.flush();
        }
        sleep(1);
        cout.flush();
    }

    return NEVER;
}
