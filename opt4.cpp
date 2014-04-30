#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include "Person.h"
#include "PersonFile.h"
#include "State.h"
#include "County.h"

using namespace std;
void PrintHeading4();
void PrintMenuUpdate();
string UserWait();
string Trim(string aString);
string SSNHyphens(const string & aSSN);

void option4()
{
    string inSSN;
    string choice;
    string test;
    string inData;
    PersonFile * pPersonFile = new PersonFile;
    Person * pPerson = new Person;
    State * pState = new State;
    County * pCounty = new County;

    while(true)
    {

        PrintHeading4();
        getline(cin,inData);
        cin.sync();
        if(inData[0] == 'q' || inData[0] == 'Q') break;
        *pPerson = pPersonFile->SearchBySSN(inData);
        if(pPerson->IsFound() == true)
        {
            cout << "\n\t\t\tRecord for SSN: " << SSNHyphens(inSSN) << " already exists." << endl;
            test = UserWait();
            if(test[0] == 'q' || test[0] =='Q')
                break;         
            
            continue;
        }
        //This Block only runs if the SSN was not found in the file
        //SetFound is run so the Person can be displayed as they are updated
        pPerson->SetFound(true);
        pPerson->SetSSN(Trim(inData));
        pPerson->DisplayPerson();

        cout << "\n\n\t\tEnter new OLN           : ";
        getline(cin, inData);
        cin.sync();
        pPerson->SetOLN(Trim(inData));

        system("clear");
        pPerson->DisplayPerson();
        cout << "\n\n\t\tEnter new Last Name     : ";
        getline(cin, inData);
        cin.sync();
        pPerson->SetLastName(Trim(inData));

        cout << "\n\n\t\tEnter new First Name    : ";
        getline(cin, inData);
        cin.sync();

        system("clear");
        pPerson->SetFirstName(Trim(inData));
        cout << "\n\n\t\tEnter new Middle Initial: ";
        getline(cin, inData);
        cin.sync();
        pPerson->SetMI(Trim(inData));
        pPerson->DisplayPerson();

        cout << "\n\n\t\tEnter new Street Address: ";
        getline(cin, inData);
        cin.sync();
        pPerson->SetStreet(Trim(inData));

        system("clear");
        pPerson->DisplayPerson();
        cout << "\n\n\t\tEnter new City          : ";
        getline(cin, inData);
        cin.sync();
        pPerson->SetCity(Trim(inData));

        system("clear");
        pPerson->DisplayPerson();

        system("clear");
        cout << "\n\t\tNow Displaying Codes for: State";
        pState->DisplayStates();
        cout << "\n\n\t\tEnter State Code        : ";
        getline(cin, inData);
        cin.sync();
        pPerson->SetStateCode(Trim(inData));
        system("clear");
        pPerson->DisplayPerson();
        if(pPerson->GetStateCode() != "02")
        {
            pPerson->SetCountyCode("00");
        }
        else
        {
            system("clear");
            cout << "\n\t\tNow Displaying Codes for: County";
            pCounty->DisplayCounties();
            cout << "\n\n\t\tEnter County Code       : ";
            getline(cin, inData);
            cin.sync();
            pPerson->SetCountyCode(Trim(inData));
        } 
        system("clear");
        pPerson->DisplayPerson();

        cout << "\n\n\t\tEnter new Zip Code      : ";
        getline(cin, inData);
        cin.sync();
        //Like SSN, the Set takes care of removing hyphens
        pPerson->SetZip(Trim(inData));

        system("clear");
        pPerson->DisplayPerson();
        cout << "\t\tCommit Record to File? (Y/N): " << flush;
        getline(cin, choice);
        cin.sync();
        if(choice[0] != 'y' && choice[0] !='Y')
        {
            cout << "\n\t\tRecord not Committed to File. " << endl;
            test = UserWait();
            if(test[0] == 'q' || test[0] =='Q')
                break;         
            continue;         
        }

        pPersonFile->AddPerson(*pPerson);
        cout << "\n\t\tRecord Committed to File." << endl;
        UserWait();
       
    }

    delete pPerson;
    delete pPersonFile;
    delete pState;
    delete pCounty;
}

void PrintHeading4()
{
    char buffer[80];
    int centerOffset;
    system("clear");
    //Print header
    string heading;
    heading = "Police Information System Add New Record Sub Menu";
    memset(buffer, '*', sizeof(buffer));

    centerOffset = (sizeof(buffer) - heading.length())/2;
    strncpy(buffer + centerOffset, heading.c_str(), heading.length());
    cout.write(buffer, sizeof(buffer));
    cout << endl;
    cout << "\n\t\tEnter SSN of Record to Add (Q to quit): ";
}
