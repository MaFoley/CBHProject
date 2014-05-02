#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include "Person.h"
#include "PersonFile.h"
#include "Vehicle.h"
#include "VehicleFile.h"
#include "State.h"
#include "County.h"
#include "Color.h"
#include "VType.h"
#include "VMake.h"

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
    //thisPerson object is used to ensure an updated SSN doesn't already exist
    Person testUpdatePerson;

    PersonFile * pPersonFile = new PersonFile;
    Person * pPerson = new Person;
    VehicleFile * pVehicleFile = new VehicleFile;
    Vehicle * pVehicle = new Vehicle;
    State * pState = new State;
    County * pCounty = new County;
    Color * pColor = new Color;
    VType * pVType = new VType;
    VMake * pVMake = new VMake;

    while(true)
    {

        PrintHeading6();
        getline(cin, inSSN);
        cin.sync();
        if(inSSN[0] == 'q' || inSSN[0] == 'Q') break;
        //the Search method sanitizes the hyphens
        *pPerson = pPersonFile->SearchBySSN(inSSN);
        if(pPerson->IsFound() && !pPerson->IsDeleted())
            *pVehicle = pVehicleFile->SearchBySSN(pPerson->GetSSN());

        while(true)
        {
            if(pPerson->IsFound() == false || pPerson->IsDeleted())
            {
                cout << "\n\t\t\tRecord for SSN: " << SSNHyphens(inSSN) << " not found." << endl;
                UserWait();
                break;
            }

            system("clear");
            cout << "\n\t\tDisplaying Record to Be Updated\n";

            pPerson->DisplayPerson();
            pVehicle->DisplayVehicle();
            PrintMenuUpdate();
            getline(cin, choice);
            cin.sync();
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
                pVehicleFile->UpdateVehicle(*pVehicle);
                pVehicleFile->SortBySSN();
                cout << "\n\t\tChanges to Record Committed to File." << endl;
                UserWait();
                break;
            }
            intChoice = atoi(choice.c_str());
            switch(intChoice)
            {
                case 1:
                    cout << "\n\n\t\tEnter new SSN: ";
                    getline(cin,inData);
                    cin.sync();
                    testUpdatePerson = pPersonFile->SearchBySSN(inData);
                    if(testUpdatePerson.IsFound() || testUpdatePerson.IsDeleted())
                    {
                        cout << "\n\t\tSSN Already Exists in File. Change to SSN not saved." << endl;
                        UserWait();
                        break;
                    }
                    pPerson->SetSSN(Trim(inData));
                    pVehicle->SetSSN(pPerson->GetSSN());
                   break;
                case 2:
                    cout << "\n\n\t\tEnter new Last Name: ";
                    getline(cin, inData);
                    cin.sync();
                    pPerson->SetLastName(Trim(inData));
                    break;
                case 3:
                    cout << "\n\n\t\tEnter new First Name: ";
                    getline(cin, inData);
                    cin.sync();
                    pPerson->SetFirstName(Trim(inData));
                    break;
                case 4:
                    cout << "\n\n\t\tEnter new Middle Initial: ";
                    getline(cin, inData);
                    cin.sync();
                    pPerson->SetMI(Trim(inData));
                    break;
                case 5:
                    cout << "\n\n\t\tEnter new Street Address: ";
                    getline(cin, inData);
                    cin.sync();
                    pPerson->SetStreet(Trim(inData));
                    break;
                case 6:
                    cout << "\n\n\t\tEnter new City: ";
                    getline(cin, inData);
                    cin.sync();
                    pPerson->SetCity(Trim(inData));
                    break;
                case 7:
                    cout << "\n\n\t\tEnter new OLN: ";
                    getline(cin, inData);
                    cin.sync();
                    pPerson->SetOLN(Trim(inData));
                    break;
                case 8:
                    system("clear");
                    cout << "\n\t\tNow Displaying Codes for: State";
                    pState->DisplayStates();
                    cout << "\n\n\t\tEnter State Code: ";
                    getline(cin, inData);
                    cin.sync();
                    pPerson->SetStateCode(Trim(inData));
                    break;   
                case 9:
                    system("clear");
                    cout << "\n\t\tNow Displaying Codes for: County";
                    pCounty->DisplayCounties();
                    cout << "\n\n\t\tEnter County Code: ";
                    getline(cin, inData);
                    pPerson->SetCountyCode(Trim(inData));
                    break;
                case 10:
                    cout << "\n\n\t\tEnter new Zip Code: ";
                    getline(cin, inData);
                    cin.sync();
                    pPerson->SetZip(Trim(inData));
                    break;
                case 11:
                    system("clear");
                    cout << "\n\t\tNow Displaying Codes for: Top Color";
                    pColor->DisplayColors();
                    cout << "\n\n\t\tEnter new Top Color Code: ";
                    getline(cin, inData);
                    pVehicle->SetTopColorCode(Trim(inData));
                    break;
                case 12:
                    system("clear");
                    cout << "\n\t\tNow Displaying Codes for: Bottom Color";
                    pColor->DisplayColors();
                    cout << "\n\n\t\tEnter new Bottom Color Code: ";
                    getline(cin, inData);
                    pVehicle->SetBottomColorCode(Trim(inData));
                    break;
                case 13:
                    cout << "\n\n\t\tEnter new Tag: ";
                    getline(cin, inData);
                    cin.sync();
                    pVehicle->SetTag(Trim(inData));
                    break;
                case 14:
                    system("clear");
                    cout << "\n\t\tNow Displaying Codes for: Vehicle Make";
                    pVMake->DisplayVMakes();
                    cout << "\n\n\t\tEnter new Vehicle Make Code: ";
                    getline(cin, inData);
                    pVehicle->SetVMakeCode(Trim(inData));
                    break;
                case 15:
                    system("clear");
                    cout << "\n\t\tNow Displaying Codes for: Vehicle Type";
                    pVType->DisplayVTypes();
                    cout << "\n\n\t\tEnter new Vehicle Type: ";
                    getline(cin, inData);
                    pVehicle->SetVTypeCode(Trim(inData));
                    break;
                default:
                    cout << "Invalid Selection: " << intChoice << " not recognized." << endl;
                    break;
            }   
        }
    }

    delete pPerson;
    delete pPersonFile;
    delete pVehicle;
    delete pVehicleFile;
    delete pState;
    delete pCounty;
    delete pColor;
    delete pVType;
    delete pVMake;
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
    cout << "\n\t\t(11) Top Color       (14) V Make    ";
    cout << "\n\t\t(12) Bottom Color    (15) V Type    ";
    cout << "\n\t\t(13) Tag                            ";
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
