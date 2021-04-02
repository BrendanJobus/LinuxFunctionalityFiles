#include <bits/stdc++.h>
using namespace std;

int main()
{
    int can;
    cin >> can;
    can--;
    string line[5] = {"Sheldon", "Leonard", "Penny", "Rajesh", "Howard"};

    while(can >= 5)
    {
        can -= 5;
        can /= 2;
    }
    cout << line[can] << endl;
    return 0;
}