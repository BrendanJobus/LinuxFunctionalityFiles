#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;

    int a[n];
    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    int lastInt = 1000000001;
    int inARow = 1, maxInARow = 0;;
    for(int i = 0; i < n; i++)
    {
        if(a[i] >= lastInt)
            inARow++;
        else
        {
            if(inARow > maxInARow)
                maxInARow = inARow;
            inARow = 1;
        }
        lastInt = a[i];
    }
    if(inARow > maxInARow)
        maxInARow = inARow;
    cout << maxInARow << endl;
}