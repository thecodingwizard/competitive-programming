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

int dp[2][2][2][5001];

template<class T> bool ckmin(T &a, const T &b) {
    return b < a ? a = b, 1 : 0;
}

void solve() {
    int n; cin >> n;
    vector<int> A(n);
    int ct = 0;
    set<int> nums;
    F0R(i, n) {
        cin >> A[i];
        if (A[i] == 2) ct++;
        else {
            nums.insert(A[i]);
        }
    }

    F0R(i, 2) F0R(k, 2) F0R(j, n+1) dp[0][i][k][j] = inf;
    dp[0][0][sz(nums) == 2 ? 0 : 1][ct] = 0;
    dp[0][1][sz(nums) == 2 ? 0 : 1][ct] = 0;

    F0R(i, n) {
        F0R(j, 2) {
            F0R(l, 2) {
                F0R(k, n+1) {
                    dp[(i+1)%2][j][l][k] = inf;
                }
            }
        }
        F0R(j, 2) {
            F0R(l, 2) {
                F0R(k, n+1) {
                    int cur = dp[i%2][j][l][k];
                    if (cur != inf) {
                        if (A[i] == 2) {
                            if (k > 0) {
                                ckmin(dp[(i+1)%2][0][0 != j ? 1 : l][k-1], cur);
                                ckmin(dp[(i+1)%2][1][1 != j ? 1 : l][k-1], cur);
                            }
                            ckmin(dp[(i+1)%2][j][l][k], cur);
                        } else if (A[i] == j) {
                            ckmin(dp[(i+1)%2][j][l][k], cur);
                        } else {
                            ckmin(dp[(i+1)%2][j][l][k], cur+1);
                            if (k > 0) ckmin(dp[(i+1)%2][!j][1][k-1], cur+1);
                        }
                    }
                }
            }
        }
    }

    int best = inf;
    F0R(i, n) {
        best = min(best, min(dp[n%2][0][1][i], dp[n%2][1][1][i]));
    }
    if (best == inf) cout << -1 << endl;
    else cout << best << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
