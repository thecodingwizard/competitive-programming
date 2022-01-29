// lol I think this solution might be O(n^3)? I didn't precompute repeatedly pairing cows
// until >= K distance...

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define ii pair<int, ll>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define inf 1000000010

template<class T> bool ckmax(T &a, const T &b) {
    return a < b ? a = b, 1 : 0;
}

int n, K;
vector<ii> G, H;
vector<int> gi, hi;
vector<pair<char, ii>> all;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t >> n >> K;
    ll tot = 0;
    for (int i = 0; i < n; i++) {
        char c; cin >> c; int x, w; cin >> x >> w;
        if (c == 'H') {
            H.pb(mp(x, w));
            hi.pb(i);
        } else {
            G.pb(mp(x, w));
            gi.pb(i);
        }
        all.pb(mp(c, mp(x, w)));
        tot += w;
    }
    if (t == 1) {
        ll dp[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dp[i][j] = 0;
            }
        }
        for (int i = 0; i < G.size(); i++) {
            for (int j = 0; j < H.size(); j++) {
                dp[i][j] = max(i>0?dp[i-1][j]:0, j>0?dp[i][j-1]:0);
                if (abs(G[i].f - H[j].f) <= K) {
                    dp[i][j] = max(dp[i][j], (i>0&&j>0?dp[i-1][j-1]:0)+G[i].s+H[j].s);
                }
            }
        }
        cout << tot-dp[G.size()-1][H.size()-1] << endl;
    } else {
        // assert(n <= 300);
        // ll dp[n+1][n+1][n+2];
        // for (int i = 0; i <= n; i++) for (int j = 0; j <= n; j++) for (int k = 0; k <= n+1; k++) dp[i][j][k] = -1e18;
        // ll best = -1e18;
        // dp[0][0][0] = 0;
        // for (int i = 0; i <= G.size(); i++) {
        //     for (int j = 0; j <= H.size(); j++) {
        //         for (int k = 0; k <= n; k++) {
        //             // option 1: pair i and j
        //             if (i < G.size() && j < H.size()) {
        //                 if (abs(G[i].f-H[j].f) <= K) {
        //                     ckmax(dp[i+1][j+1][k], dp[i][j][k]);
        //                 }
        //             }
        //             // option 2: skip i
        //             if (i < G.size()) {
        //                 if (k == 0 || all[k-1].f == 'G' || G[i].f-all[k-1].s.f > K) {
        //                     ckmax(dp[i+1][j][gi[i]+1], dp[i][j][k]+G[i].s);
        //                 }
        //             }
        //             // option 3: skip j
        //             if (j < H.size()) {
        //                 if (k == 0 || all[k-1].f == 'H' || H[j].f-all[k-1].s.f > K) {
        //                     ckmax(dp[i][j+1][hi[j]+1], dp[i][j][k]+H[j].s);
        //                 }
        //             }
        //         }
        //     }
        // }
        // for (int i = 0; i <= n; i++) {
        //     ckmax(best, dp[G.size()][H.size()][i]);
        // }
        // cout << best << endl;
        ll dp[G.size()+1][H.size()+1][3];
        for (int i = 0; i <= G.size(); i++) for (int j = 0; j <= H.size(); j++) for (int k = 0; k <= 2; k++) dp[i][j][k] = -1e18;
        ll best = -1e18;

        dp[0][0][0] = 0;
        for (int i = 0; i <= G.size(); i++) {
            for (int j = 0; j <= H.size(); j++) {
                for (int k = 2; k >= 0; k--) {
                    // option 1: pair i and j
                    if (i < G.size() && j < H.size() && abs(G[i].f - H[j].f) <= K) {
                        ckmax(dp[i+1][j+1][k], dp[i][j][k]);
                    }
                    // option 2: skip i
                    if (i < G.size()) {
                        if (k == 0 || k == 1 || G[i].f - H[j-1].f > K) {
                            ckmax(dp[i+1][j][1], dp[i][j][k] + G[i].s);
                        }
                    }
                    // option 3: skip j
                    if (j < H.size()) {
                        if (k == 0 || k == 2 || H[j].f - G[i-1].f > K) {
                            ckmax(dp[i][j+1][2], dp[i][j][k] + H[j].s);
                        }
                    }
                    // option 4: pair until k can be cleared
                    if (k > 0) {
                        int a = i, b = j;
                        while (a <= G.size() && b <= H.size()) {
                            if ((k == 1 && b < H.size() && H[b].f - G[i-1].f > K) || (k == 2 && a < G.size() && G[a].f - H[j-1].f > K)) {
                                ckmax(dp[a][b][0], dp[i][j][k]);
                                break;
                            }
                            if (a == G.size() || b == H.size() || abs(G[a].f-H[b].f) > K) break;
                            a++, b++;
                        }
                    }
                }
            }
        }

        for (int k = 0; k <= 2; k++) ckmax(best, dp[G.size()][H.size()][k]);

        cout << best << endl;
    }

    return 0;
}
