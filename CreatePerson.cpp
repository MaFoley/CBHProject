#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include "PersonFile.h"

using namespace std;
const int DATALENGTH = 111;

int main()
{
    const char INFILE[] = "person.data";
    const char OUTFILE[] = "person.db";
    int numberRecords;
    int offset;

    char inBuffer[150];

    ifstream inputFile;
    ofstream outputFile;

    inputFile.open(INFILE);

    if(!inputFile)
    {
        cerr << "Problem opening input file: " << INFILE << endl;
        return -1;
    }

    outputFile.open(OUTFILE);

    if(!outputFile)
    {
        cerr << "Problem opening output file: " << OUTFILE << endl;
        inputFile.close();
        return -2;
    }
    cout << OUTFILE << " successfully opened..." << endl;

    numberRecords = 0;

    memset(inBuffer, ' ', sizeof(inBuffer));

    while(true)
    {
        memset(inBuffer, ' ', sizeof(inBuffer));
        inputFile.getline(inBuffer, sizeof(inBuffer));

        if(inputFile.eof())
            break;
        offset = (numberRecords + 1) * DATALENGTH;
        outputFile.seekp(offset);
        outputFile.write(inBuffer, DATALENGTH);
        ++numberRecords;
    }
    outputFile.seekp(0);
    outputFile.write((char *) &numberRecords, sizeof(numberRecords));

    inputFile.close();
    outputFile.close();

    cout << "\tNumber of valid records written to " << OUTFILE << ": " << numberRecords << endl;
    cout << "\tSorting..." << endl;
    PersonFile * pPersonFile = new PersonFile;
    pPersonFile -> SortBySSN();
    delete pPersonFile;
    cout << "\tSorted!" << endl;

    return 0;
}
