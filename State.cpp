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
char * State::GetState(int inStateCode) const
{
    _pState[_recordLength] = '\0';
    memset(_pState, '*', _recordLength);

    if(inStateCode < _minCode || inStateCode > _maxCode)
        return _pState;

    strncpy(_pState, _pStates + (_recordLength * (inStateCode-_minCode)), _recordLength);
    *(_pState+LENGTH-_minCode) = '\0';
    return _pState;
}

void State::DisplayStates() const
{
    const int NUMBERROWS = 17;
    const int COLUMNWIDTH = 28;
    const int BUFFERWIDTH = 100;
    char outputBuffer[NUMBERROWS][BUFFERWIDTH];
    char singleRecord[_recordLength + 1];
    int columnPosition;
    int currentColumn;
    int currentRow;
    int i;

    if(_numberStates <= 0)
    {
        cerr << "Error! No States to Display" << endl;
        return;
    }
    currentColumn = 0;
    currentRow = 0;
    memset(outputBuffer, ' ', sizeof(outputBuffer));

    for(i = 0; i < _numberStates; i++)
    {
        

        columnPosition = currentColumn * COLUMNWIDTH;

        //Writing the Data Code
        snprintf(outputBuffer[currentRow] + columnPosition, 3, "%02d", i + _minCode); 
        outputBuffer[currentRow][columnPosition+2] = ' ';
        strncpy(singleRecord, GetState(i + _minCode), _recordLength);

        //Writing the Abbreviation
        strncpy(outputBuffer[currentRow]+columnPosition + 3, singleRecord, 2); 
        outputBuffer[currentRow][columnPosition + 5] = ' ';

        //Writing the Data Name
        strncpy(outputBuffer[currentRow]+ columnPosition + 6, singleRecord+2, _recordLength-2); 
        currentRow++;
        
        if (currentRow > NUMBERROWS - 1)
        {
            currentColumn++;
            currentRow = 0;
        }

        

    }
    cout << "\n\n" ;

    for(i = 0; i < NUMBERROWS; i++)
    {
        cout << "\t";
        cout.write(outputBuffer[i], BUFFERWIDTH);
        cout << endl;
    }

}
State::~State()
{
    delete [] _pStates;
    delete [] _pState;
}

