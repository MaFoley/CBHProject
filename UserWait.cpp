#include <iostream>
#include <string>

using namespace std;

string UserWait()
{
    string userInput;
    cout << "\n\t\t\tPress enter to continue. (Q) to quit...";
    getline(cin, userInput);
    cin.sync();
    return userInput;
}
