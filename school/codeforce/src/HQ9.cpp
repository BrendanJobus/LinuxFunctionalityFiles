#include <iostream>
using namespace std;

int main()
{
    string input;
    cin >> input;

    char inputChar[input.size() + 1];
    input.copy(inputChar, input.size() + 1);

    for(int i = 0; i < input.size() + 1; i++)
    {
        if(inputChar[i] == 'H' || inputChar[i] == 'Q' || inputChar[i] == '9')
        {
            cout << "YES\n";

            return 0;
        }
    }

    cout << "NO\n";
}