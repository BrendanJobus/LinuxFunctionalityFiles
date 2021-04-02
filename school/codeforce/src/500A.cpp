#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, t;
    cin >> n >> t;

    int j;
    vector<int> portals;
    int ai;
    for(j = 0; j < n - 1; j++)
    {
        cin >> ai;
        portals.push_back(ai);
    }

    int i = 1;
    j = 0;
    while(i < t)
    {
        i += portals[j];
        if(i == t)
        {
            cout << "YES\n";
            return 0;
        }
        j = i - 1;
    }
    cout << "NO\n";
}