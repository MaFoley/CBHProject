#include <string>

using namespace std;

string ZipNoHyphens(const string & aString)
{
    if(aString.length() < 10 || aString[5] != '-')
        return aString;
    return aString.substr(0,5)
         + aString.substr(6,4)
}
