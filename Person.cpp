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

void Person::SetStreet(const string & inStreet)
{
    int len = inStreet.length() < STREETLENGTH ?
        inStreet.length() : STREETLENGTH;
    _street.assign(inStreet, 0, len);
}

void Person::SetCity(const string & inCity)
{
    int len = inCity.length() < CITYLENGTH ?
        inCity.length() : CITYLENGTH;
    _city.assign(inCity, 0, len);
}
void Person::SetZip(const string & inZip)
{
    int len = inZip.length() < ZIPLENGTH ?
        inZip.length() : ZIPLENGTH;
    _zip.assign(inZip, 0, len);
}


