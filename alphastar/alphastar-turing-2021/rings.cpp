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

vector<int> adj[5000];
int n, l; 

bool vis[5000];
bool verify(int u, int p, int b) {
    if (vis[u]) return false;
    vis[u] = true;
    int ct = 0;
    for (int v : adj[u]) {
        if (v == p || v == b) continue;
        if (!verify(v, u, b)) return false;
        ct++;
    }
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> l;

    for (int i = 0; i < l; i++) {
        int x; cin >> x;
        if (x == -1) {
            int ans = 0;
            for (int j = 0; j < n; j++) {
                F0R(k, n) vis[k] = 0;
                bool g = true;
                for (int k = 0; k < n; k++) {
                    if (k == j) continue;
                    if (!vis[k]) {
                        if (!verify(k, k, j)) g = false;
                    }
                }
                if (g) ans++;
            }
            cout << ans << endl;
        } else {
            int y; cin >> y; --x; --y;
            adj[x].pb(y); adj[y].pb(x);
        }
    }

    return 0;
}
