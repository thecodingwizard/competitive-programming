// USACO Guide has a slightly different solution
// Note that the entire grid is dependent on the first row and the first column
// The cell (i, j) is dependent on (1, 1), (1, j), and (i, 1)
// Therefore, make a graph: 0...n-1 represents (i, 1). n...n+m-1 represents(1, j).
// For every cell that's already colored in, draw an edge between the row and the column nodes it's dependent on
// Mark the edge as "these two nodes have the same value" or "these two nodes have different values" depending on the value of the cell
// Set (1, 1) to red and calculate the # of valid assignments
// Set (1, 1) to blue and calculate the # of valid assignments
// To calculate # of valid assignments, we basically DFS from every node (beginning from the nodes whose values we already know).
// Set the values of all connected nodes.
// For nodes whose values we don't know, just arbitrarily assign a value and multiply the # of valid assignments by 2.

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

// [0...n-1] is rows
// [n...n+m-1] is columns
// n+m is 0
// n+m+1 is 1
// second: 1 if not equal, 0 if equal
vector<ii> adj[300000];
int color[300000];
bool vis[300000];
int topLeftC;

ll ans = 1;

void dfs(int u) {
    if (vis[u]) return;
    vis[u] = true;
    if (color[u] == -1) {
        //cerr << u << endl;
        ans = (ans*2)%((int)1e9);
        color[u] = 0;
    }
    for (ii v : adj[u]) {
        int expected = color[u] ^ v.s ^ topLeftC;
        if (color[v.f] == -1) color[v.f] = expected;
        if (color[v.f] != expected) {
            ans = 0;
        }
        dfs(v.f);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, k; cin >> n >> m >> k;
    int topLeft = -1;
    color[n+m] = 0;
    color[n+m+1] = 1;
    for (int i = 0; i < k; i++) {
        int x, y, c; cin >> x >> y >> c;
        if (x == y && x == 1) {
            topLeft = c;
        } else if (x == 1) {
            adj[n+y-1].emplace_back(n+m+c, 0);
            adj[n+m+c].emplace_back(n+y-1, 0);
        } else if (y == 1) {
            adj[x-1].emplace_back(n+m+c, 0);
            adj[n+m+c].emplace_back(x-1, 0);
        } else {
            if (x%2==0 && y%2==0) {
                c ^= 1;
            }
            int r = x-1, col = n+y-1;
            adj[r].pb(mp(col, c));
            adj[col].pb(mp(r, c));
        }
    }

    ll totAns = 0;
    for (topLeftC = 0; topLeftC <= 1; topLeftC++) {
        if (topLeft != -1 && topLeft != topLeftC) continue;
        ans = 1;
        for (int i = 0; i < n+m; i++) {
            color[i] = -1;
        }
        for (int i = 0; i < n+m+10; i++) {
            vis[i] = false;
        }
        dfs(n+m);
        dfs(n+m+1);
        for (int i = 0; i < n+m; i++) {
            if (i == 0 || i == n) continue; // these point to the upper left cell that's a special case
            dfs(i);
        }
        totAns = (totAns + ans) % ((int)1e9);
    }


    cout << totAns << endl;

    return 0;
}
