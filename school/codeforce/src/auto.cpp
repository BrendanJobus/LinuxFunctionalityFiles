#include <bits/stdc++.h>
using namespace std;

int main()
{
    set<int> s = {8, 2, 3, 1};  // sets store the value as the key aswell so they are naturally ordered
    vector<int> v = {8, 2, 3, 1};



    for(auto it: s)
    {
        it *= 2;
        cout << it << ' ';
    }
    cout << endl;

    for(auto it: s)
    {
        cout << it << ' ';
    }
    cout << endl;


    for(auto &it: v)
        it *= 2;
    for(auto it: v)
        cout << it << ' ';

    cout << endl;
}