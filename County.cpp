#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include "County.h"

using namespace std;

const int MINCODE = 0;
const int MAXCODE = 67;
const int LENGTH = 12;

County::County():
    _minCode(MINCODE),
    _maxCode(MAXCODE),
    _recordLength(LENGTH)
{
    char INFILE[] =  "county.db";
    ifstream inputFile;

    inputFile.open(INFILE);
    if( !inputFile)
    {
        cerr << "Error opening file: " << INFILE << endl;
    }
    else
    {
        inputFile.seekg(0);
        inputFile.read((char *) &_numberCounties, sizeof(_numberCounties));

        _pCounties = new char[_numberCounties * _recordLength];

        inputFile.seekg(LENGTH);
        inputFile.read(_pCounties, (_numberCounties * _recordLength));
        inputFile.close();

        _pCounty = new char[ _recordLength + 1];
    }
}
char * County::GetCounty(int inCountyCode) const
{
    _pCounty[_recordLength] = '\0';
    memset(_pCounty, '*', _recordLength);

    if(inCountyCode < _minCode || inCountyCode > _maxCode)
        return _pCounty;

    int offset = _recordLength * (inCountyCode - _minCode);
    strncpy(_pCounty, _pCounties + (offset), _recordLength);
    return _pCounty;
}

void County::DisplayCounties() const
{
    const int NUMBERROWS = 17;
    const int COLUMNWIDTH = 20;
    const int BUFFERWIDTH = 100;
    char outputBuffer[NUMBERROWS][BUFFERWIDTH];
    char singleRecord[_recordLength + 1];
    int columnPosition;
    int currentColumn;
    int currentRow;
    int i;

    if(_numberCounties <= 0)
    {
        cerr << "Error! No Counties to Display" << endl;
        return;
    }
    currentColumn = 0;
    currentRow = 0;
    memset(outputBuffer, ' ', sizeof(outputBuffer));

    for(i = 0; i < _numberCounties; i++)
    {
        columnPosition = currentColumn * COLUMNWIDTH;

        //Writing the Data Code
        snprintf(outputBuffer[currentRow] + columnPosition, 3, "%02d", i + _minCode); 
        outputBuffer[currentRow][columnPosition+2] = ' ';
        strncpy(singleRecord, GetCounty(i + _minCode), _recordLength);

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
        cout << "\t";
        cout.write(outputBuffer[i], BUFFERWIDTH);
        cout << endl;
    }

}

County::~County()
{
    delete [] _pCounties;
    delete [] _pCounty;
}

