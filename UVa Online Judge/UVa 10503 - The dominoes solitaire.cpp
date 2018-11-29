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

int n, m;
pair<int, int> l, r;
vector<pair<int, int>> pieces;

int count(int x) {
    int c = 0;
    while (x != 0) {
        c++;
        x -= LSOne(x);
    }
    return c;
}

bool solution_exists(int mask, int prev) {
    if (count(mask) == n) {
        if (prev == r.first) return true;
    }
    for (int i = 0; i < m; i++) {
        if (mask & (1 << i)) continue;
        auto piece = pieces[i];
        if (piece.first == prev) {
            if (solution_exists(mask | (1 << i), piece.second)) return true;
        }
        if (piece.second == prev) {
            if (solution_exists(mask | (1 << i), piece.first)) return true;
        }
    }
    return false;
}

int main() {
    while (cin >> n && n) {
        pieces.clear();
        cin >> m;
        cin >> l.first >> l.second;
        cin >> r.first >> r.second;
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            pieces.emplace_back(a, b);
        }
        if (solution_exists(0, l.second)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}