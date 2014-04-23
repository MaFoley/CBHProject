#include <string>

using namespace std;

string SSNHyphens( const string & aString)
{
    if(aString.length() < 9 || aString[3] == '-')
        return aString;
    return aString.substr(0,3) + '-' 
         + aString.substr(3,2) + '-' 
         + aString.substr(5,4);
}
