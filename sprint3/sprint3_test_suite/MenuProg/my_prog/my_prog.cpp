#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

int getMenuChoice( );
int getNumTerms( );
int average();
int max();
double min();

/***************************************************************************//**
 * @author Hannah Carroll
 *
 * @par Description:
 * This is the beginning of the program.
 *
 * @param[] none
 *
 * @returns 0 program runs correctly
 *
 ******************************************************************************/
int main ()
{
    // initialize variables
    int choice = 0, numterms = 0;
    double x = 0.0, ans = 0.0, actual = 0.0;
    // starting message indicating purpose of program
    cout << "This program will approximate values for e^x, sin(x), and cos(x)";
    cout << " then compare these values to known values\n";
    // do while loop to display message until user chooses to quit program
    cout << fixed << setprecision(4);
    do
    {
        // run getMenuChocie function to get choice
        choice = getMenuChoice ( );
        // start if, else if, else to apply choice
        if ( choice == 1 )
        {
            average();
        }
        else if ( choice == 2 )
        {
            max();

        }
        else if ( choice == 3 )
        {
            min();
        }
        else if ( choice == 4 )
        {
            cout << "bye bye jojo" << endl;
        }
        else
        {
            choice = 0;
            cout << "Please enter a valid selection from the menu,\n";
        }
    } while ( choice != 4 );
    return 0;
}

/***************************************************************************//**
 * @author Hannah Carroll
 *
 * @par Description:
 * Prints menu and retrieves user's choice
 *
 * @param[] none
 *
 * @returns choice selected by the user
 *
 ******************************************************************************/
int getMenuChoice( )
{
    // intitializing variable
    int choice = 0;
    // output menu
    cout << "What would you like to work with\n1) avg of two ints\n2) max of 4 ints\n3) min of 3 doubles\n";
    cout << "4) Quit Program\n";
    // input the user's choice
    cin >> choice;
    return choice;
}

int average()
{
    int i1, i2;

    cout << "Enter 1st int: ";
    cin >> i1;
    cout << "Enter 2nt int: ";
    cin >> i2;

    int avg = (i1 + i2) / 2;

    cout << "avg is " << avg << endl;

    return avg;
}

int max()
{
    int i1, i2, i3, i4;
    cout << "Enter 1st int: ";
    cin >> i1;
    cout << "Enter 2nt int: ";
    cin >> i2;
    cout << "Enter 3rd int: ";
    cin >> i3;
    cout << "Enter 4th int: ";
    cin >> i4;

    int max = i1;
    if(max < i2)
        max = i2;
    if(max < i3)
        max = i3;
    if(max < i4)
        max = i4;

    cout << "max is " << max << endl;

    return max;
}

double min()
{
    double d1, d2, d3, d4;
    cout << "Enter 1st num: ";
    cin >> d1;
    cout << "Enter 2nt num: ";
    cin >> d2;
    cout << "Enter 3rd num: ";
    cin >> d3;
    cout << "Enter 4th num: ";
    cin >> d4;

    double min = d1;
    if(min > d2)
        min = d2;
    if(min > d3)
        min = d3;
    if(min > d4)
        min = d4;

    cout << "min is " << min << endl;

    return min;
}