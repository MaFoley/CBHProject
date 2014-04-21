#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include "PersonFile.h"

using namespace std;

PersonFile::PersonFile():
    _currentRecordNumber(0)
{
    char INFILE[] =  "person.db";

    _personFile.open(INFILE);

    if( !_personFile)
    {
        cerr << "Error opening file: " << INFILE << endl;
    }
    else
    {
        cout << INFILE << " successfully opened..." << endl;
        _personFile.seekg(0);
        _personFile.read((char *) &_numberPersons, sizeof(_numberPersons));
    }
}

PersonFile::~PersonFile()
{
    _personFile.close();
}

