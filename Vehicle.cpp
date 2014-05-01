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
    //Reading from offsets in the record, which is retrieved from vehicle.db in via a VehicleFile object
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

    //The ternary ensures that what's put into the record is only as long as the space
    //allotted for it in the file
    len = _SSN.length() < SSNLENGTH ?
        _SSN.length() : SSNLENGTH;
    data.replace(0, len, _SSN);

    len = _VTypeCode.length() < VTYPECODELENGTH ?
        _VTypeCode.length() : VTYPECODELENGTH;
    data.replace(9, len, _VTypeCode);

    len = _topColorCode.length() < COLORCODELENGTH ?
        _topColorCode.length() : COLORCODELENGTH;
    data.replace(11, len, _topColorCode);

    len = _VMakeCode.length() < VMAKECODELENGTH ?
        _VMakeCode.length() : VMAKECODELENGTH;
    data.replace(13, len, _VMakeCode);

    len = _bottomColorCode.length() < COLORCODELENGTH ?
        _bottomColorCode.length() : COLORCODELENGTH;
    data.replace(15, len, _bottomColorCode);

    len = _tag.length() < TAGLENGTH ?
        _tag.length() : TAGLENGTH;
    data.replace(17, len, _tag);

    data[RECORDSIZE-1] = _deleted ? '1' : '0';

    return data;
}

void Vehicle::DisplayVehicle()
{
    //Rather sloppily handling if there is not a vehicle for the foreign key given
    if(_found == false || _deleted == true)
    {
        cout << "\t============================Vehicle Information====================================";
        cout << "\n\n\tFor SSN: " << SSNHyphens(_SSN) << " no vehicle found." << endl << endl;
        return;
    }
    int i;
    VType newVType;
    VMake newVMake;
    Color newColorCode;
    int intCode;
    string VTypeName;
    string VMakeName;
    string TopColorName;
    string BottomColorName;
    string data;

    //This buffer is the set-up for the display. The strncpy's below populate this buffer
    char outBuffer[][84] = {
       //0         1         2         3         4         5         6         7
       //012345678901234567890123456789012345678901234567890123456789012345678901234567890
        "============================Vehicle Information====================================",//00
        "SSN       : $$$-$$-$$$$                             TAG    :      *******          ",//00
        "TOP COLOR : (00) TOPCOLOR                     VEHICLE MAKE : (00) VMAKE            ",//01
        "BTM COLOR : (00) BOTTOMCOLOR                  VEHICLE TYPE : (00) VTYPE            ",//02
    }; //012345678901234567890123456789012345678901234567890123456789012345678901234567890

    intCode = atoi(_VTypeCode.c_str()); 
    VTypeName = newVType.GetVType(intCode);

    intCode = atoi(_VTypeCode.c_str()); 
    VMakeName = newVMake.GetVMake(intCode);

    intCode = atoi(_topColorCode.c_str()); 
    TopColorName = newColorCode.GetColor(intCode);

    intCode = atoi(_bottomColorCode.c_str()); 
    BottomColorName = newColorCode.GetColor(intCode);
    //Making Full Name from last, first MI.

    //Regular stuff
    strncpy(outBuffer[1]+12, SSNHyphens(_SSN).c_str(), SSNLENGTH+2);
    strncpy(outBuffer[1]+66, _tag.c_str(), TAGLENGTH);

    strncpy(outBuffer[2]+13, _topColorCode.c_str(), COLORCODELENGTH);
    strncpy(outBuffer[2]+17, TopColorName.c_str() + 3, TopColorName.length() - 3);
    strncpy(outBuffer[2]+62, _VMakeCode.c_str(), VMAKECODELENGTH);
    strncpy(outBuffer[2]+66, VMakeName.c_str(), VMakeName.length());

    strncpy(outBuffer[3]+13, _bottomColorCode.c_str(), COLORCODELENGTH);
    strncpy(outBuffer[3]+17, BottomColorName.c_str()+3, BottomColorName.length() -3);
    strncpy(outBuffer[3]+62, _VTypeCode.c_str(), VTYPECODELENGTH);
    strncpy(outBuffer[3]+66, VTypeName.c_str(), VTypeName.length());
    //Writing out the buffer
    for(i = 0; i < 4; i++)
    {
        cout << "\n\t";
        cout.write(outBuffer[i], sizeof(outBuffer[i]));
        cout << endl;
    }
}

//Print is just a more condensed version of display.  Used in option 7
void Vehicle::PrintVehicle()
{
    //Rather sloppily handling if there is not a vehicle for the foreign key given
    if(_found == false || _deleted == true)
    {
        cout << "\tNO VEHICLE FOUND FOR DRIVER" << endl << endl;
        return;
    }
    int i;
    VType newVType;
    VMake newVMake;
    Color newColorCode;
    int intCode;
    string VTypeName;
    string VMakeName;
    string TopColorName;
    string BottomColorName;
    string data;

    //This buffer is the set-up for the display. The strncpy's below populate this buffer
    char outBuffer[][85] = {
       //    TAG     VMAKE                      VTYPE                 TOP CLR   BTM CLR  
       //012345678901234567890123456789012345678901234567890123456789012345678901234567890
        "    TAG**** (00) VMAKE*****#           (00) VTYPE*****#####  (00) TOP  (00) BTM     ",//00
    }; //012345678901234567890123456789012345678901234567890123456789012345678901234567890
       //0         1         2         3         4         5         6         7         8

 
    //Creating integer codes so that the GetCode methods can be called correctly
    intCode = atoi(_VTypeCode.c_str()); 
    VTypeName = newVType.GetVType(intCode);

    intCode = atoi(_VTypeCode.c_str()); 
    VMakeName = newVMake.GetVMake(intCode);

    intCode = atoi(_topColorCode.c_str()); 
    TopColorName = newColorCode.GetColor(intCode);

    intCode = atoi(_bottomColorCode.c_str()); 
    BottomColorName = newColorCode.GetColor(intCode);

    //Regular strncpy's straight from the members of the class
    strncpy(outBuffer[0]+4, _tag.c_str(), TAGLENGTH);

    strncpy(outBuffer[0]+13, _VMakeCode.c_str(), VMAKECODELENGTH);
    strncpy(outBuffer[0]+17, VMakeName.c_str(), VMakeName.length());
    strncpy(outBuffer[0]+40, _VTypeCode.c_str(), VTYPECODELENGTH);
    strncpy(outBuffer[0]+44, VTypeName.c_str(), VTypeName.length());

    strncpy(outBuffer[0]+62, _topColorCode.c_str(), COLORCODELENGTH);
    strncpy(outBuffer[0]+66, TopColorName.c_str(), 3); //prints out abbreviation instead of full color name
    strncpy(outBuffer[0]+72, _bottomColorCode.c_str(), COLORCODELENGTH);
    strncpy(outBuffer[0]+76, BottomColorName.c_str(), 3); //prints out abbreviation instead of full color name

    //Writing out the buffer
    //Loop structure is kept just in case more rows are desired later
    for(i = 0; i < 1; i++)
    {
        cout.write(outBuffer[i], sizeof(outBuffer[i]));
        cout << endl;
    }
    cout << endl;
}


//This set make use of the ternary operator to ensure what's put into the member
//is not too large for the space allotted in the .db file
void Vehicle::SetTag(const string & inTag)
{
    int len = inTag.length() < TAGLENGTH ?
        inTag.length() : TAGLENGTH;
    _tag.assign(inTag, 0, len);
    Upper(_tag);
}

//Setting the Codes requires accounting for single digit codes.  This is accomplished via the if-else construct
void Vehicle::SetVTypeCode(const string & inVTypeCode)
{
    if(inVTypeCode.length() == 1)
    {
        _VTypeCode = "0" + inVTypeCode;

    }
    else
        _VTypeCode.replace(0,2,inVTypeCode);
}

void Vehicle::SetVMakeCode(const string & inVMakeCode)
{
    if(inVMakeCode.length() == 1)
    {
        _VMakeCode = "0" + inVMakeCode;

    }
    else
        _VMakeCode.replace(0,2,inVMakeCode);
}

void Vehicle::SetTopColorCode(const string & inTopColorCode)
{
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

