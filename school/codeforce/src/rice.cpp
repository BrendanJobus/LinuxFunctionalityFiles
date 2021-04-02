#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    int grains, a, b, c, d;
    for(int i = 0; i < t; i++)
    {
        cin >> grains >> a >> b >> c >> d;
        if( (a - b) * grains > c + d || (a + b) * grains < c - d )
            cout << "No" << endl;
        else
            cout << "Yes" << endl;
    }
}