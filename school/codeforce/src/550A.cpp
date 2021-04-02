#include <bits/stdc++.h>
using namespace std;

int main() {
    string input;
    cin >> input;

    int n = input.find("AB");
    if(n != -1) {
        input.erase(n, 2);
        n = input.find("BA");
        if(n == -1) {
            cout << "NO" << endl;
        }
        else { cout << "YES" << endl; }
    }
    else { cout << "NO" << endl; }
}