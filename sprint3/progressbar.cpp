#include <stdio.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include <ctime>

using namespace std;

//PARAMETERS: ./progbar <#_seconds_to_run_test> <program_pid> <program_name>
int main(int argc, char* argv[])
{

    //Initialize default parameters
    int runtime = 60;           //argv1
    int kill_pid = -123;        //argv2
    string progname("program"); //argv3

    //Initializations
    float next = 0.05;
    int remaining = 0;
    string progbar("");
    int time = 0;


    //Argument check and assignments
    if (argc < 2)
    {
        cout << "Running progbar in stand-alone mode...";
        cout << "Default parameters in use." << endl;
    }
    
    if ( argc > 1 )
        int runtime = atoi(argv[1]);
    if ( argc > 2 )
        kill_pid = atoi(argv[2]);
    if ( argc > 3 )
        progname = argv[3];

    //set header
    printf("\nTesting %s for %d seconds...\n", progname.c_str(), runtime);
    printf("\n\n\n");

    cout.flush();

    while(time < runtime + 1)
    {   
        /*Return two spaces
          Print Elapsed Time
          Print Remaining Time
          Flush to stdio
          Update progress bar if needed
          Sleep for 1 second*/
        
        remaining = runtime - time;
        printf("\033[F\033[F");
        printf("Elapsed   Time: %d       \n",time);
        printf("Remaining Time: %d       \n",remaining);
        cout.flush();
        printf("[                    ]");
        printf("\r[");
        
        //increment time
        time++;
        
        //update progress bar based on %time remaining
        while( ((float)time / (float)runtime) >= next && next <= 1.00)
        {
            progbar += "=";
            next += 0.05;
        }
        cout << progbar;
        cout.flush();
        if (time < runtime + 1)
            sleep(1);
    }
    cout << endl;
    printf("\033[F[====================]         \n");

    if( kill_pid > 0 )      //This will be < 0 if in standalone mode
        kill(kill_pid, 9);
    return 0;
}
