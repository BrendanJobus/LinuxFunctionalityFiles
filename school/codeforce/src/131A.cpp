#include <bits/stdc++.h>
using namespace std;

#define lowercaseStart 97
#define lowercaseEnd 122
#define uppercaseStart 65
#define uppercaseEnd 90
#define caseTransformer 32

int main()
{
    string input;
    cin >> input;

    if(input.size() == 1 && input[0] >= lowercaseStart && input[0] <= lowercaseEnd)
    {
        char character = input[0] - caseTransformer;
        cout << character << endl; 
        return 0;
    }

    for(int character = 1; character < input.size(); character++)
    {
        if(input[character] < uppercaseStart || input[character] > uppercaseEnd)
        {
            cout << input << endl; 
            return 0;
        }
    }
    string s = "";
    if(input[0] >= lowercaseStart && input[0] <= lowercaseEnd)
    {
        char current = input[0] - caseTransformer;
        s += current;
        for(int i = 1; i < input.size(); i++)
        {
            current = input[i] + caseTransformer;
            s += current;
        }
    }
    else
    {
        char current;
        for(int i = 0; i < input.size(); i++)
        {
            current = input[i] + caseTransformer;
            s += current;
        }
    }
    cout << s << endl;
}