#include <iostream>
#include <string>
using namespace std;

const int DATALENGTH = 20;
const int CODELENGTH = 2;
const int ABBRLENGTH = 2;

int main()
{
    //Read from direct access file into inBuffer;

    string inBuffer;

    string strCode;
    string strAbbr;
    string dataName;

    inBuffer = "09DCDistrict of Columbia";
    strCode = inBuffer[0:1];
    strAbbr = inBuffer[2:3];
    dataName = inBuffer[4:23];

    char lineBuffer[DATALENGTH + 3];
    strncpy(lineBuffer, strCode.c_str(), CODELENGTH);
    strncpy(lineBuffer + CODELENGTH, strAbbr.c_str(), ABBRLENGTH);
    strncpy(lineBuffer + CODELENGTH + ABBRLENGTH, dataName.c_str(), DATALENGTH - CODELENGTH - ABBRLENGTH);

    return 0;
}
/*
 * XX AB STATE NAME(20)
 */

