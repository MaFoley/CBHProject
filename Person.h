#include <string>
using namespace std;

string SSNHyphens(const string &);
string SSNNoHyphens(const string &);
class Person
{
    public:
        Person();
        ~Person() {}
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

        //Note that _SSN is ALWAYS stored without hyphens
        void SetSSN(const & inSSN) { _SSN = SSNNoHyphens(inSSN); }
        void SetOLN(const string & inOLN) { _OLN = inOLN; }
        void SetStateCode(const string & inStateCode) { _stateCode = inStateCode; }
        void SetCountyCode(const string & inCountyCode) { _countyCode = inCountyCode; }
        void SetlastName(const string & inLastName) { _lastName = inLastName; }
        void SetFirstName(const string & inFirstName) { _firstName = inFirstName; }
        void SetMI(const string & inMI) { _MI = inMI; }
        void Setstreet(const string & instreet) { _street = instreet; }
        void Setcity(const string & incity) { _city = incity; }
        void Setzip(const string & inzip) { _zip = inzip; }


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
        
