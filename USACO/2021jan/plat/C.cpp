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

int n, m, q; 
string A[1000];

// oops should really just use prefix sums
struct {
    int ft[1010][1010];
    void upd2(int x, int y, int v) {
        while (y <= 1009) {
            ft[x][y] += v;
            y += y&-y;
        }
    }
    void upd(int x, int y, int v) {
        x++; y++;
        while (x <= 1009) {
            upd2(x, y, v);
            x += x&-x;
        }
    }
    int qry2(int x, int y) {
        int s = 0;
        while (y) {
            s += ft[x][y];
            y -= y&-y;
        }
        return s;
    }
    int qry(int x, int y) {
        x++; y++;
        int s = 0;
        while (x) {
            s += qry2(x, y);
            x -= x&-x;
        }
        return s;
    }
    int qry(int x1, int y1, int x2, int y2) {
        return qry(x2, y2) - qry(x1-1, y2) - qry(x2, y1-1) + qry(x1-1, y1-1);
    }
} horizEdges, vertEdges, special;

int id[1001][1001];
ii specialLoc[1010001];

int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, -1, 0, 1 };

void dfs(int u, int v, int x) {
    if (id[u][v] != 0) return;
    id[u][v] = x;
    // up
    if (u > 0 && (v==0||v==m||A[u-1][v-1] != A[u-1][v])) dfs(u-1, v, x);
    // down
    if (u+1<=n && (v==0||v==m||A[u][v-1]!=A[u][v])) dfs(u+1, v, x);
    // left
    if (v > 0 && (u==0||u==n||A[u][v-1]!=A[u-1][v-1])) dfs(u, v-1, x);
    // right
    if (v+1<=m && (u==0||u==n||A[u][v]!=A[u-1][v])) dfs(u, v+1, x);
}

bool in(ii loc, int a, int b, int x, int y) {
    return a <= loc.f && loc.f <= x && b <= loc.s && loc.s <= y;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m >> q;
    F0R(i, n) cin >> A[i];

    int ctr = 0;
    F0R(i, n) {
        F0R(j, m) {
            if (i+1 < n && A[i][j] != A[i+1][j]) {
                horizEdges.upd(i, j, 1);
            }
            if (j+1 < m && A[i][j] != A[i][j+1]) {
                vertEdges.upd(i, j, 1);
            }
        }
    }
    F0R(i, n+1) {
        F0R(j, m+1) {
            if (id[i][j] == 0) {
                specialLoc[++ctr] = mp(i, j);
                special.upd(i, j, 1);
                dfs(i, j, ctr);
            }
        }
    }

    F0R(i, q) {
        int a, b, x, y; cin >> a >> b >> x >> y; --a; --b; --x; --y;
        int vertices = (x-a+2)*(y-b+2);
        int edges = horizEdges.qry(a, b, x-1, y) + vertEdges.qry(a, b, x, y-1) + 2*(x-a+1+y-b+1);
        int components = 1 + special.qry(a+1, b+1, x, y);

        set<int> bad;
        for (int i = a; i <= x+1; i++) {
            if (in(specialLoc[id[i][b]], a+1, b+1, x, y)) bad.insert(id[i][b]);
            if (in(specialLoc[id[i][y+1]], a+1, b+1, x, y)) bad.insert(id[i][y+1]);
        }
        for (int i = b; i <= y+1; i++) {
            if (in(specialLoc[id[a][i]], a+1, b+1, x, y)) bad.insert(id[a][i]);
            if (in(specialLoc[id[x+1][i]], a+1, b+1, x, y)) bad.insert(id[x+1][i]);
        }

        components -= bad.size();

        cout << edges - vertices + components << endl;
    }

    return 0;
}
