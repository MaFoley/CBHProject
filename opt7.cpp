#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include "Person.h"
#include "PersonFile.h"
using namespace std;
PrintHeading7();
void option7()
{
    PersonFile * pPersonFile = new PersonFile;
    Person aPerson;
    system("clear")
    PrintHeading7();
}

 
void PrintHeading7()
{   
    int centerOffset;
    char buffer[80];
    string heading;

    heading = "Police Information System Print Report Sub Menu";
    memset(buffer, '*', sizeof(buffer));

    centerOffset = (sizeof(buffer) - heading.length())/2;
    strncpy(buffer + centerOffset, heading.c_str(), heading.length());

            //0         1         2         3         4         5         6         7         8
            //012345678901234567890123456789012345678901234567890123456789012345678901234567890
    buffer = " 
    

}
