#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
using namespace std;

void option1();
void option4();
void option5();
void option6();
void option7();

string UserWait();
void PrintMenu();
void DisplayRecord(const int LookupType);

int main ()
{
    const int SSNLOOK = 2;
    const int OLNLOOK = 3;
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
                DisplayRecord(SSNLOOK);
                break;
            case '3':
                DisplayRecord(OLNLOOK);
                break;
            case '4':
                option4();
                break;
            case '5':
                option5();
                break;
            case '6':
                option6();
                break;
            case '7':
                option7();
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
    int centerOffset;
    char buffer[80];
    string heading;

    heading = "Police Information System Main Menu";
    memset(buffer, '*', sizeof(buffer));

    centerOffset = (sizeof(buffer) - heading.length())/2;
    strncpy(buffer + centerOffset, heading.c_str(), heading.length());

    //Print header
    system("clear");
    cout.write(buffer, sizeof(buffer));
    cout << endl;
    cout << "\n";
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

