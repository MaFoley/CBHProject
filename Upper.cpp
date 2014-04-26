#include <string>

using namespace std;

void Upper(string & aString)
{
    for(int i = 0; i < aString.size(); ++i)
    {
        if(aString[i] >= 97 && aString[i] <= 122)
            aString[i] -= 32;
    }
    return;
}
