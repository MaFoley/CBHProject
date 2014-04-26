#include <string>
using namespace std;

string SSNHyphens(const string &);
string SSNNoHyphens(const string &);
class Person
{
    public:
        Person();
        ~Person() {}

        void MakePerson(const string & inRecord);
        string Recordify();
        void DisplayPerson();
//
        //All the gets
        const string & GetSSN() const { return _SSN;}
        string GetSSNWithHyphens() const { return SSNHyphens(_SSN); }
        const string & GetOLN() const { return _OLN;}
        const string & GetStateCode() const { return _stateCode;}
        const string & GetCountyCode() const { return _countyCode;}
        const string & GetLastName() const { return _lastName;}
        const string & GetFirstName() const { return _firstName;}
        const string & GetMI() const { return _MI;}
        const string & GetStreet() const { return _street;}
        const string & GetCity() const { return _city;}
        const string & GetZip() const { return _zip;}
        const bool & IsDeleted() const { return _deleted; }

        //Note that _SSN is ALWAYS stored without hyphens
        //These are all the sets
        void SetSSN(const string & inSSN) { _SSN = SSNNoHyphens(inSSN); }

        void SetOLN(const string & inOLN);
        void SetStateCode(const string & inStateCode);
        void SetCountyCode(const string & inCountyCode);
        void SetLastName(const string & inLastName);
        void SetFirstName(const string & inFirstName);
        void SetMI(const string & inMI);
        void SetStreet(const string & instreet);
        void SetCity(const string & incity);
        void SetZip(const string & inzip);
        void SetFound(const bool & inFound) { _found = inFound; }

    private:
        string _SSN;
        string _OLN;
        string _stateCode;
        string _countyCode;
        string _lastName;
        string _firstName;
        string _MI;
        string _street;
        string _city;
        string _zip;
        int _length;
        bool _found;
        bool _deleted;
        
};

