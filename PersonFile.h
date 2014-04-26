#include <fstream>
#include <string>
#include <cstdio>
#include "Person.h"

using namespace std;

class PersonFile
{
public:
    PersonFile();
    ~PersonFile();
    int GetNumberPersons() const { return _numberPersons; }
    int GetCurrentRecordNumber() const { return _currentRecordNumber; }
    void SortBySSN();
    Person SearchBySSN(const string & inSSN);
    Person SearchByOLN(const string & inOLN);
private:
    int _numberPersons;
    int _recordSize;
    int _currentRecordNumber;
    fstream _personFile;
};
