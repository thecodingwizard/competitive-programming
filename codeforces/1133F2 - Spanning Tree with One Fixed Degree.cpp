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
#include <list>

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

class UnionFind {
private:
  vi p, rank, setSize;
  int numSets;
public:
  UnionFind(int N) {
    setSize.assign(N, 1); numSets = N; rank.assign(N, 0);
    p.assign(N, 0); for (int i = 0; i < N; i++) p[i] = i; }
  int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
  bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
  void unionSet(int i, int j) { 
    if (!isSameSet(i, j)) { numSets--; 
    int x = findSet(i), y = findSet(j);
    if (rank[x] > rank[y]) { p[y] = x; setSize[x] += setSize[y]; }
    else                   { p[x] = y; setSize[y] += setSize[x];
                             if (rank[x] == rank[y]) rank[y]++; } } }
  int numDisjointSets() { return numSets; }
  int sizeOfSet(int i) { return setSize[findSet(i)]; }
};

vi children[200005];
UnionFind UF(200005);
bool visited[200005];
bool canReach[200005];
vii ans;

void dfs(int u) {
    visited[u] = true;
    for (int v : children[u]) {
        if (v == 1) continue;
        if (!visited[v]) {
            dfs(v);
        }
    }
}

void dfs2(int u) {
    canReach[u] = true;
    for (int v : children[u]) {
        if (v == 1) continue;
        if (!canReach[v]) dfs2(v);
    }
}

int main() {
    int n, m, d; cin >> n >> m >> d;
    int oneDegree = 0;
    vii edges;
    F0R(i, m) {
        int a, b; cin >> a >> b;
        children[a].pb(b);
        children[b].pb(a);
        if (a == 1 || b == 1) oneDegree++;
        edges.pb(mp(a, b));
    }

    SET(visited, false, n+1);
    int numDisjoint = 0;
    F0R1(i, n) {
        if (i == 1) continue;
        if (!visited[i]) {
            numDisjoint++;
            dfs(i);
        }
    }

    if (numDisjoint > d || oneDegree < d) {
        cout << "NO" << endl;
        return 0;
    }

    cout << "YES" << endl;

    SET(canReach, false, n+1);
    for (int u : children[1]) {
        if (!canReach[u]) {
            dfs2(u);
            ans.pb(mp(1, u));
            UF.unionSet(1, u);
            d--;
        }
    }

    for (int u : children[1]) {
        if (d == 0) break;
        if (!UF.isSameSet(1, u)) {
            d--;
            UF.unionSet(1, u);
            ans.pb(mp(1, u));
        }
    }

    for (ii edge : edges) {
        if (edge.pA == 1 || edge.pB == 1) continue;
        if (!UF.isSameSet(edge.pA, edge.pB)) {
            ans.pb(edge);
            UF.unionSet(edge.pA, edge.pB);
        }
    }

    for (ii x : ans) {
        cout << x.pA << " " << x.pB << endl;
    }

    return 0;
}
