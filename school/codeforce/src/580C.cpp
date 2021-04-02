#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> a;

    int tmp;
    for(int i = 0; i < n; i++ ) {
        cin >> tmp;
        a.push_back(tmp);
    }

    vector<vector<int>> edges;
    for(int i = 0; i < n - 1; i++) {
        cin >> tmp;
        edges.push_back(new vector<int> [tmp]);
        cin >> tmp;
        edges[i].push_back(tmp);
    }
}