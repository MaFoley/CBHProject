#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include "VMake.h"

using namespace std;

const int MINCODE = 1;
const int MAXCODE = 51;
const int LENGTH = 11;

VMake::VMake():
    _minCode(MINCODE),
    _maxCode(MAXCODE),
    _recordLength(LENGTH)
{
    char INFILE[] =  "vmake.db";
    ifstream inputFile;

    inputFile.open(INFILE);
    if( !inputFile)
    {
        cerr << "Error opening file: " << INFILE << endl;
    }
    else
    {
        inputFile.seekg(0);
        inputFile.read((char *) &_numberVMakes, sizeof(_numberVMakes));

        _pVMakes = new char[_numberVMakes * _recordLength];

        inputFile.seekg(LENGTH);
        inputFile.read(_pVMakes, (_numberVMakes * _recordLength));
        inputFile.close();

        _pVMake = new char[ _recordLength + 1];
    }
}
char * VMake::GetVMake(int inVMakeCode) const
{
    _pVMake[_recordLength] = '\0';
    memset(_pVMake, '*', _recordLength);

    if(inVMakeCode < _minCode || inVMakeCode > _maxCode)
        return _pVMake;

    int offset = _recordLength * (inVMakeCode - _minCode);
    strncpy(_pVMake, _pVMakes + (offset), _recordLength);
    return _pVMake;
}

void VMake::DisplayVMakes() const
{
    const int NUMBERROWS = 17;
    const int COLUMNWIDTH = 20;
    const int BUFFERWIDTH = 80;
    char outputBuffer[NUMBERROWS][BUFFERWIDTH];
    char singleRecord[_recordLength + 1];
    int columnPosition;
    int currentColumn;
    int currentRow;
    int i;

    if(_numberVMakes <= 0)
    {
        cerr << "Error! No VMakes to Display" << endl;
        return;
    }
    currentColumn = 0;
    currentRow = 0;
    memset(outputBuffer, ' ', sizeof(outputBuffer));

    for(i = 0; i < _numberVMakes; i++)
    {
        columnPosition = currentColumn * COLUMNWIDTH;

        //Writing the Data Code
        snprintf(outputBuffer[currentRow] + columnPosition, 3, "%02d", i + _minCode); 
        outputBuffer[currentRow][columnPosition+2] = ' ';
        strncpy(singleRecord, GetVMake(i + _minCode), _recordLength);

        //Writing the Data Name
        strncpy(outputBuffer[currentRow]+ columnPosition + 3, singleRecord, 
                _recordLength); 
        currentRow++;
        
        if (currentRow > NUMBERROWS - 1)
        {
            currentColumn++;
            currentRow = 0;
        }

    }

    cout << "\n\n";

    for(i = 0; i < NUMBERROWS; i++)
    {
        cout << "\t\t";
        cout.write(outputBuffer[i], BUFFERWIDTH);
        cout << endl << endl;
    }

}

VMake::~VMake()
{
    delete [] _pVMakes;
    delete [] _pVMake;
}

