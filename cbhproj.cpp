#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

void option1();
void option2();
void option3();
void option4();
void option5();
void option6();
void option7();

string UserWait();
void PrintMenu();

int main ()
{
    bool continueLoop = true;
    string opt;
    while(continueLoop)
    {
        PrintMenu();
        getline(cin, opt);
        cin.sync();

        switch(opt[0])
        {
            case '1':
                option1();
                break;
            case '2':
                option2();
                UserWait();
                break;
            case '3':
                option3();
                UserWait();
                break;
            case '4':
                option4();
                UserWait();
                break;
            case '5':
                option5();
                UserWait();
                break;
            case '6':
                option6();
                UserWait();
                break;
            case '7':
                option7();
                UserWait();
                break;
            case 'q':
            case 'Q':
                continueLoop = false;
                cout << "Exit CBH Project\n";
                    break;
            default:
                cout << "\n\t\t\tInvalid Selection. You entered: " << opt << "\n";
                cout << "\t\t\tPlease select (1-7) or q\n";
                UserWait();
                break;
        }
    }
    return 0;
}

void PrintMenu()
{
    system("clear");
    //Print header
    cout.fill('*');
    cout.width(16);
    cout << '*';
    cout << "Police Information System Main Menu";
    cout.fill('*');
    cout.width(29);
    cout << '*';
    cout << "\n\n";
    //Print Selection choices
    cout << "\t\t\t(1) - Display Adjunct Files\n";
    cout << "\t\t\t(2) - Display Record (Search by SSN)\n";
    cout << "\t\t\t(3) - Display Record (Search by OLN)\n";
    cout << "\t\t\t(4) - Add Record\n";
    cout << "\t\t\t(5) - Delete Existing Record\n";
    cout << "\t\t\t(6) - Modify Existing Record\n";
    cout << "\t\t\t(7) - List Master File\n";
    cout << "\t\t\t(Q) - Exit Database\n\n";

    cout.fill('*');
    cout.width(80);
    cout << '*';
    cout <<"\n\n\t\t\tEnter a Selection: ";
}
