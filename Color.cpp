#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include "Color.h"

using namespace std;

const int MINCODE = 1;
const int MAXCODE = 31;
const int LENGTH = 25;

Color::Color():
    _minCode(MINCODE),
    _maxCode(MAXCODE),
    _recordLength(LENGTH)
{
    char INFILE[] =  "color.db";
    ifstream inputFile;

    inputFile.open(INFILE);
    if( !inputFile)
    {
        cerr << "Error opening file: " << INFILE << endl;
    }
    else
    {
        inputFile.seekg(0);
        inputFile.read((char *) &_numberColors, sizeof(_numberColors));

        _pColors = new char[_numberColors * _recordLength];

        inputFile.seekg(LENGTH);
        inputFile.read(_pColors, _numberColors * _recordLength);
        inputFile.close();

        _pColor = new char[ _recordLength + 1];
    }
}
char * Color::GetColor(int inColorCode) const
{
    _pColor[_recordLength] = '\0';
    memset(_pColor, '*', _recordLength);

    if(inColorCode < _minCode || inColorCode > _maxCode)
        return _pColor;

    strncpy(_pColor, _pColors + (_recordLength * (inColorCode - _minCode)), _recordLength);
    return _pColor;
}

void Color::DisplayColors() const
{
    const int NUMBERROWS = 16;
    const int COLUMNWIDTH = 30;
    const int BUFFERWIDTH = 100;
    const int ABBRLENGTH = 3;
    char outputBuffer[NUMBERROWS][BUFFERWIDTH];
    char singleRecord[_recordLength + 1];
    int columnPosition;
    int currentColumn;
    int currentRow;
    int i;

    if(_numberColors <= 0)
    {
        cerr << "Error! No Colors to Display" << endl;
        return;
    }
    currentColumn = 0;
    currentRow = 0;
    memset(outputBuffer, ' ', sizeof(outputBuffer));

    for(i = 0; i < _numberColors; i++)
    {
        cerr << "columnPosition: " << columnPosition << endl;
        cerr << "currentColumn: " << currentColumn << endl;
        

        columnPosition = currentColumn * COLUMNWIDTH;

        //Writing the Data Code
        snprintf(outputBuffer[currentRow] + columnPosition, 3, "%02d", i + _minCode); 
        outputBuffer[currentRow][columnPosition+2] = ' ';
        strncpy(singleRecord, GetColor(i + _minCode), _recordLength);

        //Writing the Abbreviation
        strncpy(outputBuffer[currentRow]+columnPosition + 3, singleRecord, ABBRLENGTH); 
        outputBuffer[currentRow][columnPosition + 6] = ' ';

        //Writing the Data Name
        strncpy(outputBuffer[currentRow]+ columnPosition + 7, singleRecord + ABBRLENGTH, 
                _recordLength-ABBRLENGTH); 
        currentRow++;
        
        if (currentRow > NUMBERROWS - 1)
        {
            currentColumn++;
            currentRow = 0;
        }

        

    }

    for(i = 0; i < NUMBERROWS; i++)
    {
        cout.write(outputBuffer[i], BUFFERWIDTH);
        cout << endl;
    }

}
Color::~Color()
{
    delete [] _pColors;
    delete [] _pColor;
}

