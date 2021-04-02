#include <bits/stdc++.h>
using namespace std;

#define uppercaseStart 65
#define uppercaseEnd 90
#define uppercaseTransformer 32

int main()
{
    string input;
    cin >> input;

    int characters = input.size();
    char current;
    for(int i = 0; i < input.size(); i++)
    {
        current = input.at(i);
        
        if(current == 'A' || current == 'E' || current == 'I' || current == 'O' || current == 'U' || current == 'Y' || current == 'y' || current == 'a' || current == 'e' || current == 'i' || current == 'o' || current == 'u')
        {
            input.erase(i, 1);
            i--;
        }
        else
        {
            if(current >= uppercaseStart && current <= uppercaseEnd)
            {
                current += uppercaseTransformer;
                input.replace(i, 1, 1, current);
            }

            if(i != 0)
            {
                string preString = input.substr(0, i);
                string postString = input.substr(i, input.size() - i);
                preString += ".";
                input = preString + postString;
                i++;
            }
            else
            {
                input = "." + input;
                i++;
            }
            
        }
    }
    cout << input << endl;
}