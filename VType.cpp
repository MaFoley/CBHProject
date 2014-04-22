#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include "VType.h"

using namespace std;

const int MINCODE = 1;
const int MAXCODE = 15;
const int LENGTH = 15;

VType::VType():
    _minCode(MINCODE),
    _maxCode(MAXCODE),
    _recordLength(LENGTH)
{
    char INFILE[] =  "vtype.db";
    ifstream inputFile;

    inputFile.open(INFILE);
    if( !inputFile)
    {
        cerr << "Error opening file: " << INFILE << endl;
    }
    else
    {
        inputFile.seekg(0);
        inputFile.read((char *) &_numberVTypes, sizeof(_numberVTypes));

        _pVTypes = new char[_numberVTypes * _recordLength];

        inputFile.seekg(LENGTH);
        inputFile.read(_pVTypes, (_numberVTypes * _recordLength));
        inputFile.close();

        _pVType = new char[ _recordLength + 1];
    }
}
char * VType::GetVType(int inVTypeCode) const
{
    _pVType[_recordLength] = '\0';
    memset(_pVType, '*', _recordLength);

    if(inVTypeCode < _minCode || inVTypeCode > _maxCode)
        return _pVType;

    int offset = _recordLength * (inVTypeCode - _minCode);
    strncpy(_pVType, _pVTypes + (offset), _recordLength);
    return _pVType;
}

void VType::DisplayVTypes() const
{
    const int NUMBERROWS = 8;
    const int COLUMNWIDTH = 20;
    const int BUFFERWIDTH = 50;
    char outputBuffer[NUMBERROWS][BUFFERWIDTH];
    char singleRecord[_recordLength + 1];
    int columnPosition;
    int currentColumn;
    int currentRow;
    int i;

    if(_numberVTypes <= 0)
    {
        cerr << "Error! No VTypes to Display" << endl;
        return;
    }
    currentColumn = 0;
    currentRow = 0;
    memset(outputBuffer, ' ', sizeof(outputBuffer));

    for(i = 0; i < _numberVTypes; i++)
    {
        columnPosition = currentColumn * COLUMNWIDTH;

        //Writing the Data Code
        snprintf(outputBuffer[currentRow] + columnPosition, 3, "%02d", i + _minCode); 
        outputBuffer[currentRow][columnPosition+2] = ' ';
        strncpy(singleRecord, GetVType(i + _minCode), _recordLength);

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
        cout << "\t\t\t" ;
        cout.write(outputBuffer[i], BUFFERWIDTH);
        cout << endl << endl;
    }

}

VType::~VType()
{
    delete [] _pVTypes;
    delete [] _pVType;
}

