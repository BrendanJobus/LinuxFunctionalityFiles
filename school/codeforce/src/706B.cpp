#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, x, q, m;
    cin >> n;
    vector<int> prices;

    while(n--)
    {
        cin >> x;
        prices.push_back(x);
    }
    cin >> q;

    sort(prices.begin(), prices.end());

    int toSpend, placesToSpend;
    while(q--)
    {
        placesToSpend = 0;
        cin >> toSpend;
        for(auto it: prices)
        {
            if(toSpend > it)
                break;
            placesToSpend++;
        }
        cout << placesToSpend << endl;
    }

    return 0;
}