#include <fstream>
#include <string>
#include <cstdio>

using namespace std;
class Person;

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
    Person SearchByRecordNumber(const int & inRecordNumber);
    void UpdatePerson(Person & aPerson);
    void AddPerson(Person & aPerson);
private:
    int _numberPersons;
    int _recordSize;
    int _currentRecordNumber;
    fstream _personFile;
};
