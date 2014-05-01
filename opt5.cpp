#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include "Person.h"
#include "PersonFile.h"
#include "Vehicle.h"
#include "VehicleFile.h"

using namespace std;
void PrintHeading5();
string UserWait();
string SSNHyphens(const string & aSSN);

void option5()
{
    string inSSN;
    string test;
    string choiceDelete;
    PersonFile * pPersonFile = new PersonFile;
    Person * pPerson = new Person;
    VehicleFile * pVehicleFile = new VehicleFile;
    Vehicle * pVehicle = new Vehicle;

    while(true)
    {

        PrintHeading5();
        getline(cin, inSSN);
        if(inSSN[0] == 'q' || inSSN[0] == 'Q') break;
        //the Search method sanitizes the hyphens
        *pPerson = pPersonFile->SearchBySSN(inSSN);
        pPerson->DisplayPerson();
        if( pPerson->IsFound() || !pPerson->IsDeleted())
        {
            *pVehicle = pVehicleFile->SearchBySSN(pPerson->GetSSN());
            pVehicle->DisplayVehicle();
        }
        
        if(pPerson->IsDeleted() || pPerson->IsFound() == false)
        {
            cout << "\n\t\t\tRecord for SSN: " << SSNHyphens(inSSN) << " not found." << endl;
            test = UserWait();
            if(test[0] == 'q' || test[0] == 'Q') 
                break;

            continue;
        }

        cout << "\n\t\tIs this the person you wish to delete? (Y/N): ";
        getline(cin, choiceDelete);
        if(choiceDelete[0] == 'Y' || choiceDelete[0] == 'y')
        {
            //Vehicle is deleted first because this makes the logic of checking for its driver more straightforward
            if( pPerson->IsFound() || !pPerson->IsDeleted())
            {
                pVehicle->SetDeleted(true);
                pVehicleFile->UpdateVehicle(*pVehicle);//ie write them back to the file, as deleted
            }
            pPerson->SetDeleted(true);
            pPersonFile->UpdatePerson(*pPerson);//ie write them back to the file, as deleted

            cout << "\n\t\tRecord for SSN: " << pPerson->GetSSNWithHyphens() << 
                " Deleted!" << endl;
        }
        else
            cout << "\n\t\tRecord for SSN: " << pPerson->GetSSNWithHyphens() << 
                " not deleted." << endl;
        test = UserWait();
        if(test[0] == 'q' || test[0] == 'Q') break;
    }

    delete pPerson;
    delete pPersonFile;
    delete pVehicle;
    delete pVehicleFile;
}
void PrintHeading5()
{
    int centerOffset;
    char buffer[80];

    system("clear");
    //Print header
    string heading;
    heading = "Police Information System Delete Existing Record Sub Menu";
    memset(buffer, '*', sizeof(buffer));

    centerOffset = (sizeof(buffer) - heading.length())/2;
    strncpy(buffer + centerOffset, heading.c_str(), heading.length());
    cout.write(buffer, sizeof(buffer));
    cout << endl;
    cout << "\n\t\tEnter SSN of Record to Be Deleted (Q to quit): ";
}
