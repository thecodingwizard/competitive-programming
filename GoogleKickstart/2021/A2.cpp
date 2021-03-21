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

int r, c;
bool A[1000][1000];
int maxLen[1000][1000][4];

int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, -1, 0, 1 };
int getLen(int i, int j, int dir) {
    if (i < 0 || i >= r || j < 0 || j >= c) return 0;
    if (maxLen[i][j][dir] != -1) return maxLen[i][j][dir];
    if (A[i][j] == 0) {
        return maxLen[i][j][dir] = 0;
    }
    return maxLen[i][j][dir] = 1 + getLen(i+dx[dir], j + dy[dir], dir);
}

ll ans = 0;

void add(int a, int b) {
    ans += max(min(a, b/2)-1, 0);
    ans += max(min(b, a/2)-1, 0);
}

void solve() {
    ans = 0;
    cin >> r >> c;
    F0R(i, r) F0R(j, c) cin >> A[i][j];

    F0R(i, r) {
        F0R(j, c) {
            F0R(k, 4) {
                maxLen[i][j][k] = -1;
            }
        }
    }

    F0R(i, r) {
        F0R(j, c) {
            F0R(k, 4) {
                maxLen[i][j][k] = getLen(i, j, k);
            }
        }
    }

    F0R(i, r) {
        F0R(j, c) {
            int lenLeft = maxLen[i][j][1];
            int lenUp = maxLen[i][j][0];
            int lenRight = maxLen[i][j][3];
            int lenDown = maxLen[i][j][2];

            add(lenLeft, lenUp);
            add(lenLeft, lenDown);
            add(lenRight, lenUp);
            add(lenRight, lenDown);
        }
    }
    cout << ans << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        cout << "Case #" << tc << ": ";
        solve();
    }

    return 0;
}
