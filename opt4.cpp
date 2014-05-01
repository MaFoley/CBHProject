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
#include "VMake.h"
#include "VType.h"

using namespace std;
void PrintHeading4();
void PrintMenuUpdate();
void UserInputVehicle(Person & aPerson, Vehicle & aVehicle);
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
    VehicleFile * pVehicleFile = new VehicleFile;
    Vehicle * pVehicle = new Vehicle;
    State * pState = new State;
    County * pCounty = new County;
    VMake * pVMake = new VMake;
    Color * pColor = new Color;
    VType * pVType = new VType;

    while(true)
    {

        PrintHeading4();
        getline(cin,inSSN);
        cin.sync();
        if(inSSN[0] == 'q' || inSSN[0] == 'Q') break;
        *pPerson = pPersonFile->SearchBySSN(inSSN);

        //Ensuring that the Record does not alrady exist
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
        pPerson->SetSSN(Trim(inSSN));

        cout << "\n\n\t\tEnter new OLN           : ";
        getline(cin, inData);
        cin.sync();
        pPerson->SetOLN(Trim(inData));

        cout << "\n\n\t\tEnter new Last Name     : ";
        getline(cin, inData);
        cin.sync();
        pPerson->SetLastName(Trim(inData));

        cout << "\n\n\t\tEnter new First Name    : ";
        getline(cin, inData);
        cin.sync();
        pPerson->SetFirstName(Trim(inData));

        cout << "\n\n\t\tEnter new Middle Initial: ";
        getline(cin, inData);
        cin.sync();
        pPerson->SetMI(Trim(inData));

        cout << "\n\n\t\tEnter new Street Address: ";
        getline(cin, inData);
        cin.sync();
        pPerson->SetStreet(Trim(inData));

        cout << "\n\n\t\tEnter new City          : ";
        getline(cin, inData);
        cin.sync();
        pPerson->SetCity(Trim(inData));

        system("clear");
        cout << "\n\t\tNow Displaying Codes for: State";
        pState->DisplayStates();
        cout << "\n\n\t\tEnter State Code        : ";
        getline(cin, inData);
        cin.sync();
        pPerson->SetStateCode(Trim(inData));

        //Only prompts for County if State is Alabama
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

        cout << "\n\n\t\tEnter new Zip Code      : ";
        getline(cin, inData);
        cin.sync();
        //Like SSN, the Set takes care of removing hyphens
        pPerson->SetZip(Trim(inData));

        system("clear");
        pPerson->DisplayPerson();
        cout << "\n\t\tAdd Vehicle for this Record? (Y/N): " << flush;
        getline(cin, choice);
        cin.sync();



        //Everything in this if block is Populating the Vehicle Record
        if(choice[0] == 'y' || choice[0] =='Y')
        {
            UserInputVehicle(*pPerson, *pVehicle);
        }



        system("clear");
        pPerson->DisplayPerson();
        pVehicle->DisplayVehicle();
        cout << "\n\t\tCommit Record to File? (Y/N): " << flush;
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
        pVehicleFile->AddVehicle(*pVehicle);
        cout << "\n\t\tRecord Committed to File." << endl;
        test = UserWait();
        if(test[0] == 'q' || test[0] =='Q')
            break;
    }

    delete pPerson;
    delete pPersonFile;
    delete pVehicle;
    delete pVehicleFile;
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

void UserInputVehicle(Person & aPerson, Vehicle & aVehicle)
{
    string inData;

    VMake * pVMake = new VMake;
    Color * pColor = new Color;
    VType * pVType = new VType;
    aVehicle.SetSSN(aPerson.GetSSN());

    //Setting these ensures display will behave
    aVehicle.SetFound(true);
    aVehicle.SetDeleted(false);

    //Works much the same as Populating the Person class members
    cout << "\n\n\t\tEnter new TAG           : ";
    getline(cin, inData);
    cin.sync();
    aVehicle.SetTag(Trim(inData));
 
    system("clear");
    cout << "\n\t\tNow Displaying Codes for:  VMake";
    pVMake->DisplayVMakes();
    cout << "\n\n\t\tEnter  VMake Code       : ";
    getline(cin, inData);
    cin.sync();
    aVehicle.SetVMakeCode(Trim(inData));

    system("clear");
    cout << "\n\t\tNow Displaying Codes for:  VType";
    pVType->DisplayVTypes();
    cout << "\n\n\t\tEnter  VType Code       : ";
    getline(cin, inData);
    cin.sync();
    aVehicle.SetVTypeCode(Trim(inData));

    system("clear");
    cout << "\n\t\tNow Displaying Codes for: Top Color";
    pColor->DisplayColors();
    cout << "\n\n\t\tEnter Top Color Code    : ";
    getline(cin, inData);
    cin.sync();
    aVehicle.SetTopColorCode(Trim(inData));

    system("clear");
    cout << "\n\t\tNow Displaying Codes for: Bottom Color";
    pColor->DisplayColors();
    cout << "\n\n\t\tEnter Bottom Color Code : ";
    getline(cin, inData);
    cin.sync();
    aVehicle.SetBottomColorCode(Trim(inData));


    delete pVMake;
    delete pVType;
    delete pColor;

}
