#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdio>
#include "PersonFile.h"

using namespace std;
const int RECORDSIZE = 111;
string SSNNoHyphens(const string &);

PersonFile::PersonFile():
    _recordSize(RECORDSIZE)
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
            sorted = false;
        }
    }
    ++numPass;
}
PersonFile::~PersonFile()
{
    _personFile.close();
}

Person PersonFile::SearchBySSN(const string & aSSN)
{
    int first;
    int last;
    int midpoint;
    int icompare;
    char dataRecord[RECORDSIZE];
    string ssnSearch;
    Person foundPerson;

    foundPerson.SetFound(false);
    ssnSearch = SSNNoHyphens(aSSN);
    first=1;
    last=_numberPersons;

    while(true)
    {
        if(first > last) return foundPerson;
        midpoint=(first+last)/2;
        _personFile.seekg(midpoint*RECORDSIZE);
        _personFile.read(dataRecord,RECORDSIZE);
        icompare =  strncmp(ssnSearch.c_str(),dataRecord,9);

        if(icompare < 0) last=midpoint-1;
        if(icompare > 0) first=midpoint+1;
        if(icompare == 0)
        {
            _currentRecordNumber=midpoint+1;
            foundPerson.MakePerson(dataRecord);
            if(foundPerson.IsDeleted())
                foundPerson.SetFound(false);
            return foundPerson;
        }
    }
}

Person PersonFile::SearchByOLN(const string & aOLN)
{
    int icompare;
    char dataRecord[RECORDSIZE];
    string olnSearch;
    Person foundPerson;

    foundPerson.SetFound(false);

    for(int searchRecord = 1; searchRecord <= _numberPersons; ++searchRecord)
    {
        cout << "searchRecord: " << searchRecord << endl;
        _personFile.seekg(searchRecord*RECORDSIZE);
        _personFile.read(dataRecord,RECORDSIZE);
        icompare =  strncmp(olnSearch.c_str(), dataRecord+9 ,olnSearch.length());

        if(icompare == 0)
        {
            _currentRecordNumber = searchRecord;
            foundPerson.MakePerson(dataRecord);
            if(foundPerson.IsDeleted())
                foundPerson.SetFound(false);
            return foundPerson;
        }
    }
}
