#include <iostream>
#include "State.h"
using namespace std;


int main()
{
    State * pStateObj;
    pStateObj = new State;
    /*
    cout << "Min code: " << pStateObj -> GetMinCode() << endl;
    cout << "Max code: " << pStateObj -> GetMaxCode() << endl;
    cout << "Record Length: " << pStateObj -> GetRecordLength() << endl;
    cout << "Number of States: " <<pStateObj -> GetNumberStates() << endl;
    cout << "All of it!!!!!\n" << pStateObj -> GetStates() << endl;
    cout << "GetStates: \n" << pStateObj -> GetState(1) << endl;
    cout << pStateObj -> GetState(2) << endl;
    cout << pStateObj -> GetState(51) << endl;
    */
    pStateObj -> DisplayStates();

    delete pStateObj;
    return 0;
}
