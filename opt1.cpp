#include <string>
#include <iostream>
#include <cstdlib>
#include "State.h"
#include "Color.h"
#include "County.h"
#include "VMake.h"
#include "VType.h"

using namespace std;

void PrintOpt1Menu();
void PrintAuxiliarySubHdg( string AuxName);
string  UserWait();


void option1()
{
    State * pState = new State;
    Color * pColor = new Color;
    County * pCounty = new County;
    VMake * pVMake = new VMake;
    VType * pVType = new VType;
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
                PrintAuxiliarySubHdg("Color");
                pColor ->DisplayColors();
                UserWait();
                break;
            case '2':
                PrintAuxiliarySubHdg("County");
                pCounty ->DisplayCounties();
                UserWait();
                break;
            case '3':
                PrintAuxiliarySubHdg("State");
                pState ->DisplayStates();
                UserWait();
                break;
            case '4':
                PrintAuxiliarySubHdg("VMake");
                pVMake ->DisplayVMakes();
                UserWait();
                break;
            case '5':
                PrintAuxiliarySubHdg("VType");
                pVType ->DisplayVTypes();
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

    delete pColor;
    delete pCounty;
    delete pState;
    delete pVMake;
    delete pVType;
}

void PrintOpt1Menu()
{
     system("clear");
    //Print header
    cout.fill('*');
    cout.width(10);
    cout << '*';
    cout << "Police Information System Display Auxiliary Files Sub Menu";
    cout.fill('*');
    cout.width(12);
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

void PrintAuxiliarySubHdg(string AuxName)
{
    system("clear");
    //Print header
    cout.fill('*');
    cout.width(10);
    cout << '*';
    cout << "Police Information System Display Auxiliary Files Sub Menu";
    cout.fill('*');
    cout.width(12);
    cout << '*';
    cout << "\n\n";
    cout << "\t\t\t Displaying Codes For: " << AuxName;
 }
