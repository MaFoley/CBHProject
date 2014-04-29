#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include "Person.h"
#include "PersonFile.h"
using namespace std;
void PrintHeading7();
string UserWait();
void option7()
{
    PersonFile * pPersonFile = new PersonFile;
    Person aPerson;
    int i;
    string test;

    system("clear");
    PrintHeading7();
    for(i = 1; i <= pPersonFile->GetNumberPersons();i++)
    {
        aPerson = pPersonFile->SearchByRecordNumber(i);
        aPerson.PrintPerson();
        if(i % 5 == 0)
        {
            test = UserWait();
            if(test[0] == 'q' || test[0] =='Q') break;
            system("clear");
            PrintHeading7();
        }
    }
    if(i >= pPersonFile->GetNumberPersons()) 
        UserWait();
    
    delete pPersonFile;
}

 
void PrintHeading7()
{   
    int centerOffset;
    char buffer[80];
    string heading;
    string Row1Heading;
    string Row2Heading;
    string Row3Heading;
    string Row4Heading;

    heading = "Police Information System Print Report Sub Menu";
    memset(buffer, '*', sizeof(buffer));

    centerOffset = (sizeof(buffer) - heading.length())/2;
    strncpy(buffer + centerOffset, heading.c_str(), heading.length());

    cout.write(buffer, sizeof(buffer));
    cout << endl;

                 //0         1         2         3         4         5         6         7         8
                 //012345678901234567890123456789012345678901234567890123456789012345678901234567890
    Row1Heading = "============================Displaying Master Report================================";
    Row2Heading = "SSN         FULL NAME                          OLN           STATE  COUNTY      ";
    Row3Heading = "            ADDRESS                        CITY                     ZIPCODE     ";
    Row4Heading = "====================================================================================";
    cout << "\n";
    cout <<Row1Heading << endl;
    cout <<Row2Heading << endl;
    cout <<Row3Heading << endl;
    cout <<Row4Heading << endl;

}
