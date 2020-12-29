/*
 * Same solution as editorial; lots of DP
 */

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

ll dp(int s, int t, int mx);

int n, k, q; 
int A[60][60];
int S[60], T[60];
int bs[60], bt[60];

int memo2[120][120][60];
int memo3[120][120][60];
ll sToX(int s, int x, int mx) {
    if (memo2[s][x][mx] != -1) return memo2[s][x][mx];
    ll ans = 0;
    F0R(i, n) {
        if (A[i][x]) {
            ans = (ans + dp(s, i, mx-1)) % mod;
        }
    }
    return memo2[s][x][mx] = ans;
}
ll xToT(int x, int t, int mx) {
    if (memo3[x][t][mx] != -1) return memo3[x][t][mx];
    ll ans = 0;
    F0R(i, n) {
        if (A[x][i]) {
            ans = (ans + dp(i, t, mx-1)) % mod;
        }
    }
    return memo3[x][t][mx] = ans;
}

int memo[120][120][60];
ll dp(int s, int t, int mx) {
    if (mx < 0) return 0;
    if (t >= n && bt[t-n]>mx) return 0;
    if (memo[s][t][mx] != -1) return memo[s][t][mx];

    ll ans = 0;
    
    if (s < n && t < n) {
        if (s == t) ans++;
    }

    // case 1: don't press mx
    ans = (ans + dp(s, t, mx-1));

    // case 2: press mx in the middle
    F0R(x, n) {
        ans = (ans + sToX(s, x, mx)*xToT(x, t, mx))%mod;
    }
    
    // case 3: press mx first
    if (s < n) ans = (ans + xToT(s, t, mx)) % mod;
    else if (s >= n && mx == bs[s-n]) {
        if (S[s-n] == t) ans = (ans+1)%mod;
        ans = (ans + xToT(S[s-n], t, mx)) % mod;
    }

    // case 4: press mx last
    if (t < n) ans = (ans + sToX(s, t, mx)) % mod;
    else if (t >= n && mx == bt[t-n]) {
        if (T[t-n] == s) ans = (ans+1)%mod;
        ans = (ans + sToX(s, T[t-n], mx)) % mod;
    } 

    return memo[s][t][mx] = ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k >> q;

    F0R(i, n) F0R(j, n) { char c; cin >> c; A[i][j] = c == '1'; }
    F0R(i, n+q) F0R(j, n+q) F0R(x, k) memo[i][j][x] = -1;
    F0R(i, n+q) F0R(j, n+q) F0R(x, k) memo2[i][j][x] = -1;
    F0R(i, n+q) F0R(j, n+q) F0R(x, k) memo3[i][j][x] = -1;
    F0R(i, q) {
        cin >> bs[i] >> S[i] >> bt[i] >> T[i];
        S[i]--; bs[i]--; T[i]--; bt[i]--;

        int extra = bs[i] == bt[i] && S[i] == T[i] ? 1 : 0;
        
        cout << dp(i+n, i+n, k-1)+extra << endl;
    }

    return 0;
}
