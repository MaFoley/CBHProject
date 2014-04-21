#include <string>
#include <iostream>
#include <cstdlib>
#include "State.h"

using namespace std;

void PrintOpt1Menu();
void UserWait();
void option1()
{
    bool continueLoop = true;
    string opt;
    while(continueLoop)
    {
        PrintOpt1Menu();
        getline(cin, opt);
        cin.sync();

           switch(opt[0])
           {
            case '1':
                UserWait();
                break;
            case '2':
                UserWait();
                break;
            case '3':
                UserWait();
                break;
            case '4':
                UserWait();
                break;
            case '5':
                UserWait();
                break;
            case 'q':
            case 'Q':
                continueLoop = false;
                cout << "Exit Display Auxiliary Files Sub Menu\n";
                    break;
            default:
                cout << "\n\t\t\tInvalid Selection. You entered: " << opt << "\n";
                cout << "\t\t\tPlease select (1-5) or q\n";
                UserWait();
                break;
           }
    }
}

void PrintOpt1Menu()
{
     system("clear");
    //Print header
    cout.fill('*');
    cout.width(16);
    cout << '*';
    cout << "Police Information System Display Auxiliary Files Sub Menu";
    cout.fill('*');
    cout.width(16);
    cout << '*';
    cout << "\n\n";
    //Print Selection choices
    cout << "\t\t\t(1) - Display Color Codes\n";
    cout << "\t\t\t(2) - Display County Codes\n";
    cout << "\t\t\t(3) - Display State Codes\n";
    cout << "\t\t\t(4) - Display Vehicle Make Codes\n";
    cout << "\t\t\t(5) - Display Vehicle Type Codes\n";
    cout << "\t\t\t(Q) - Exit to Main Menu\n";

    cout.fill('*');
    cout.width(80);
    cout << '*';
    cout <<"\n\n\t\t\tEnter a Selection: ";
}
