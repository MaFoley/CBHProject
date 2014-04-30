#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include "Vehicle.h"
#include "Color.h"
#include "VType.h"
#include "VMake.h"

using namespace std;

string SSNHyphens(const string &);
string SSNNoHyphens(const string &);
string Trim(string aString);
void Upper(string &);



const int SSNLENGTH = 9;
const int COLORCODELENGTH = 2;
const int VTYPECODELENGTH = 2;
const int VMAKECODELENGTH = 2;
const int TAGLENGTH = 7;
const int RECORDSIZE = 25;

Vehicle::Vehicle() :  _length(RECORDSIZE), _found(false), _deleted(false)
{
}


void Vehicle::MakeVehicle(const string & inRecord)
{
    _found = true;
    _SSN = inRecord.substr(0, SSNLENGTH);
    _VTypeCode = inRecord.substr(9, VTYPECODELENGTH);
    _topColorCode = inRecord.substr(11, COLORCODELENGTH);
    _VMakeCode = inRecord.substr(13, VMAKECODELENGTH);
    _bottomColorCode = inRecord.substr(15, COLORCODELENGTH);
    _tag = inRecord.substr(17, TAGLENGTH);
    //ie if the last bit is 1, deleted = true
    _deleted = (inRecord[RECORDSIZE -1] == '1') ? true : false;
}

string Vehicle::Recordify()
{
    string data;
    int len;

    data.assign(_length, 0x20);

    len = _SSN.length() < SSNLENGTH ?
        _SSN.length() : SSNLENGTH;
    data.replace(0, len, _SSN);

    len = _VTypeCode.length() < VTYPECODELENGTH ?
        _VTypeCode.length() : VTYPECODELENGTH;
    data.replace(9, len, _VTypeCode);

    len = _topColorCode.length() < COLORCODELENGTH ?
        _topColorCode.length() : COLORCODELENGTH;
    data.replace(15, len, _topColorCode);

    len = _VMakeCode.length() < VMAKECODELENGTH ?
        _VMakeCode.length() : VMAKECODELENGTH;
    data.replace(13, len, _VMakeCode);

    len = _bottomColorCode.length() < COLORCODELENGTH ?
        _bottomColorCode.length() : COLORCODELENGTH;
    data.replace(15, len, _bottomColorCode);


    data[RECORDSIZE-1] = _deleted ? '1' : '0';

    return data;
}
/*
void Vehicle::DisplayVehicle()
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

    intStateCode = atoi(_VTypeCode.c_str()); 
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
    strncpy(outBuffer[2]+57, _VTypeCode.c_str(), STATECODELENGTH);
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


void Vehicle::PrintVehicle()
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

    intStateCode = atoi(_VTypeCode.c_str()); 
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
    strncpy(outBuffer[0]+62, _VTypeCode.c_str(), STATECODELENGTH);
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
*/

void Vehicle::SetTag(const string & inTag)
{
    int len = inTag.length() < TAGLENGTH ?
        inTag.length() : TAGLENGTH;
    _tag.assign(inTag, 0, len);
}

void Vehicle::SetVTypeCode(const string & inVTypeCode)
{
    cout << "inVTypeCode.length() " << inVTypeCode.length() << endl;
    if(inVTypeCode.length() == 1)
    {
        _VTypeCode = "0" + inVTypeCode;

    }
    else
        _VTypeCode.replace(0,2,inVTypeCode);
}

void Vehicle::SetVMakeCode(const string & inVMakeCode)
{
    cout << "inVMakeCode.length() " << inVMakeCode.length() << endl;
    if(inVMakeCode.length() == 1)
    {
        _VMakeCode = "0" + inVMakeCode;

    }
    else
        _VMakeCode.replace(0,2,inVMakeCode);
}

void Vehicle::SetTopColorCode(const string & inTopColorCode)
{
    cout << "inTopColorCode.length() " << inTopColorCode.length() << endl;
    if(inTopColorCode.length() == 1)
    {
        _topColorCode = "0" + inTopColorCode;

    }
    else
        _topColorCode.replace(0,2,inTopColorCode);
}


void Vehicle::SetBottomColorCode(const string & inBottomColorCode)
{
    if(inBottomColorCode.length() == 1)
    {
        _bottomColorCode= "0" + inBottomColorCode;
    }
    else
        _bottomColorCode.replace(0,2,inBottomColorCode);
}

