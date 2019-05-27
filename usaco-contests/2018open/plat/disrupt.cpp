#include <bits/stdc++.h>

using namespace std;

template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define F0R1(i, a) for (int i=1; i<=(a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
#define F0Rd1(i, a) for (int i=a; i>0; i--)
#define SORT(vec) sort(vec.begin(), vec.end())
#define RSORT(vec) sort(vec.rbegin(), vec.rend())
#define MIN(a, b) a = min(a, b)
#define MAX(a, b) a = max(a, b)

#define INF 1000000010
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define pA first
#define pB second
#define mp make_pair
#define pb push_back
#define PI acos(-1.0)
#define ll long long
#define MOD (int)(2e+9+11)
#define SET(vec, val, size) for (int i = 0; i < size; i++) vec[i] = val;
#define SET2D(arr, val, dim1, dim2) F0R(i, dim1) F0R(j, dim2) arr[i][j] = val;
#define SET3D(arr, val, dim1, dim2, dim3) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) arr[i][j][k] = val;
#define SET4D(arr, val, dim1, dim2, dim3, dim4) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) F0R(l, dim4) arr[i][j][k][l] = val;
#define READGRID(arr, dim) F0R(i, dim) F0R(j, dim) cin >> arr[i][j];
#define all(x) (x).begin(), (x).end()

typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<ll> vl;

void setupIO(const string &PROB) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream infile(PROB + ".in");
    if (infile.good()) {
        freopen((PROB + ".in").c_str(), "r", stdin);
        freopen((PROB + ".out").c_str(), "w", stdout);
    }
}

/* ============================ */

vi children[50000];
vii extra[50000];
bool visited[50000];
int ans[50000];
int depth[50000];
set<ii> pool[70000];
int poolCtr = 0;

int dfs(int u, int d, int idx) {
    depth[u] = d;
    visited[u] = true;
    for (int v : children[u]) {
        if (!visited[v]) {
            int nxtIdx = dfs(v, d + 1, poolCtr++);
            if (pool[idx].empty()) idx = nxtIdx;
            else {
                int curSz = pool[idx].size();
                int nxtSz = pool[nxtIdx].size();
                if (curSz < nxtSz) {
                    for (ii x : pool[idx]) {
                        if (pool[nxtIdx].count(x)) {
                            pool[nxtIdx].erase(x);
                        } else {
                            pool[nxtIdx].insert(x);
                        }
                    }
                    idx = nxtIdx;
                } else {
                    for (ii x : pool[nxtIdx]) {
                        if (pool[idx].count(x)) {
                            pool[idx].erase(x);
                        } else {
                            pool[idx].insert(x);
                        }
                    }
                }
            }
        }
    }
    for (ii x : extra[u]) {
        if (pool[idx].count(x)) {
            pool[idx].erase(x);
        } else {
            pool[idx].insert(x);
        }
    }
    if (pool[idx].empty()) ans[u] = -1;
    else ans[u] = pool[idx].begin()->pA;
    return idx;
}

int main() {
    setupIO("disrupt");
    SET(visited, false, 50000);

    int n, m; cin >> n >> m;
    vii edges;
    F0R(i, n - 1) {
        int p, q; cin >> p >> q;
        --p; --q;
        edges.pb(mp(p, q));
        children[p].pb(q);
        children[q].pb(p);
    }
    F0R(i, m) {
        int p, q, r; cin >> p >> q >> r;
        --p; --q;
        extra[p].pb(mp(r, i));
        extra[q].pb(mp(r, i));
    }
    dfs(0, 1, poolCtr++);
    for (ii edge : edges) {
        int d1 = depth[edge.pA], d2 = depth[edge.pB];
        if (d1 < d2) {
            cout << ans[edge.pB] << endl;
        } else {
            cout << ans[edge.pA] << endl;
        }
    }

    return 0;
}