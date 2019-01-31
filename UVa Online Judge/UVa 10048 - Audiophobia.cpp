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

using namespace std;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define F0R1(i, a) for (int i=1; i<=(a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
#define F0Rd1(i, a) for (int i=a; i>0; i--)
#define SORT(vec) sort(vec.begin(), vec.end())

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
#define MOD2 1000000007
#define SET(vec, val, size) for (int i = 0; i < size; i++) vec[i] = val;
#define SET2D(arr, val, dim1, dim2) F0R(i, dim1) F0R(j, dim2) arr[i][j] = val;
#define SET3D(arr, val, dim1, dim2, dim3) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) arr[i][j][k] = val;
#define SET4D(arr, val, dim1, dim2, dim3, dim4) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) F0R(l, dim4) arr[i][j][k][l] = val;
#define READGRID(arr, dim) F0R(i, dim) F0R(j, dim) cin >> arr[i][j];
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

vii children[100];

bool visited[100];
int dfs(int a, int b) {
    if (a == b) return 0;
    visited[a] = true;
    int best = INF;
    for (ii child : children[a]) {
        if (visited[child.pA]) continue;
        best = min(best, max(child.pB, dfs(child.pA, b)));
    }
    return best;
}

int main() {
    int c, s, q, caseNum = 1;
    while (cin >> c >> s >> q && (c || s || q)) {
        viii edges;
        F0R(i, c) children[i].clear();
        F0R(i, s) {
            int a, b, w; cin >> a >> b >> w;
            --a; --b;
            edges.pb(mp(w, mp(a, b)));
        }
        UnionFind UF(c);
        SORT(edges);
        for (iii edge : edges) {
            if (UF.isSameSet(edge.pB.pA, edge.pB.pB)) continue;
            UF.unionSet(edge.pB.pA, edge.pB.pB);
            children[edge.pB.pA].pb(mp(edge.pB.pB, edge.pA));
            children[edge.pB.pB].pb(mp(edge.pB.pA, edge.pA));
        }

        if (caseNum != 1) cout << endl;
        cout << "Case #" << caseNum++ << endl;
        F0R(i, q) {
            int a, b; cin >> a >> b;
            --a; --b;
            SET(visited, false, 100);
            int ans = dfs(a, b);
            if (ans == INF) cout << "no path" << endl;
            else cout << ans << endl;
        }
    }

    return 0;
}
