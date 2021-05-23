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

int dp[2][4][4][4][4];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    string s; cin >> s;
    F0R(i, 4) F0R(j, 4) F0R(l, 4) F0R(m, 4) {
        dp[0][i][j][l][m] = i == 0 && j == 0 && m == 0 && l == 0 ? 0 : -inf;
    }
    F0R(i, n) {
        int x = 1;
        if (s[i] == 'F') x = 2;
        if (s[i] == 'B') x = 3;
        
        F0R(a, 4) F0R(b, 4) F0R(d, 4) F0R(e, 4) {
            dp[(i+1)%2][a][b][d][e] = -inf;
        }
        F0R(a, 4) F0R(b, 4) F0R(d, 4) F0R(e, 4) {
            int base = dp[i%2][a][b][d][e];
            if (base == -inf) continue;
            set<int> g = {a,b,x}; g.erase(0);
            set<int> h = {d,e,x}; h.erase(0);
            dp[(i+1)%2][b][x][d][e] = max(dp[(i+1)%2][b][x][d][e], base+(int)g.size());
            dp[(i+1)%2][a][b][e][x] = max(dp[(i+1)%2][a][b][e][x], base+(int)h.size());
        }
    }

    int best = 0;
    F0R(i, 4) F0R(j, 4) F0R(l, 4) F0R(m, 4) {
        best = max(best, dp[n%2][i][j][l][m]);
    }
    cout << best << endl;

    return 0;
}
