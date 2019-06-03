#include <iostream>
#include <string>
#include <utility>
#include <sstream>
#include <algorithm>
#include <stack>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <bitset>
#include <cmath>

using namespace std;

#define INF 1000000000
#define LSOne(S) (S & (-S))
typedef vector<int> vi;

int n, k, optimal;
bitset<101> colored;
bitset<101> optimalColored;
vi adj[101];

void recurse(int i, int ct) {
    if (ct > optimal) {
        optimal = ct;
        optimalColored = colored;
    }
    if (i > n) return;
    recurse(i + 1, ct);
    auto connected = adj[i];
    for (int x = 0; x < connected.size(); x++) {
        if (colored[connected[x]]) return;
    }
    colored[i] = true;
    recurse(i + 1, ct + 1);
    colored[i] = false;
}

int main() {
    int m;
    cin >> m;
    while (m--) {
        cin >> n >> k;
        optimal = 0;
        colored.reset();
        for (auto &i : adj) i.clear();
        for (int i = 0; i < k; i++) {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        recurse(1, 0);
        cout << optimal << endl;
        bool first = true;
        for (int i = 1; i <= 100; i++) {
            if (optimalColored[i]) {
                if (!first) cout << " ";
                first = false;
                cout << i;
            }
        }
        cout << endl;
    }
    return 0;
}