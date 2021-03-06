#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdio>
#include "Person.h"
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
void PersonFile::AddPerson(Person & aPerson)
{
    ++_numberPersons;
    _currentRecordNumber = _numberPersons;
    _personFile.seekp(0);
    _personFile.write((char *) &_numberPersons, sizeof(_numberPersons));
    UpdatePerson(aPerson);
    SortBySSN();
}

void PersonFile::UpdatePerson(Person & aPerson)
{
    string record;
    record = aPerson.Recordify();
    _personFile.seekp(_currentRecordNumber*RECORDSIZE);
    _personFile.write(record.c_str(), RECORDSIZE);
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
    string ssnBlankFilled = "         "; //Searching needs to account for spaces
    char dataRecord[RECORDSIZE];
    string ssnSearch;
    Person foundPerson;

    foundPerson.SetFound(false);
    foundPerson.SetSSN(aSSN);
    ssnSearch = SSNNoHyphens(aSSN);
    ssnBlankFilled.replace(0,ssnSearch.length(), ssnSearch);
    first=1;
    last=_numberPersons;

    while(true)
    {
        if(first > last)
        { 
            cout << "currentRecordNumber: " << _currentRecordNumber << endl;
            return foundPerson;
        } 

        midpoint=(first+last)/2;
        _personFile.seekg(midpoint*RECORDSIZE);
        _personFile.read(dataRecord,RECORDSIZE);
        icompare =  strncmp(ssnBlankFilled.c_str(),dataRecord,9);

        if(icompare < 0) last=midpoint-1;
        if(icompare > 0) first=midpoint+1;
        if(icompare == 0)
        {
            _currentRecordNumber=midpoint;
            cout << "currentRecordNumber: " << _currentRecordNumber << endl;
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
    string olnBlankFilled = "         "; //Searching by OLN needs to account for spaces
    Person foundPerson;

    foundPerson.SetFound(false);
    foundPerson.SetOLN(aOLN);

    for(int searchRecord = 1; searchRecord <= _numberPersons; ++searchRecord)
    {
        _personFile.seekg(searchRecord*RECORDSIZE);
        _personFile.read(dataRecord,RECORDSIZE);
        olnBlankFilled.replace(0,aOLN.length(), aOLN);
        icompare =  strncmp(olnBlankFilled.c_str(), dataRecord+9 ,olnBlankFilled.length());

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

Person PersonFile::SearchByRecordNumber(const int & inRecordNumber)
{
    char dataRecord[RECORDSIZE];
    Person foundPerson;
    if(inRecordNumber < 1 || inRecordNumber > _numberPersons)
    {
        foundPerson.SetFound(false);
        return foundPerson;
    }

    _personFile.seekg(inRecordNumber*RECORDSIZE);
    _personFile.read(dataRecord, RECORDSIZE);

    _currentRecordNumber = inRecordNumber;
    foundPerson.MakePerson(dataRecord);
    if(foundPerson.IsDeleted())
        foundPerson.SetFound(false);
    return foundPerson;
}
    
        
