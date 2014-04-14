#include <iostream>
#include <string>

using namespace std;

string UserWait()
{
    string userInput;
    cout << "\n\t\t\tPress enter to continue...";
    getline(cin, userInput);
    cin.sync();
    return userInput;
}
