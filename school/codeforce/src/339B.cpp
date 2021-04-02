#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n, m;
    cin >> n >> m;

    vector<long long> tasks;
    long long a;
    for(int i = 0; i < m; i++)
    {
        cin >> a;
        tasks.push_back(a);
    }

    long long current = 1, time = 0;
    for(int i = 0; i < m; i++)
    {
        if(current < tasks[i])
        {
            time += tasks[i] - current;
            current = tasks[i];
        }
        else if(current > tasks[i])
        {
            time += n - current;
            time += tasks[i];
            current = tasks[i];
        }
    }
    cout << time << endl;
}