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
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
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

void fastscan(int&n) {bool negative=false;register int c;n=0;c=getchar();if(c=='-') {negative=true;c=getchar();}
    for(;(c>47&&c<58);c=getchar()){n=n*10+c-48;}
    if(negative){n*=-1;}}

void setupIO(string PROB) {
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

int n, m, k, q;
map<int, set<ii>> A[200100];
set<ii> B;
set<ii> C[200100];
iii edges[200100];
vii children[200100];
ii parent[200100];
int color[200100];

void dfs(int x) {
    for (ii child : children[x]) {
        if (parent[child.pA].pB == -INF) {
            parent[child.pA].pA = x;
            parent[child.pA].pB = child.pB;
            dfs(child.pA);
        }
    }
}

void generateMST() {
    UnionFind UF(n);
    F0R(i, m) {
        int a = edges[i].pB.pA, b = edges[i].pB.pB, l = edges[i].pA;
        if (UF.isSameSet(a, b)) continue;
        UF.unionSet(a, b);
        children[a].pb(mp(b, l));
        children[b].pb(mp(a, l));
    }
    parent[0].pA = -1;
    dfs(0);
}

ii getBest(int node, int color) {
    auto it = C[node].begin();
    if (it == C[node].end()) return mp(INF, node);
    if (it->pB == color) it++;
    if (it == C[node].end()) return mp(INF, node);
    return mp(it->pA, node);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    setupIO("grass");

    fastscan(n); fastscan(m); fastscan(k); fastscan(q);
    int a, b, x = 0;
    F0R(i, m) {
        fastscan(edges[x].pB.pA); fastscan(edges[x].pB.pB); fastscan(edges[x].pA);
        --edges[x].pB.pA; --edges[x].pB.pB;
        x++;
    }
    sort(edges, edges+m);
    F0R(i, n) {
        fastscan(color[i]);
        parent[i].pB = -INF;
    }

    generateMST();

    F0R(i, n) {
        if (parent[i].pA == -1) continue;
        A[parent[i].pA][color[i]].insert(mp(parent[i].pB, i));
    }
    F0R(i, n) {
        for (auto const& x : A[i]) {
            set<ii> color = x.pB;
            C[i].insert(mp(color.begin()->pA, x.pA));
        }
        B.insert(getBest(i, color[i]));
    }

    int prevColor, p;
    bool flag;
    F0R(i, q) {
        fastscan(a);
        fastscan(b);
        --a;
        prevColor = color[a];
        color[a] = b;

        B.erase(getBest(a, prevColor));

        p = parent[a].pA;

        if (p != -1) {
            B.erase(getBest(p, color[p]));

            flag = A[p][prevColor].size() > 0 && A[p][prevColor].begin()->pA == parent[a].pB;
            if (flag) C[p].erase(mp(A[p][prevColor].begin()->pA, prevColor));
            A[p][prevColor].erase(mp(parent[a].pB, a));
            if (flag && A[p][prevColor].size() > 0) C[p].insert(mp(A[p][prevColor].begin()->pA, prevColor));

            flag = A[p][b].size() > 0 && A[p][b].begin()->pA >= parent[a].pB;
            if (flag) C[p].erase(mp(A[p][b].begin()->pA, b));
            A[p][b].insert(mp(parent[a].pB, a));
            if (flag || A[p][b].size() == 1) C[p].insert(mp(A[p][b].begin()->pA, b));

            B.insert(getBest(p, color[p]));
        }

        B.insert(getBest(a, b));

        ii best = *B.begin();
        cout << best.pA << "\n";
    }

    return 0;
}