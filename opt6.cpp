#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include "Person.h"
#include "PersonFile.h"
#include "State.h"
#include "County.h"

using namespace std;
void PrintHeading6();
void PrintMenuUpdate();
string UserWait();
string Trim(string aString);

void option6()
{
    string inSSN;
    string choice;
    string test;
    int intChoice;
    string inData;
    PersonFile * pPersonFile = new PersonFile;
    Person * pPerson = new Person;
    State * pState = new State;
    County * pCounty = new County;

    while(true)
    {

        PrintHeading6();
        getline(cin, inSSN);
        if(inSSN[0] == 'q' || inSSN[0] == 'Q') break;
        //the Search method sanitizes the hyphens
        *pPerson = pPersonFile->SearchBySSN(inSSN);
        while(true)
        {
            if(pPerson->IsFound() == false || pPerson->IsDeleted())
            {
                cout << "\n\t\t\tRecord for SSN: " << SSNHyphens(inSSN) << " not found." << endl;
                break;
            }

            system("clear");
            cout << "\n\t\tDisplaying Record to Be Updated\n";

            pPerson->DisplayPerson();
            PrintMenuUpdate();
            getline(cin, choice);
            if(choice[0] == 'c' || choice[0] == 'C')
            {
                cout << "Changes to Record not Saved." << endl;
                UserWait();
                break;
            }
            if(choice[0] == 's' || choice[0] == 'S')
            {
                pPersonFile->UpdatePerson(*pPerson);
                pPersonFile->SortBySSN();
                cout << "Changes to Record Committed to File." << endl;
                UserWait();
                break;
            }
            intChoice = atoi(choice.c_str());
            switch(intChoice)
            {
                case 1:
                    cout << "\n\n\t\tEnter new SSN: ";
                    getline(cin,inData);
                    pPerson->SetSSN(Trim(inData));
                   break;
                case 2:
                    cout << "\n\n\t\tEnter new Last Name: ";
                    getline(cin, inData);
                    pPerson->SetLastName(Trim(inData));
                    break;
                case 3:
                    cout << "\n\n\t\tEnter new First Name: ";
                    getline(cin, inData);
                    pPerson->SetFirstName(Trim(inData));
                    break;
                case 4:
                    cout << "\n\n\t\tEnter new Middle Initial: ";
                    getline(cin, inData);
                    pPerson->SetMI(Trim(inData));
                    break;
                case 5:
                    cout << "\n\n\t\tEnter new Street Address: ";
                    getline(cin, inData);
                    pPerson->SetStreet(Trim(inData));
                    break;
                case 6:
                    cout << "\n\n\t\tEnter new City: ";
                    getline(cin, inData);
                    pPerson->SetCity(Trim(inData));
                    break;
                case 7:
                    cout << "\n\n\t\tEnter new OLN: ";
                    getline(cin, inData);
                    pPerson->SetOLN(Trim(inData));
                    break;
                case 8:
                    system("clear");
                    cout << "\n\t\tNow Displaying Codes for: State";
                    pState->DisplayStates();
                    cout << "\n\n\t\tEnter State Code: ";
                    getline(cin, inData);
                    pPerson->SetStateCode(Trim(inData));
                    break;   
                case 9:
                    system("clear");
                    cout << "\n\t\tNow Displaying Codes for: County";
                    pCounty->DisplayCounties();
                    cout << "\n\n\t\tEnter State Code: ";
                    getline(cin, inData);
                    pPerson->SetCountyCode(Trim(inData));
                    break;
                case 10:
                    cout << "\n\n\t\tEnter new Zip Code: ";
                    getline(cin, inData);
                    pPerson->SetZip(Trim(inData));
                    break;
                default:
                    cout << "Invalid Selection: " << intChoice << " not recognized." << endl;
                    break;
            }   
        }
    }

    delete pPerson;
    delete pPersonFile;
    delete pState;
    delete pCounty;
}
void PrintMenuUpdate()
{
    cout << "\n\t\t*************************************";
    cout << "\n\t\t(01) SSN             (07) OLN       ";
    cout << "\n\t\t(02) Last Name       (08) State     ";
    cout << "\n\t\t(03) First Name      (09) County    ";
    cout << "\n\t\t(04) Middle Initial  (10) Zip Code  ";
    cout << "\n\t\t(05) Street Address                 ";
    cout << "\n\t\t(06) City                           ";
    cout << "\n\t\t=====================================";
    cout << "\n\t\t(11) TAG             (14) V Make    ";
    cout << "\n\t\t(C) Cancel Changes   (S) Save to File";
    cout << "\n\t\t*************************************";
    cout << "\n\n\t\tEnter Number of Field to Update: " << flush;

    //SSN. OLN, State, County, LName, FName, MI, Street, City, Zip
}
    
void PrintHeading6()
{
    char buffer[80];
    int centerOffset;
    system("clear");
    //Print header
    string heading;
    heading = "Police Information System Update Existing Record Sub Menu";
    memset(buffer, '*', sizeof(buffer));

    centerOffset = (sizeof(buffer) - heading.length())/2;
    strncpy(buffer + centerOffset, heading.c_str(), heading.length());
    cout.write(buffer, sizeof(buffer));
    cout << endl;
    cout << "\n\t\tEnter SSN of Record to Be Updated (Q to quit): ";
}
