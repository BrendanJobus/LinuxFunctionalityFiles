#include <bits/stdc++.h>
using namespace std;

int main()
{
    int numOfCoins;
    cin >> numOfCoins;
    vector<int> coins;
    int coin, total = 0;

    for(int j = 0; j < numOfCoins; j++)
    {
        scanf("%d", &coin);
        coins.push_back(coin);
        total += coin;
    }

    sort(coins.begin(), coins.end());

    vector<int>::reverse_iterator rit;
    int coinsNeeded = 0;
    rit = coins.rbegin();    
    for(int myTotal = 0; myTotal * 2 <= total; rit++)
    {        
        coin = *rit;
        myTotal += coin;
        coinsNeeded++;
    }
    
    cout << coinsNeeded << endl;
}