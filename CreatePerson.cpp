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

    char inBuffer[112];

    ifstream inputFile;
    ofstream outputFile;

    inputFile.open(INFILE);

    if(!inputFile)
    {
        cerr << "Problem opening input file: " << INFILE << endl;
        return -1;
    }
    cout << INFILE << " successfully opened..." << endl;

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
        outputFile.seekp((numberRecords + 1) * DATALENGTH);
        outputFile.write(inBuffer, DATALENGTH);
        cerr << inBuffer << endl;
        ++numberRecords;
    }
    outputFile.seekp(0);
    outputFile.write((char *) &numberRecords, sizeof(numberRecords));

    outputFile.seekp(DATALENGTH);
    outputFile.write(inBuffer, sizeof(inBuffer));

    inputFile.close();
    outputFile.close();

    cout << "Number of valid records written to " << OUTFILE << ": " << numberRecords << endl;

    return 0;
}
