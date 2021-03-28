/*
 * https://github.com/stefdasca/CompetitiveProgramming/blob/master/Infoarena/countfefete.cpp
 *
 * Consider each bit separately. Sort the nodes in decreasing order.
 * Use union-find to merge nodes; in each component, keep track of the number
 * of subsets in that component that xor to a 1 and xor to a 0.
 * When unioning two components, the node we're currently processing is the
 * "smallest" node that will be xor'ed twice.
 *
 * Loop through each bit in the union function to avoid TLE -- make each component
 * store information for every bit rather than rerunning the algorithm 30 times.
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

#define maxn 200000
const int mod = 1e9+7;

int n; 
int A[maxn];
vector<int> adj[maxn];

int sz[maxn];
int pa[maxn];
pair<ll, ll> val[maxn][31];

ll ans = 0;

void add(ll a, ll b, int i) {
    ans = (ans + a*b%mod*(1<<i)%mod)%mod;
}

int get(int x) { return pa[x] == x ? x : pa[x] = get(pa[x]); }
void unite(int x, int b) {
    int a = get(x); b = get(b);

    for (int i = 0; i < 31; i++) {
        bool hasOne = (A[x]&(1<<i)) > 0;

        // first, update answer
        if (hasOne) {
            add(val[a][i].f, val[b][i].f, i);
            add(val[a][i].s, val[b][i].s, i);
        } else {
            add(val[a][i].s, val[b][i].f, i);
            add(val[a][i].f, val[b][i].s, i);
        }
    }

    if (sz[a] > sz[b]) swap(a, b);

    for (int i = 0; i < 31; i++) {
        int old = val[b][i].f;
        val[b][i].f = (val[b][i].f + val[a][i].f + (ll)val[b][i].f*val[a][i].f + (ll)val[b][i].s*val[a][i].s) % mod;
        val[b][i].s = (val[b][i].s + val[a][i].s + (ll)old*val[a][i].s + (ll)val[b][i].s*val[a][i].f) % mod;
    }

    pa[a] = b;
    sz[b] += sz[a];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    freopen("countfefete.in", "r", stdin);
    freopen("countfefete.out", "w", stdout);

    cin >> n;
    vector<ii> nodes;
    F0R(i, n) {
        cin >> A[i];
        nodes.pb(mp(-A[i], i));
    }

    F0R(i, n-1) {
        int a, b; cin >> a >> b; --a; --b;
        adj[a].pb(b); adj[b].pb(a);
    }

    sort(all(nodes));

    F0R(j, n) {
        F0R(i, 31) {
            bool hasOne = (A[j]&(1<<i)) > 0;
            pa[j] = j;
            sz[j] = 1;
            val[j][i] = mp(!hasOne, hasOne);
        }
    }

    for (auto x : nodes) {
        int u = x.s;
        for (int v : adj[u]) {
            if (A[v] < A[u]) continue;
            if (get(u) != get(v)) {
                unite(u, v);
            }
        }
    }

    cout << ans << "\n";

    return 0;
}
