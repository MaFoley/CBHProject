#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include "PersonFile.h"

using namespace std;

PersonFile::PersonFile()
{
    char INFILE[] =  "Person.db";
    ifstream inputFile;

    inputFile.open(INFILE);
    if( !inputFile)
    {
        cerr << "Error opening file: " << INFILE << endl;
    }
    else
    {
        inputFile.seekg(0);
        inputFile.read((char *) &_numberPersons, sizeof(_numberPersons));
    }
}

PersonFile::~PersonFile()
{
    inputFile.close();
}

