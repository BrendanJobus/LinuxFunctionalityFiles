#include <bits/stdc++.h>
using namespace std;

int main()
{
    int tests;
    cin >> tests;
    int a;
    while(tests--)
    {
        cin >> a;
        if(360 % (180 - a) == 0)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
}