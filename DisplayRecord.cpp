#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include "Person.h"
#include "PersonFile.h"

using namespace std;
void PrintHeading2(const int LookupFlag);
string UserWait();
string SSNHyphens(const string & aString);

const int SSNLOOKUP = 2;//ie the option number
const int OLNLOOKUP = 3;

void DisplayRecord(const int LookupFlag)
{
    string inData;
    string test;
    PersonFile * pPersonFile = new PersonFile;
    Person * pPerson = new Person;

    while(true)
    {

        PrintHeading2(LookupFlag);
        getline(cin, inData);
        cin.sync();
        if(inData[0] == 'q' || inData[0] == 'Q') break;
        //the Search method sanitizes the hyphens
        if(LookupFlag == SSNLOOKUP)
            *pPerson = pPersonFile->SearchBySSN(inData);
        else
            *pPerson = pPersonFile->SearchByOLN(inData);
        cout << "\n";
        pPerson->DisplayPerson();
        if(pPerson->IsFound() == false || pPerson->IsDeleted())
        {
            if(LookupFlag == SSNLOOKUP)
                cout << "\t\t\tRecord for SSN: " << SSNHyphens(inData) << " not found." << endl;
            else
                cout << "\t\t\tRecord for OLN: " <<inData << " not found." << endl;
        }
        test = UserWait();
        if(test[0] == 'q' || test[0] == 'Q') break;
    }

    delete pPerson;
    delete pPersonFile;
}
void PrintHeading2(const int LookupFlag)
{
    system("clear");
    //Print header
    char buffer[80];
    string heading;
    if(LookupFlag == SSNLOOKUP)
        heading = "Police Information System Search by SSN Sub Menu";
    if(LookupFlag == OLNLOOKUP)
        heading = "Police Information System Search by OLN Sub Menu";
    memset(buffer, '*', sizeof(buffer));

    strncpy(buffer + 16, heading.c_str(), heading.length());
    cout.write(buffer, sizeof(buffer));
    cout << endl;
    if(LookupFlag == SSNLOOKUP)
        cout << "\n\t\t\tEnter SSN of Record to Display (Q to quit): ";
    if(LookupFlag == OLNLOOKUP)
        cout << "\n\t\t\tEnter OLN of Record to Display (Q to quit): ";
}
