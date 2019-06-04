#include <iostream>
#include <string>
#include <utility>
#include <sstream>
#include <algorithm>
#include <stack>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <bitset>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <unordered_set>
#include <ctime>

using namespace std;

template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define F0R1(i, a) for (int i=1; i<=(a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
#define F0Rd1(i, a) for (int i=a; i>0; i--)
#define SORT(vec) sort(vec.begin(), vec.end())
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

class FenwickTree {
private:
    vi ft;

public:
    FenwickTree() {}
    FenwickTree(int n) { ft.assign(n + 1, 0); }

    int rsq(int b) {
        int sum = 0; for (; b; b -= LSOne(b)) sum ^= ft[b];
        return sum; }

    int rsq(int a, int b) {
        return rsq(b) ^ (a == 1 ? 0 : rsq(a - 1)); }

    void adjust(int k, int v) {
        for (; k < (int)ft.size(); k += LSOne(k)) ft[k] ^= v; }
};

int n, q;
int A[100000];
vi children[100000];
int sz[101000], ctr = 1;
map<int, int> idx;
FenwickTree FT(101000);
int depth[101000], p[18][101000];

void build(int x, int pa, int d) {
    depth[x] = d;
    p[0][x] = pa;
    FOR(i, 1, 18) {
        p[i][x] = p[i-1][p[i-1][x]];
    }
    for (int child : children[x]) {
        if (child != pa) build(child, x, d+1);
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    int c = depth[a] - depth[b];
    F0R(i, 18) {
        if ((c >> i) & 1) a = p[i][a];
    }
    if (a == b) return a;

    F0Rd(i, 18) {
        if (p[i][a] != p[i][b]) {
            a = p[i][a];
            b = p[i][b];
        }
    }
    return p[0][a];
}

int dfs(int node, int p) {
    int nodeCtr = ctr++;
    idx[node] = nodeCtr;
    int size = 1;
    for (int child : children[node]) {
        if (child == p) continue;
        size += dfs(child, node);
    }
    sz[nodeCtr] = size;
    FT.adjust(nodeCtr, A[node]);
    FT.adjust(nodeCtr + sz[nodeCtr], A[node]);
    return sz[nodeCtr];
}

int main() {
    setupIO("cowland");
    cin >> n >> q;
    F0R(i, n) cin >> A[i];
    F0R(i, n-1) {
        int a, b; cin >> a >> b;
        --a; --b;
        children[a].pb(b);
        children[b].pb(a);
    }
    dfs(0, -1);
    build(0, 0, 0);

    F0R(i, q) {
        int x; cin >> x;
        if (x == 1) {
            int y, v; cin >> y >> v;
            --y;
            int id = idx[y];
            FT.adjust(id, A[y] ^ v);
            FT.adjust(id + sz[id], A[y] ^ v);
            A[y] = v;
        } else {
            int a, b; cin >> a >> b;
            int ans = FT.rsq(idx[a-1]) ^ FT.rsq(idx[b-1]) ^ A[lca(a-1, b-1)];
            cout << ans << endl;
        }
    }

    return 0;
}
