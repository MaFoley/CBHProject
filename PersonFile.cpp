#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include "PersonFile.h"

using namespace std;
const int RECORDSIZE = 111;

PersonFile::PersonFile():
    _recordSize(RECORDSIZE),
    _currentRecordNumber(0)
{
    char PERSONFILE[] =  "person.db";
    int initZero = 0;

    fstream person1(PERSONFILE, ios::in | ios::out | ios::binary);

    if(!person1.is_open())
    {
        ofstream person2(PERSONFILE);
        person2.seekp(0);
        person2.write((char *) &initZero, sizeof(initZero));
        person2.close();
    }
    else
    {
        person1.close();
    }


    _personFile.open(PERSONFILE, ios::in | ios::out | ios::binary);

    if( !_personFile)
    {
        cerr << "Error opening file: " << PERSONFILE << endl;
    }
    else
    {
        cout << PERSONFILE << " successfully opened..." << endl;
        _personFile.seekg(0);
        _personFile.read((char *) &_numberPersons, sizeof(_numberPersons));
    }
}

void PersonFile::SortBySSN()
{
    bool sorted;
    char input1[RECORDSIZE];
    char input2[RECORDSIZE];
    int numPass;
    int i;

    numPass = 1;
    sorted = false;

    while(!sorted)
    {
        sorted = true;
        for( i = 1; i <= _numberPersons - numPass; ++i)
        {
            _personFile.seekg(i * _recordSize);
            _personFile.read(input1, _recordSize);
            _personFile.seekg((i+1) * _recordSize);
            _personFile.read(input2, _recordSize);
            
            if(strncmp(input1,input2,9) < 0)
               continue;
            //Beyond this point only runs if input1 > input2


            _personFile.seekp(i * _recordSize);
            _personFile.write(input2, _recordSize);
            _personFile.seekp((i+1) * _recordSize);
            _personFile.write(input1, _recordSize);
        }
    }
    ++numPass;
}
PersonFile::~PersonFile()
{
    _personFile.close();
}

