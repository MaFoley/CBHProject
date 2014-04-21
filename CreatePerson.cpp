#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>

using namespace std;
const int DATALENGTH = 111;

int main()
{
    const char INFILE[] = "person.data";
    const char OUTFILE[] = "person.db";
    int numberRecords;

    char inBuffer[150];

    ifstream inputFile;
    ofstream _personFile;

    inputFile.open(INFILE);

    if(!inputFile)
    {
        cerr << "Problem opening input file: " << INFILE << endl;
        return -1;
    }

    _personFile.open(OUTFILE);

    if(!_personFile)
    {
        cerr << "Problem opening output file: " << OUTFILE << endl;
        inputFile.close();
        return -2;
    }

    numberRecords = 0;

    memset(inBuffer, ' ', sizeof(inBuffer));

    while(true)
    {
        memset(inBuffer, ' ', sizeof(inBuffer));
        inputFile.getline(inBuffer, sizeof(inBuffer));

        if(inputFile.eof())
            break;
        _personFile.seekp((numberRecords + 1) * DATALENGTH);
        _personFile.write(inBuffer, DATALENGTH);
        ++numberRecords;
    }
    _personFile.seekp(0);
    _personFile.write((char *) &numberRecords, sizeof(numberRecords));

    _personFile.seekp(DATALENGTH);
    _personFile.write(inBuffer, sizeof(inBuffer));

    inputFile.close();
    _personFile.close();

    cout << "Number of valid records written to " << OUTFILE << ": " << numberRecords << endl;

    return 0;
}
