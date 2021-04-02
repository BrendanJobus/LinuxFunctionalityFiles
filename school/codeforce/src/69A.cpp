#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int x, y, z;
    int xForce = 0, yForce = 0, zForce = 0;
    for(int i = 0; i < n; i++)
    {
        cin >> x >> y >> z;
        xForce += x;
        yForce += y;
        zForce += z;
    }
    if(xForce == 0 && yForce == 0 && zForce == 0)
        cout << "YES\n";
    else
        cout << "NO\n";
}