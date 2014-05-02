#include <fstream>
#include <string>
#include <cstdio>
/*
 This Class deals with writing and reading from the person.db file.
 the Searches require an exact match for 9 characters, i.e. '1' only matches on "1        "
 and not "123456789"
 * */

using namespace std;
class Person;

class PersonFile
{
public:
    PersonFile();
    ~PersonFile();
    int GetNumberPersons() const { return _numberPersons; }
    int GetCurrentRecordNumber() const { return _currentRecordNumber; }
    void SetCurrentRecordNumber(const int inRecordNumber) {_currentRecordNumber = inRecordNumber; }
    void SortBySSN();
    Person SearchBySSN(const string & inSSN);
    Person SearchByOLN(const string & inOLN);
    Person SearchByRecordNumber(const int & inRecordNumber);
    void UpdatePerson(Person & aPerson);
    void AddPerson(Person & aPerson);
private:
    int _numberPersons;
    int _recordSize;
    int _currentRecordNumber;
    fstream _personFile;
};
