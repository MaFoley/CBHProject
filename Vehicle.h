#include <string>
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
//
        //All the gets
        const string & GetSSN() const { return _SSN;}
        const string & GetVType() const { return _VType;}
        const string & GetTopColorCode() const { return _topColorCode;}
        const string & GetBottomColorCode() const { return _bottomColorCode;}
        const string & GetVMake() const { return _VMake;}
        const string & GetTag() const { return _tag;}
        const bool & IsDeleted() const { return _deleted; }

        //Note that _SSN is ALWAYS stored without hyphens
        //These are all the sets
        void SetSSN(const string & inSSN) { _SSN = SSNNoHyphens(inSSN); }
        void SetVType(const string & inVType);
        void SetTopColorCode(const string & inTopColorCode);
        void SetVMake(const string & inVMake);
        void SetBottomColorCode(const string & inBottomColorCode);
        void SetTag(const string & inTag);
        void SetFound(const bool & inFound) { _found = inFound; }

    private:
        string _SSN;
        string _VType;
        string _topColorCode;
        string _bottomColorCode;
        string _VMake;
        string _tag;
        int _length;
        bool _found;
        bool _deleted;
        
};

