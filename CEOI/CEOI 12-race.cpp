/*
 * dp[i][j][0] = max path starting on i, bounded by [i...j] (counterclockwise)
 * dp[i][j][1] = max path starting on j, bounded by [i...j] (counterclockwise)
 *
 * Do another dp to handle the case where k = 1:
 * - for a fixed (j, i) where you go from j --> i, you can either go clockwise or counterclockwise from i,
 *   then cross the line once to get to x, then use the dp above to calculate the new value
 * - brute force over all x
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
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define inf 1000000010

#define maxn 500
int n, k; 
vector<int> adj[maxn];
vector<int> radj[maxn];
bool connected[maxn][maxn];

int memo[maxn][maxn][2];
int dp(int x, int y, bool onY) {
    if (memo[x][y][onY] != -1) return memo[x][y][onY];
    int best = 1;

    for (int i : adj[onY ? y : x]) {
        bool legal = false;
        if (x < y) {
            if (x < i && i < y) {
                legal = true;
            }
        } else {
            if (i > x || i < y) {
                legal = true;
            }
        }
        if (!legal) continue;

        best = max(best, 1 + max(dp(x, i, 1), dp(i, y, 0)));
    }

    return memo[x][y][onY] = best;
}

// path[i][x] = longest path to x starting from i, going counterclockwise
int path[maxn][maxn];
// going clockwise
int pathRev[maxn][maxn];

// return true if i --> j --> k is going counterclockwise
bool ccw(int i, int j, int k) {
    if (k < i) k += n;
    if (j < i) j += n;
    return i < j && j < k;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    F0R(i, n) {
        int x;
        while (cin >> x && x != 0) {
            --x;
            adj[i].pb(x);
            connected[i][x] = 1;
        }
    }

    int best = -1, bestIdx = -1;

    F0R(i, n) F0R(j, n) F0R(k, 2) memo[i][j][k] = -1;

    F0R(i, n) {
        for (int j : adj[i]) {
            int val = max(dp(i, j, 1), dp(j, i, 0));
            if (best < val) {
                best = val;
                bestIdx = i;
            }
        }
    }

    if (k) {
        F0R(i, n) {
            path[i][i] = 1;

            FOR(add, 0, n) {
                int j = (i+add)%n;

                if (connected[j][i]) {
                    FOR(add2, 1, n) {
                        int nxt = (j+add2)%n;
                        if (ccw(i, j, nxt) && path[i][nxt] > 0) {
                            int val = max(dp(nxt, i, 0), dp(j, nxt, 1)) + path[i][nxt] - 1;
                            if (best < val) {
                                best = val;
                                bestIdx = j;
                            }
                        }
                    }
                }

                if (path[i][j] > 0) {
                    for (int k : adj[j]) {
                        if (j == i || ccw(i, j, k)) path[i][k] = max(path[i][k], path[i][j]+1);
                    }
                }
            }

            pathRev[i][i] = 1;
            FOR(sub, 0, n) {
                int j = (i-sub+n)%n;

                if (connected[j][i]) {
                    FOR(sub2, 1, n) {
                        int nxt = (j-sub2+n)%n;
                        if (ccw(i, nxt, j) && pathRev[i][nxt] > 0) {
                            int val = max(dp(nxt, j, 0), dp(i, nxt, 1)) + pathRev[i][nxt] - 1;
                            //cout << j << "-->" << i << "--> ... -->" << nxt << ": " << val << endl;
                            if (best < val) {
                                best = val;
                                bestIdx = j;
                            }
                        }
                    }
                }

                //cout << "pathRev[" << i << "][" << j << "]: " << pathRev[i][j] << endl;
                if (pathRev[i][j] > 0) {
                    for (int k : adj[j]) {
                        if (j == i || ccw(i, k, j)) pathRev[i][k] = max(pathRev[i][k], pathRev[i][j] + 1);
                    }
                }
            }
        }
    }

    cout << best << endl;
    cout << bestIdx+1 << endl;

    return 0;
}
