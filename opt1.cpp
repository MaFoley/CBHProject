#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
using namespace std;

const int DATALENGTH = 22;
const int ABBRLENGTH = 2;
const int NAMELENGTH = 20;

int main()
{
    //Read from direct access file into inBuffer;
    ifstream inputFile;
    int numRecords;
    char inBuffer[DATALENGTH + 1];
    char charAbbr[ABBRLENGTH + 1];
    char charName[NAMELENGTH + 1];


    inputFile.open("state.db");

    inputFile.seekg(0);
    inputFile.read((char *) &numRecords, sizeof(numRecords));

    for(int counter = 1; counter <= numRecords; counter ++)
    {
        inputFile.seekg(DATALENGTH * counter); //Counter acts as the record number
        inputFile.read(inBuffer, DATALENGTH);
        inBuffer[DATALENGTH] = '\0';

        strncpy(charAbbr, inBuffer, ABBRLENGTH);
        strncpy(charName, inBuffer, NAMELENGTH);
        charAbbr[ABBRLENGTH] = '\0';
        charName[NAMELENGTH] = '\0';

        cout.fill('0');
        cout.width(2);
        cout << counter;
        cout.fill(' ');
        cout << ' ' << charAbbr << ' ' << charName << '\n';
    }
    inputFile.close();


    return 0;
}
/*
 * XX AB STATE NAME(20)
 */

