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
<<<<<<< HEAD
=======
    cout << "GetStates: \n" << pStateObj -> GetState(1) << endl;
    cout << pStateObj -> GetState(2) << endl;
    cout << pStateObj -> GetState(51) << endl;
>>>>>>> 52e8a7e133ac800bfbd901e45ab4279a897ff9fe

    delete pStateObj;
    return 0;
}
