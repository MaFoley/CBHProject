#include <string>
/*
 *There are fewer members for Vehicle than Person.  However, most of them are Codes for information in the auxiliary files
 */
using namespace std;

string SSNHyphens(const string &);
string SSNNoHyphens(const string &);
class Vehicle
{
    public:
        Vehicle();
        ~Vehicle() {}
        void MakeVehicle(const string & inRecord);
        string Recordify();

        void DisplayVehicle();
        void PrintVehicle();

        //All the gets
        const string & GetSSN() const { return _SSN;}
        string GetSSNWithHyphens() const { return SSNHyphens(_SSN); }
        const string & GetVTypeCode() const { return _VTypeCode;}
        const string & GetVMakeCode() const { return _VMakeCode;}
        const string & GetTopColorCode() const { return _topColorCode;}
        const string & GetBottomColorCode() const { return _bottomColorCode;}
        const string & GetTag() const { return _tag;}
        const bool & IsFound() const { return _found; }
        const bool & IsDeleted() const { return _deleted; }

        //These are all the sets
        void SetSSN(const string & inSSN) { _SSN = SSNNoHyphens(inSSN); }

        void SetVTypeCode(const string & inVType);
        void SetTopColorCode(const string & inTopColorCode);
        void SetBottomColorCode(const string & inBottomColorCode);
        void SetVMakeCode(const string & inVMake);
        void SetFirstName(const string & inFirstName);
        void SetMI(const string & inMI);
        void SetTag(const string & intag);
        void SetCity(const string & incity);
        void SetZip(const string & inzip);
        void SetFound(const bool & inFound) { _found = inFound; }
        void SetDeleted(const bool & inDeleted) { _deleted = inDeleted; }

    private:
        string _SSN;
        string _VTypeCode;
        string _VMakeCode;
        string _topColorCode;
        string _bottomColorCode;
        string _tag;
        int _length;
        bool _found;
        bool _deleted;
        
};

