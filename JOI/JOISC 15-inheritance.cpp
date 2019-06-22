/*
 * Union Find, greedy.
 *
 * Note that the optimal strategy is to sort the edges by decreasing cost, and for every edge, attempt to give it
 * to the first child. If the first child can't receive it, then try the next child, and so on.
 *
 * We can do this using Union Find
 */

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
#define LL_INF 4500000000000000000LL
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

void setupIO(const string &PROB = "") {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if (PROB.length() != 0) {
        ifstream infile(PROB + ".in");
        if (infile.good()) {
            freopen((PROB + ".in").c_str(), "r", stdin);
            freopen((PROB + ".out").c_str(), "w", stdout);
        }
    }
}

/* ============================ */

struct UnionFind {
    int p[1000], rnk[1000];
    UnionFind() {
        F0R(i, 1000) p[i] = i;
        F0R(i, 1000) rnk[i] = 0;
    }
    int find(int u) {
        if (p[u] == u) return u;
        return p[u] = find(p[u]);
    }
    bool isSameSet(int a, int b) {
        return find(a) == find(b);
    }
    void unionSet(int a, int b) {
        int x = find(a), y = find(b);
        if (rnk[x] > rnk[y]) {
            p[y] = x;
        } else {
            p[x] = y;
            if (rnk[x] == rnk[y]) rnk[x]++;
        }
    }
};

struct edge {
    int cost, a, b, id;
};

bool operator<(const edge &lhs, const edge &rhs) {
    return lhs.cost > rhs.cost;
}

int n, m, k;
vector<edge> edges;
UnionFind uf[10000];
int ans[300000];
int nxt[1000][1000];

int main() {
    setupIO();

    cin >> n >> m >> k;
    F0R(i, m) {
        int a, b, c; cin >> a >> b >> c;
        edges.pb(edge{c, a-1, b-1, i});
    }
    sort(all(edges));
    SET2D(nxt, 0, 1000, 1000);

    SET(ans, 0, m);
    for (auto edge : edges) {
        FOR(i, nxt[edge.a][edge.b], k) {
            if (!uf[i].isSameSet(edge.a, edge.b)) {
                uf[i].unionSet(edge.a, edge.b);
                ans[edge.id] = i + 1;
                nxt[edge.a][edge.b] = i + 1;
                break;
            }
        }
    }
    F0R(i, m) {
        cout << ans[i] << "\n";
    }

    return 0;
}