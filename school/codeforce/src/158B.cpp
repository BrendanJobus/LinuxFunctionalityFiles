#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int groupSize[5] = {0};
    int  groupi;
    while(n--)
    {
        cin >> groupi;
        groupSize[groupi]++;
    }

    int total = groupSize[4] + groupSize[3] + (groupSize[2] / 2);
    groupSize[1] -= groupSize[3];
    if(groupSize[2] % 2 == 1)
    {
        total += 1;
        groupSize[1] -= 2;
    }

    if(groupSize[1] > 0)
    {
        total += (groupSize[1] + 3) / 4;
    }

    cout << total << endl;
    return 0;
}