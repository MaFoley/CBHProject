#include <iostream>
#include<cstring>
#include<cstdlib>
#include<fstream>

using namespace std;
const int CODELENGTH = 2;
const int DATALENGTH = 22;
const int MINCODE = 1;
const int MAXCODE = 51;

int main()
{
    const char INFILE[] = "state.data";
    const char OUTFILE[] = "state.db";

    char inBuffer[80];
    char outBuffer[(MAXCODE-MINCODE+1) * DATALENGTH];
    char charCode[CODELENGTH + 1];
    int intCode;
    int numValid, numInvalid;

    ifstream inputFile;
    ofstream outputFile;

    inputFile.open(INFILE);

