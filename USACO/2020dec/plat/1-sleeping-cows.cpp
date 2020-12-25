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

const int mod = 1e9+7;

int n; 
vector<ii> A;

int memo[6000][3001][2];
ll dp(int idx, int numCows, int skippedCow) {
    if (idx == 2*n) {
        return numCows == 0 ? 1 : 0;
    }
    if (memo[idx][numCows][skippedCow] != -1) return memo[idx][numCows][skippedCow];

    ll ans = 0;
    if (A[idx].s == 1) {
        // barn
        if (numCows > 0) {
            ans = (ans+dp(idx+1, numCows-1, skippedCow)*numCows)%mod;
        }
        if (!skippedCow) {
            ans = (ans+dp(idx+1, numCows, skippedCow))%mod;
        }
    } else {
        // cow
        ans = (dp(idx+1, numCows+1, skippedCow) + dp(idx+1, numCows, 1))%mod;
    }
    return memo[idx][numCows][skippedCow] = ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    F0R(i, n) {
        int x; cin >> x;
        A.pb(mp(x, 0));
    }
    F0R(i, n) {
        int x; cin >> x;
        A.pb(mp(x, 1));
    }
    sort(all(A));

    F0R(i, 2*n) F0R(j, n+1) F0R(k, 2) memo[i][j][k] = -1;
    cout << dp(0, 0, 0) << endl;

    return 0;
}
