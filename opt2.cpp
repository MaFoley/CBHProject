#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>

using namespace std;
void PrintHeading();

void option2()
{
    PrintHeading();
}
void PrintHeading()
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
    cout << "\n";
}
