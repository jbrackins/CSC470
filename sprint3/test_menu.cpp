#include "test_menu.hpp"
using namespace std;


int main()
{
    read_spec_file();
    return 0;
}


void read_spec_file()
{
    struct menu_option option[25];
    int i, j, k = 0;

    int total_options = 0;
    ifstream input("my_prog.spec");
    string line[25];
    char * temp;
    bool loop;

    i = 0;

    while( getline( input, line[total_options] ) ) 
    {
        total_options++;
    }


    while( i < total_options ) 
    {
        option[i].number = strtok( (char*)line[i].c_str(), " ");
        loop = true;

        j = 0;
        do
        {
            temp = strtok(NULL, " ");
            if(temp != NULL )
                option[i].type[j] = temp;
            else
            {
                option[i].type[j] = "";
                loop = false;
            }
            j++;
        }while(loop);
        option[i].args = j-1;  
        i++;
    }


    srand(time(NULL));
    int x = 0;
    //Minimum generation
    for(x = 0; x < total_options+2; x++)
    {
        if (x != total_options) //ignore "exit" option
            option_generator(x, option, total_options);
    }

    //Extemporaneous Generation
    for(x = 0; x < 15; x++)
    {
        int r = (rand()%(total_options)+1);

        if (r != total_options) //ignore "exit" option
            option_generator(r, option, total_options);
        else
            x--;                //don't count if "exit" had generated
    }
    //Generate the "exit" option last
    option_generator(total_options, option, total_options);
}

void option_generator(int opt, struct menu_option option[], int arr_size)
{
    cout << opt << " ";
    for(int i = 0; i < arr_size; i++)
    {
        if(atoi(option[i].number) == opt)
        {
            for(int j = 0; j < option[i].args; j++)
            {
                double test_case_in = random_generator(option[i].type[j]);
                cout << test_case_in << " ";
                srand(test_case_in);
            }    
        }
    }
    cout << endl;
}


void find_spec_file()
{


}


double random_generator(string kind)
{
    double number = ((float)rand()/(float)(RAND_MAX)) * 2000;// / RAND_MAX;
    int inumber = rand() % 2000;
    if (kind == "int")
        return inumber;
    else
        return number;
    sleep(2);
}