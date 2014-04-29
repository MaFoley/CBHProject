#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include "Person.h"
#include "PersonFile.h"

using namespace std;
void PrintHeading5();
string UserWait();

void option5()
{
    string inSSN;
    string choiceDelete;
    PersonFile * pPersonFile = new PersonFile;
    Person * pPerson = new Person;

    while(true)
    {

        PrintHeading5();
        getline(cin, inSSN);
        if(inSSN[0] == 'q' || inSSN[0] == 'Q') break;
        //the Search method sanitizes the hyphens
        *pPerson = pPersonFile->SearchBySSN(inSSN);
        pPerson->DisplayPerson();

        if(pPerson->IsDeleted() || pPerson->IsFound() == false)
        {
            UserWait();
            continue;
        }

        cout << "\n\t\tIs this the person you wish to delete? (Y/N): ";
        getline(cin, choiceDelete);
        if(choiceDelete[0] == 'Y' || choiceDelete[0] == 'y')
        {
            pPerson->SetDeleted(true);
            pPersonFile->UpdatePerson(*pPerson);//ie write them back to the file, as deleted
        }
        else
            cout << "\n\t\tRecord for SSN: " << pPerson->GetSSNWithHyphens() << 
                " not deleted." << endl;
        UserWait();
    }

    delete pPerson;
    delete pPersonFile;
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
