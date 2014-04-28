#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include "Color.h"
#include "VMake.h"
#include "VType.h"

using namespace std;


const int SSNLENGTH = 9;
const int OLNLENGTH = 9;
const int STATECODELENGTH = 2;
const int COUNTYCODELENGTH = 2;
const int LASTNAMELENGTH = 17;
const int FIRSTNAMELENGTH = 12;
const int MILENGTH = 1;
const int STREETLENGTH = 30;
const int CITYLENGTH = 19;
const int ZIPLENGTH = 9;
const int RECORDSIZE = 111;

Person::Person() :  _length(RECORDSIZE), _found(false), _deleted(false)
{
}

void Person::MakePerson(const string & inRecord)
{
    _found = true;
    _SSN = inRecord.substr(0, SSNLENGTH);
    _OLN = inRecord.substr(9, OLNLENGTH);
    _stateCode = inRecord.substr(18, STATECODELENGTH);
    _countyCode = inRecord.substr(20, COUNTYCODELENGTH);
    _lastName = inRecord.substr(22, LASTNAMELENGTH);
    _firstName = inRecord.substr(39, FIRSTNAMELENGTH);
    _MI = inRecord.substr(51, MILENGTH);
    _street = inRecord.substr(52, STREETLENGTH);
    _city = inRecord.substr(82, CITYLENGTH);
    _zip = inRecord.substr(101, ZIPLENGTH);
    
    //ie if the last bit is 1, deleted = true
    _deleted = (inRecord[RECORDSIZE -1] == '1') ? true : false;
}

string Person::Recordify()
{
    string data;
    int len;

    data.assign(_length, 0x20);

    len = _SSN.length() < SSNLENGTH ?
        _SSN.length() : SSNLENGTH;
    data.replace(0, len, _SSN);

    len = _OLN.length() < OLNLENGTH ?
        _OLN.length() : OLNLENGTH;
    data.replace(9, len, _OLN);

    len = _stateCode.length() < STATECODELENGTH ?
        _stateCode.length() : STATECODELENGTH;
    data.replace(18, len, _stateCode);

    len = _countyCode.length() < COUNTYCODELENGTH ?
        _countyCode.length() : COUNTYCODELENGTH;
    data.replace(20, len, _countyCode);

    len = _lastName.length() < LASTNAMELENGTH ?
        _lastName.length() : LASTNAMELENGTH;
    data.replace(22, len, _lastName);

    len = _firstName.length() < FIRSTNAMELENGTH ?
        _firstName.length() : FIRSTNAMELENGTH;
    data.replace(39, len, _firstName);

    len = _MI.length() < MILENGTH ?
        _MI.length() : MILENGTH;
    data.replace(51, len, _MI);

    len = _street.length() < STREETLENGTH ?
        _street.length() : STREETLENGTH;
    data.replace(52, len, _street);
    
    len = _city.length() < CITYLENGTH ?
        _city.length() : CITYLENGTH;
    data.replace(82, len, _city);

    len = _zip.length() < ZIPLENGTH ?
        _zip.length() : ZIPLENGTH;
    data.replace(101, len, _zip);
    data[RECORDSIZE-1] = _deleted ? '1' : '0';

    return data;
}
//void Person::Recordify()

void Person::DisplayPerson()
{
    if(_found == false || _deleted == true)
    {
        cout << "\n\t\t\tRecord not found!" << endl;
        return;
    }
    const int COUNTYLENGTH = 12;
    const int STATELENGTH = 22;
    int i;
    State newState;
    County newCounty;
    int intStateCode;
    int intCountyCode;
    string StateName;
    string CountyName;

    //This buffer is the set-up for the display. The strncpy's below populate this buffer
    char outBuffer[][82] = {
       //012345678901234567890123456789012345678901234567890123456789012345678901234567890
        "Record for: LASTNAME********* FIRSTNAME*** M                                     ",//00
        "       SSN: $$$-$$-$$$$                          OLN: *********                  ",//01
        "                                                                                 ",//02
        "   ADDRESS: STREET************************     STATE: (XX) STATE*****************",//03
        "            CITY*************** ST  ZIP*******  CNTY: (XX) COUNTY******          " //04
    }; //012345678901234567890123456789012345678901234567890123456789012345678901234567890

    intStateCode = atoi(_stateCode.c_str()); 
    intCountyCode = atoi(_countyCode.c_str()); 
    StateName = newState.GetState(intStateCode);
    CountyName = newCounty.GetCounty(intCountyCode);

    strncpy(outBuffer[0]+12, _lastName.c_str(), LASTNAMELENGTH);
    strncpy(outBuffer[0]+30, _firstName.c_str(), FIRSTNAMELENGTH);
    strncpy(outBuffer[0]+43, _MI.c_str(), MILENGTH);

    strncpy(outBuffer[1]+12, SSNHyphens(_SSN).c_str(),SSNLENGTH + 2);
    strncpy(outBuffer[1]+54, _OLN.c_str(), OLNLENGTH);

    strncpy(outBuffer[3]+12, _street.c_str(), STREETLENGTH);
    strncpy(outBuffer[3]+55, _stateCode.c_str(), STATECODELENGTH);
    strncpy(outBuffer[3]+59, StateName.c_str()+2, STATELENGTH);

    strncpy(outBuffer[4]+12, _city.c_str(), CITYLENGTH);
    strncpy(outBuffer[4]+32, StateName.c_str(), 2);
    strncpy(outBuffer[4]+36, ZipHyphens(_zip).c_str(), ZIPLENGTH + 1);
    strncpy(outBuffer[4]+55, _countyCode.c_str(), COUNTYCODELENGTH);
    strncpy(outBuffer[4]+59, CountyName.c_str(), COUNTYLENGTH);

    //Writing out the buffer
    for(i = 0; i < 5; i++)
    {
        cout << "\n\t";
        cout.write(outBuffer[i], sizeof(outBuffer[i]));
        cout << endl;
    }
}


void Person::SetOLN(const string & inOLN)
{
    int len = inOLN.length() < OLNLENGTH ?
        inOLN.length() : OLNLENGTH;
    _OLN.assign(inOLN, 0, len);
}

void Person::SetStateCode(const string & inStateCode)
{
    _stateCode.assign(inStateCode, 0, STATECODELENGTH);
}

void Person::SetCountyCode(const string & inCountyCode)
{
    _countyCode.assign(inCountyCode, 0, COUNTYCODELENGTH);
}

void Person::SetLastName(const string & inLastName)
{
    int len = inLastName.length() < LASTNAMELENGTH ?
        inLastName.length() : LASTNAMELENGTH;
    _lastName.assign(inLastName, 0, len);
    //Upper(_lastName);
}

void Person::SetFirstName(const string & inFirstName)
{
    int len = inFirstName.length() < FIRSTNAMELENGTH ?
        inFirstName.length() : FIRSTNAMELENGTH;
    _firstName.assign(inFirstName, 0, len);
    //Upper(_firstName);
}

void Person::SetMI(const string & inMI)
{
    int len = inMI.length() < MILENGTH ?
        inMI.length() : MILENGTH;
    _MI.assign(inMI, 0, len);
}



/*
const int SSNLENGTH = 9;
const int OLNLENGTH = 9;
const int STATECODELENGTH = 2;
const int COUNTYCODELENGTH = 2;
const int LASTNAMELENGTH = 17;
const int FIRSTNAMELENGTH = 12;
const int MILENGTH = 1;
const int STREETLENGTH = 30;
const int CITYLENGTH = 19;
const int ZIPLENGTH = 9;
const int RECORDSIZE = 111;
*/
