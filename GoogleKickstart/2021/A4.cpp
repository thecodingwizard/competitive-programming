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

int pa[1000];
int sz[1000];
int find(int x) { return pa[x] == x ? x : pa[x] = find(pa[x]); }
void unite(int a, int b) {
    a = find(a), b = find(b);
    if (sz[a] < sz[b]) swap(a, b);
    pa[b] = a;
    sz[a] += sz[b];
}

void solve() {
    int n; cin >> n;
    F0R(i, 2*n) {
        pa[i] = i;
        sz[i] = 1;
    }
    int A[n][n];
    F0R(i, n) F0R(j, n) cin >> A[i][j];
    int B[n][n];
    F0R(i, n) F0R(j, n) cin >> B[i][j];
    int R[n], C[n]; F0R(i, n) cin >> R[i]; F0R(i, n) cin >> C[i];

    ll tot = 0;
    vector<pair<int, ii>> edges;
    F0R(i, n) {
        F0R(j, n) {
            if (A[i][j] == -1) {
                tot += B[i][j];
                edges.pb(mp(B[i][j], mp(i, n+j)));
            }
        }
    }
    sort(all(edges));
    reverse(all(edges));
    for (auto e : edges) {
        if (find(e.s.f) != find(e.s.s)) {
            unite(e.s.f, e.s.s);
            tot -= e.f;
        }
    }
    cout << tot << endl;
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
