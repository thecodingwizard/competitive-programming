/*
 * Loop through all the characters; we'll find the number of submatrices that has
 * one of the corners as the current character c.
 *
 * For a given character c, define above[i][j] = the first row r above row i such that
 * A[r][j] >= c.
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

int main() {
    cin.tie(0)->sync_with_stdio(0);
    freopen("ssdj.in", "r", stdin);
    freopen("ssdj.out", "w", stdout);

    int n; cin >> n;
    char A[n][n];
    F0R(i, n) F0R(j, n) cin >> A[i][j];

    int above[n][n]; // index of row above (i, j) that's >= c
    int ans = 0;
    for (char c = 'z'; c >= 'a'; c--) {
        F0R(col, n) {
            int prev = -1;
            F0R(row, n) {
                above[row][col] = prev;
                if (A[row][col] >= c) {
                    prev = row;
                }
            }
        }
        F0R(row, n) {
            int rightCol = -1;
            int upperBound = -2;
            for (int col = n-1; ~col; col--) {
                if (A[row][col] >= c) {
                    rightCol = col;
                    upperBound = above[row][col]+1;
                } else {
                    if (rightCol == -1) continue;
                    if (upperBound <= above[row][col]) {
                        if (A[row][rightCol] == c || A[above[row][col]][col] == c) {
                            ans++;
                        }
                        upperBound = above[row][col]+1;
                    }
                }
            }
        }
    }
    cout << ans << endl;

    return 0;
}
