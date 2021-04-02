#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n, m, a;
    cin >> n >> m >> a;
    long long nAxisStones = 1 + ((n - 1) / a);
    long long mAxisStones = 1 + ((m - 1) / a);
    cout  << nAxisStones * mAxisStones << endl;
}