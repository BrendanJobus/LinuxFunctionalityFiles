#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, error;
    cin >> n;
    int n1 = n - 1, n2 = n - 2;
    int error1 = 0, error2 = 0, error3 = 0;
    while(n != 0)
    {
        cin >> error;
        error1 += error;
        n--;
    }
    while(n1 != 0)
    {
        cin >> error;
        error2 += error;
        n1--;
    }
    while(n2 != 0)
    {
        cin >> error;
        error3 += error;
        n2--;
    }

    int firstError = error1 - error2, secondError = error2 - error3;
    cout << firstError << endl << secondError << endl;

    return 0;
}