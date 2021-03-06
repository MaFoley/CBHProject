#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>

using namespace std;
const int CODELENGTH = 2;
const int DATALENGTH = 15;
const int MINCODE = 1;
const int MAXCODE = 15;

int main()
{
    const char INFILE[] = "vtype.data";
    const char OUTFILE[] = "vtype.db";

    char inBuffer[80];
    char outBuffer[(MAXCODE-MINCODE+1) * DATALENGTH];
    char charCode[CODELENGTH + 1];
    int intCode;
    int numValid, numInvalid;

    ifstream inputFile;
    ofstream outputFile;

    inputFile.open(INFILE);
    
    if(!inputFile)
    {
        cerr << "Problem openeing input file: " << INFILE << endl;
        return 1;
    }

    outputFile.open(OUTFILE);

    if(!outputFile)
    {
        cerr << "Problem openeing output file: " << OUTFILE << endl;
        inputFile.close();
        return 2;
    }

    numValid = 0;
    numInvalid = 0;

    memset(outBuffer, ' ', sizeof(outBuffer));

    while(true)
    {
        memset(inBuffer, ' ', sizeof(inBuffer));
        inputFile.getline(inBuffer, sizeof(inBuffer));

        if(inputFile.eof())
            break;

        strncpy(charCode, inBuffer, CODELENGTH);
        charCode[CODELENGTH] = '\0';
        intCode = atoi(charCode);
        
        if(intCode < MINCODE || intCode > MAXCODE)
        {
            ++numInvalid;
            continue;
        }

        int copyLength = strlen(inBuffer) - CODELENGTH < DATALENGTH
            ? strlen(inBuffer) - CODELENGTH : DATALENGTH;
        strncpy(outBuffer + ((intCode - MINCODE) * DATALENGTH),
                inBuffer + CODELENGTH,
                copyLength);
        ++numValid;
    }
    outputFile.seekp(0);
    outputFile.write((char *) &numValid, sizeof(numValid));

    outputFile.seekp(DATALENGTH);
    outputFile.write(outBuffer, sizeof(outBuffer));

    inputFile.close();
    outputFile.close();

    cout << "vtype.db: " << endl;
    cout << "\tNumber of valid records written to " << OUTFILE << ": " << numValid << endl;
    cout << "\tNumber of invalid not written: " << numInvalid << endl;
     
    return 0;
}
