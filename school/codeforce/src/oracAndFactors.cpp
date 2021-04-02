#include <bits/stdc++.h>
#define evenDivisor 2;
using namespace std;

int main()
{
    int t;
    cin >> t;
    int n, k;
    for(int i = 0; i < t; i++)
    {
        cin >> n >> k;
        if(n % evenDivisor == 0)
            n += (evenDivisor * k);
        else
        {
            int x = 3;
            while(n % x != 0)
            {
                if(x * 2 >= n)
                    x = n;
                else
                    x += 2;
            }
            n += x;
            n += (evenDivisor * --k);
        }
        cout << n << endl;
    }
}