#include <bits/stdc++.h>
using namespace std;

int main()
{
    int s, n, x, y, i;
    cin >> s >> n;
    vector<pair<int, int>> dragons;
    for(i = 0; i < n; i++)
    {
        cin >> x >> y;
        dragons.push_back({x, y});
    }

    sort(dragons.begin(), dragons.end());
    i = 0;
    while(i < n)
    {
        if(dragons[i].first >= s)
        {
            cout << "NO\n"; 
            return 0;
        }

        s += dragons[i].second;
        i++;
    }

    cout << "YES\n";
}