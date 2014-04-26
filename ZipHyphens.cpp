#include <string>

using namespace std;

string ZipHyphens( const string & aString)
{
    if(aString.length() < 9 || aString[5] == '-')
        return aString;
    return aString.substr(0,5) + '-' 
         + aString.substr(5,4);
}
