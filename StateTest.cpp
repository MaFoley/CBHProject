#include <iostream>
#include "State.h"
using namespace std;


int main()
{
    State * pStateObj;
    pStateObj = new State;
    cout << "Min code: " << pStateObj -> GetMinCode() << endl;
    cout << "Max code: " << pStateObj -> GetMaxCode() << endl;
    cout << "Record Length: " << pStateObj -> GetRecordLength() << endl;
    cout << "Number of States: " <<pStateObj -> GetNumberStates() << endl;
    cout << "All of it!!!!!\n" << pStateObj -> GetStates() << endl;

    delete pStateObj;
    return 0;
}
