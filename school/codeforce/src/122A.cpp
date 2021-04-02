#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    int lucky[] = {4, 7, 47, 74, 444, 447, 474, 477, 744, 747, 777};
    for(int i = 0; i < 11; i++)
    {
        if(n % lucky[i] == 0)
        {
            cout << "YES\n";
            return 0;
        }
    }
    cout << "NO\n";    
}