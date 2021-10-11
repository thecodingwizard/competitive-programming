#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define ii pair<int, int>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define inf 1000000010

int r, c, k;
vector<vector<bool>> blocked;

int solve() {
    vector<int> numCars(c, 0);
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < k; j++) {
            numCars[i] += blocked[j][i];
        }
    }
    int best = 1e9;
    for (int moves = 0; moves < r; moves++) {
        int cur = moves;
        for (int i = 0;i < c; i++) {
            if (k+moves<r) numCars[i] += blocked[k+moves][i];
            if (k+moves<r&&blocked[k+moves][i]) {
                cur++;
                continue;
            }
            if (numCars[i] > k) {
                cur++;
            }
        }
        best = min(best, cur);
    }
    return best;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        cout << "Case #" << tc << ": ";

        cin >> r >> c >> k; --k;
        blocked.assign(r, vector<bool>());
        for (int i = 0; i < r; i++) {
            blocked[i].assign(c, 0);
        }
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                char c; cin >> c;
                blocked[i][j] = c == 'X';
            }
        }
        int best = solve();
        for (int i = 0; i < r/2; i++) {
            for (int j = 0; j < c; j++) {
                swap(blocked[i][j], blocked[r-1-i][j]);
            }
        }
        k = r-1-k;
        best = min(best, solve());
        cout << best << endl;
    }

    return 0;
}
