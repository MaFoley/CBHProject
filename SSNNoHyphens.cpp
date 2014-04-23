#include <string>

using namespace std;

string SSNNoHyphens( const string & aString)
{
    if(aString.length() < 9 || aString[3] != '-')
        return aString;
    return aString.substr(0,3)
         + aString.substr(4,2)
         + aString.substr(7,4);
}
