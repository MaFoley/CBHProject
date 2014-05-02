#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include "Person.h"
#include "PersonFile.h"
#include "Vehicle.h"
#include "VehicleFile.h"
using namespace std;
void PrintHeading7();
string UserWait();
void option7()
{
    PersonFile * pPersonFile = new PersonFile;
    Person aPerson;
    VehicleFile * pVehicleFile = new VehicleFile;
    Vehicle aVehicle;
    const int RECPERPAGE = 5;
    int i;
    int PersonsOnPage;
    int PersonsPrinted;
    string test;

    system("clear");
    PrintHeading7();
    //PersonsOnPage is required to prevent a bug where deleted records would prevent
    //a display of any records occuring before a pause
    PersonsOnPage= 0;
    PersonsPrinted = 0;
    for(i = 1; i <= pPersonFile->GetNumberPersons();i++)
    {
        aPerson = pPersonFile->SearchByRecordNumber(i);
        aPerson.PrintPerson();
        if(aPerson.IsFound() && !aPerson.IsDeleted())
        {
            PersonsPrinted++;
            PersonsOnPage++;
            aVehicle = pVehicleFile->SearchBySSN(aPerson.GetSSN());
            aVehicle.PrintVehicle();
        }
        if(PersonsPrinted % RECPERPAGE == 0 && PersonsOnPage != 0)
        {
            cout << "====================================================================================" << endl;
            test = UserWait();
            if(test[0] == 'q' || test[0] =='Q') break;
            system("clear");
            PrintHeading7();
            PersonsOnPage = 0;
        }
    }
    if(i >= pPersonFile->GetNumberPersons() && PersonsPrinted % RECPERPAGE != 0) 
        UserWait();
    
    delete pPersonFile;
    delete pVehicleFile;
}

 
void PrintHeading7()
{   
    int centerOffset;
    char buffer[80];
    string heading;
    string RowHeading[] = {
     //0         1         2         3         4         5         6         7         8
     //012345678901234567890123456789012345678901234567890123456789012345678901234567890
     "============================Displaying Master Report================================",
     "SSN         FULL NAME                          OLN           STATE  COUNTY      ",
     "            ADDRESS                        CITY                     ZIPCODE     ",
     "    TAG     VMAKE                      VTYPE                 TOP CLR   BTM COLOR",
     "===================================================================================="
     //012345678901234567890123456789012345678901234567890123456789012345678901234567890
     //0         1         2         3         4         5         6         7         8
    };

    heading = "Police Information System Print Report Sub Menu";
    memset(buffer, '*', sizeof(buffer));

    centerOffset = (sizeof(buffer) - heading.length())/2;
    strncpy(buffer + centerOffset, heading.c_str(), heading.length());

    cout.write(buffer, sizeof(buffer));
    cout << endl;
/*
                 //0         1         2         3         4         5         6         7         8
                 //012345678901234567890123456789012345678901234567890123456789012345678901234567890
    Row1Heading = "============================Displaying Master Report================================";
    Row2Heading = "SSN         FULL NAME                          OLN           STATE  COUNTY      ";
    Row3Heading = "            ADDRESS                        CITY                     ZIPCODE     ";
    Row4Heading = "    TAG     VMAKE                      VTYPE                 TOP CLR   BTM COLOR";
    Row5Heading = "====================================================================================";
                 //012345678901234567890123456789012345678901234567890123456789012345678901234567890
                 //0         1         2         3         4         5         6         7         8
*/
    cout << "\n";
    for(int i = 0; i < 5; i++)
        cout << RowHeading[i] << endl;

}
