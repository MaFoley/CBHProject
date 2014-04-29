#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include "Person.h"
#include "PersonFile.h"

using namespace std;
void PrintHeading2();
string UserWait();
string SSNHyphens(const string & aString);

void option2()
{
    string inSSN;
    string test;
    PersonFile * pPersonFile = new PersonFile;
    Person * pPerson = new Person;

    while(true)
    {

        PrintHeading2();
        getline(cin, inSSN);
        if(inSSN[0] == 'q' || inSSN[0] == 'Q') break;
        //the Search method sanitizes the hyphens
        *pPerson = pPersonFile->SearchBySSN(inSSN);
        cout << "\n";
        pPerson->DisplayPerson();
        if(pPerson->IsFound() == false || pPerson->IsDeleted())
            cout << "\t\t\tRecord for SSN: " << SSNHyphens(inSSN) << " not found." << endl;
        test = UserWait();
        if(test[0] == 'q' || test[0] == 'Q') break;
    }

    delete pPerson;
    delete pPersonFile;
}
void PrintHeading2()
{
    system("clear");
    //Print header
    char buffer[80];
    string heading;
    heading = "Police Information System Search by SSN Sub Menu";
    memset(buffer, '*', sizeof(buffer));

    strncpy(buffer + 16, heading.c_str(), heading.length());
    cout.write(buffer, sizeof(buffer));
    cout << endl;
    cout << "\n\t\t\tEnter SSN of Record to Display (Q to quit): ";
}
