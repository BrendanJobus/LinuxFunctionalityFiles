#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> pieces;
    for(int i = 0; i < m; i++)
    {
        int f;
        scanf("%d", &f);
        pieces.push_back(f);
    }

    sort(pieces.begin(), pieces.end());
    
    int a = pieces.front(), b = pieces.back();

    int diff = 1001;
    int i = 0;

    for(int j = n - 1; j < pieces.size(); j++)
    {
        if(pieces.at(j) - pieces.at(i) < diff)
            diff = pieces.at(j) - pieces.at(i);
        i++;
    }

    cout << diff << endl;
}