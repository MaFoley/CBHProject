#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include "Person.h"

using namespace std;

string SSNHyphens(const string &);



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
    int i;
    char outBuffer[][82] = {
        "SSN: $$$-$$-$$$$                                                                 ",
        "01                                                                               ",
        "02                                                                               "
    }; //01234567890123456789012345678901245678901234567890123456789012345678901234567890

    strncpy(outBuffer[0]+5, SSNHyphens(_SSN).c_str(),SSNLENGTH + 2);

    for(i = 0; i < 3; i++)
    {
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
