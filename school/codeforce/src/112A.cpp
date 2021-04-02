#include <bits/stdc++.h>
using namespace std;
#define caseTransformer 32
#define lowercaseStart 97

int main()
{
    string string1, string2;
    cin >> string1 >> string2;
    
    int value1 = 0, value2 = 0;
    for(int i = 0; i < string1.size(); i++)
    {
        if(string1[i] < lowercaseStart)
        {
            string1[i] += caseTransformer;
        }
        if(string2[i] < lowercaseStart)
        {
            string2[i] += caseTransformer;
        }
    }

    if(string1 < string2)
    {
        cout << -1 << endl;
    }
    else if(string1 == string2)
    {
        cout << 0 << endl;
    }
    else
    {
        cout << 1 << endl;
    }

    return 0;
}