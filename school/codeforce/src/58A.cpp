#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    cin >> s;

    char hello[] = {'h', 'e', 'l', 'l', 'o'};
    int current = 0;
    for(auto it: s)
    {
        if(it == hello[current] && hello[current] != 'o')
            current++;
        else if(it == hello[current] && hello[current] == 'o')
        {
            cout << "YES\n";
            return 0;
        }
    }
    cout << "NO\n";
}