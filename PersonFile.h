#include <fstream>
#include <string>
#include <cstdio>

using namespace std;

class PersonFile
{
public:
    PersonFile();
    ~PersonFile();
    int GetNumberPersons() const { return _numberPersons; }
    int GetCurrentRecordNumber() const { return _currentRecordNumber; }
    void SortBySSN();
private:
    int _numberPersons;
    int _recordSize;
    int _currentRecordNumber;
    fstream _personFile;
};
