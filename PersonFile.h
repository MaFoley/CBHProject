#include <fstream>
#include <string>

class PersonFile
{
public:
    PersonFile();
    ~PersonFile();
    int GetNumberPersons() const { return _numberPersons; }
    int GetCurrentRecordNumber() const { return _currentRecordNumber; }
private:
    int _numberPersons;
    int _recordLength;
    int _currentRecordNumber;
    fstream _personFile;
};
