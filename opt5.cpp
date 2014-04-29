#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include "Person.h"
#include "PersonFile.h"

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
            cout << "\n\t\tRecord for SSN: " << pPerson->GetSSNWithHyphens() << 
                " Deleted!" << endl;
            pPerson->SetDeleted(true);
            pPersonFile->UpdatePerson(*pPerson);//ie write them back to the file, as deleted
        }
        else
            cout << "\n\t\tRecord for SSN: " << pPerson->GetSSNWithHyphens() << 
                " not deleted." << endl;
        test = UserWait();
        if(test[0] == 'q' || test[0] == 'Q') break;
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
