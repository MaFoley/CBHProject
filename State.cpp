#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include "State.h"

using namespace std;

const int MINCODE = 1;
const int MAXCODE = 51;
const int LENGTH = 22;

State::State():  
    _minCode(MINCODE), 
    _maxCode(MAXCODE), 
    _recordLength(LENGTH)
{ 
    char INFILE[] =  "state.db";
    ifstream inputFile;

    inputFile.open(INFILE);
    if( !inputFile)
    {
        cerr << "Error opening file: " << INFILE << endl;
    }
    else
    {
        inputFile.seekg(0);
        inputFile.read((char *) &_numberStates, sizeof(_numberStates));

        _pStates = new char[_numberStates * _recordLength];

        inputFile.seekg(LENGTH);
        inputFile.read(_pStates, _numberStates * _recordLength);
        inputFile.close();

        _pState = new char[ _recordLength + 1];
    }
}
<<<<<<< HEAD

=======
char * State::GetState(int inStateCode) const
{
    strncpy(_pState, _pStates + (LENGTH * (inStateCode-1)), LENGTH);
    *(_pState+LENGTH-1) = '\0';
    return _pState;
}
    
>>>>>>> 52e8a7e133ac800bfbd901e45ab4279a897ff9fe
State::~State()
{
    delete [] _pStates;
    delete [] _pState;
}

