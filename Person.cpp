#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include "Person.h"
#include "County.h"
#include "State.h"

using namespace std;

string SSNHyphens(const string &);
string ZipHyphens(const string &);
string Trim(string aString);
void Upper(string &);



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

void Person::DisplayPerson()
{
    if(_found == false || _deleted == true)
    {
        return;
    }
    int i;
    State newState;
    County newCounty;
    int intStateCode;
    int intCountyCode;
    string StateName;
    string CountyName;
    string data;
    string fullName;
    string CityStZip;

    //This buffer is the set-up for the display. The strncpy's below populate this buffer
    char outBuffer[][84] = {
       //012345678901234567890123456789012345678901234567890123456789012345678901234567890
        "SSN       : $$$-$$-$$$$                        OLN    :      *********             ",//00
        "FULL NAME : LASTNAME          FIRSTNAME    M                                       ",//01
        "ADDRESS   : STREET                             STATE  : (00) STATE                 ",//02
        "            CITY                ST  ZIP        COUNTY : (00) COUNTY                " //03
    }; //012345678901234567890123456789012345678901234567890123456789012345678901234567890

    intStateCode = atoi(_stateCode.c_str()); 
    intCountyCode = atoi(_countyCode.c_str()); 
    StateName = newState.GetState(intStateCode);
    CountyName = newCounty.GetCounty(intCountyCode);

    //Making Full Name from last, first MI.
    fullName.clear();
    fullName.append(Trim(_lastName));
    fullName.append(", ");
    fullName.append(Trim(_firstName));
    fullName.append(" ");
    if(_MI != " ")
    {
        fullName.append(Trim(_MI));
        fullName.append(".");
    }
    data.assign(34, ' ');
    data.replace(0, fullName.length(), fullName);
    strncpy(outBuffer[1]+12, data.c_str(), 34);

    //Making the second part of address look good
    CityStZip.clear();
    CityStZip.append(Trim(_city));
    CityStZip.append(", ");
    CityStZip.append(Trim(StateName.substr(0,2)));
    CityStZip.append(" ");
    CityStZip.append(Trim(ZipHyphens(_zip)));
    data.assign(34, ' ');
    data.replace(0, CityStZip.length(), CityStZip);
    strncpy(outBuffer[3]+12, data.c_str(), 34);

    //Regular stuff
    strncpy(outBuffer[0]+12, SSNHyphens(_SSN).c_str(), SSNLENGTH+2);
    strncpy(outBuffer[0]+61, _OLN.c_str(), OLNLENGTH);

    strncpy(outBuffer[2]+12, _street.c_str(), _street.length());
    strncpy(outBuffer[2]+57, _stateCode.c_str(), STATECODELENGTH);
    Upper(StateName);
    strncpy(outBuffer[2]+61, StateName.c_str()+2, newState.GetRecordLength()-2);

    strncpy(outBuffer[3]+57, _countyCode.c_str(), COUNTYCODELENGTH);
    Upper(CountyName);
    strncpy(outBuffer[3]+61, CountyName.c_str(), newCounty.GetRecordLength());

    //Writing out the buffer
    for(i = 0; i < 4; i++)
    {
        cout << "\n\t";
        cout.write(outBuffer[i], sizeof(outBuffer[i]));
        cout << endl;
    }
}


void Person::PrintPerson()
{
    if(_found == false || _deleted == true)
        return;
    int i;
    State newState;
    County newCounty;
    int intStateCode;
    int intCountyCode;
    string StateName;
    string CountyName;
    string data;
    string fullName;
    string CitySt;

    //This buffer is the set-up for the display. The strncpy's below populate this buffer
    char outBuffer[][85] = {
       //SSN         FULL NAME?                         OLN           STATE  COUNTY
       //            ADDRESS                        CITY                     ZIPCODE
       //012345678901234567890123456789012345678901234567890123456789012345678901234567890
        "$$$-$$-$$$$ FULLNAME##**********##########**** OLN######     (00)ST (00)COUNTY####**",//00
        "            STREET####**********########## CITYST####************   ZIPCODE###      ",//01
    }; //012345678901234567890123456789012345678901234567890123456789012345678901234567890
       //0         1         2         3         4         5         6         7         8

    intStateCode = atoi(_stateCode.c_str()); 
    intCountyCode = atoi(_countyCode.c_str()); 
    StateName = newState.GetState(intStateCode);
    CountyName = newCounty.GetCounty(intCountyCode);

    //Making Full Name from last, first MI.
    fullName.clear();
    fullName.append(Trim(_lastName));
    fullName.append(", ");
    fullName.append(Trim(_firstName));
    fullName.append(" ");
    if(_MI != " ")
    {
        fullName.append(Trim(_MI));
        fullName.append(".");
    }
    data.assign(34, ' ');
    data.replace(0, fullName.length(), fullName);
    strncpy(outBuffer[0]+12, data.c_str(), 34);

    //Making the second part of address look good
    CitySt.clear();
    CitySt.append(Trim(_city));
    CitySt.append(", ");
    CitySt.append(Trim(StateName.substr(0,2)));
    data.assign(24, ' ');
    data.replace(0, CitySt.length(), CitySt);
    strncpy(outBuffer[1]+43, data.c_str(), 24);

    //Regular stuff
    strncpy(outBuffer[0]+0, SSNHyphens(_SSN).c_str(), SSNLENGTH+2);
    strncpy(outBuffer[0]+47, _OLN.c_str(), OLNLENGTH);
    strncpy(outBuffer[0]+62, _stateCode.c_str(), STATECODELENGTH);
    strncpy(outBuffer[0]+65, StateName.c_str(), 2);
    strncpy(outBuffer[0]+69, _countyCode.c_str(), COUNTYCODELENGTH);
    strncpy(outBuffer[0]+72, CountyName.c_str(), newCounty.GetRecordLength());

    strncpy(outBuffer[1]+12, _street.c_str(), _street.length());
    strncpy(outBuffer[1]+68, ZipHyphens(_zip).c_str(), 10);

    //Writing out the buffer
    for(i = 0; i < 2; i++)
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
    cout << "inStateCode.length() " << inStateCode.length() << endl;
    if(inStateCode.length() == 1)
    {
        _stateCode = "0" + inStateCode;

    }
    else
        _stateCode.replace(0,2,inStateCode);
}


void Person::SetCountyCode(const string & inCountyCode)
{
    if(inCountyCode.length() == 1)
    {
        _countyCode= "0" + inCountyCode;
    }
    else
        _countyCode.replace(0,2,inCountyCode);
}

void Person::SetLastName(const string & inLastName)
{
    int len = inLastName.length() < LASTNAMELENGTH ?
        inLastName.length() : LASTNAMELENGTH;
    _lastName.assign(inLastName, 0, len);
    Upper(_lastName);
}

void Person::SetFirstName(const string & inFirstName)
{
    int len = inFirstName.length() < FIRSTNAMELENGTH ?
        inFirstName.length() : FIRSTNAMELENGTH;
    _firstName.assign(inFirstName, 0, len);
    Upper(_firstName);
}

void Person::SetMI(const string & inMI)
{
    int len = inMI.length() < MILENGTH ?
        inMI.length() : MILENGTH;
    _MI.assign(inMI, 0, len);
    Upper(_MI);
}

void Person::SetStreet(const string & inStreet)
{
    int len = inStreet.length() < STREETLENGTH ?
        inStreet.length() : STREETLENGTH;
    _street.assign(inStreet, 0, len);
    Upper(_street);
}

void Person::SetCity(const string & inCity)
{
    int len = inCity.length() < CITYLENGTH ?
        inCity.length() : CITYLENGTH;
    _city.assign(inCity, 0, len);
    Upper(_city);
}

void Person::SetZip(const string & inZip)
{
    int len = inZip.length() < ZIPLENGTH ?
        inZip.length() : ZIPLENGTH;
    _zip.assign(inZip, 0, len);
    Upper(_zip);
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
