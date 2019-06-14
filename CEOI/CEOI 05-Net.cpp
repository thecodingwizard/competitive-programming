// Step 1: Find all 2-edge connected components and compress them
// Resulting graph is a tree
// For each node of the leaf, determine whether it has A, B, AB, or none

// Step 2: Now check bridges that lack A. To do this, for every leaf node, mark the edge
// to its parent as critical. Then remove the edge. If the parent node is now a leaf node
// and the parent node doesn't have A, then repeat the process.
// Do this process again for B.

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

int n, m, k, l;
vi children[100000];
bool A[100000], B[100000];

int dfsLow[100000], dfsNum[100000], dfsCtr = 0;
set<ii> bridges;
void findBridges(int u, int p) {
    dfsLow[u] = dfsNum[u] = dfsCtr++;
    for (int v : children[u]) {
        if (dfsLow[v] == INF) {
            findBridges(v, u);
            MIN(dfsLow[u], dfsLow[v]);
        } else if (v != p) {
            MIN(dfsLow[u], dfsNum[v]);
        }
        if (dfsLow[v] > dfsNum[u]) {
            bridges.insert(mp(u, v));
            bridges.insert(mp(v, u));
        }
    }
}

bool visited[100000];
// Compressed nodes info
set<int> nodeChildren[100000];
int inDegree[100000];
int nodeId[100000];
int services[100000]; // 0 = none, 1 = A, 10 = B, 11 = AB
int nodeCtr = 0;

void dfsNode(int u, int id) {
    nodeId[u] = id;
    visited[u] = true;
    if (A[u]) services[id] |= 1;
    if (B[u]) services[id] |= 2;
    for (int v : children[u]) {
        if (!visited[v] && bridges.count(mp(u, v)) == 0) {
            dfsNode(v, id);
        }
    }
}

vii ans;
void dfsAns(int u, int tgtService) {
    visited[u] = true;
    for (int v : nodeChildren[u]) {
        inDegree[v]--;
        if (!visited[v]) {
            ans.pb(mp(u, v));
            if (inDegree[v] < 2 && (services[v] & tgtService) == 0) dfsAns(v, tgtService);
        }
    }
}

int main() {
    setupIO();
    cin >> n >> m >> k >> l;
    SET(A, false, n); SET(B, false, n);
    F0R(i, k) {
        int x; cin >> x;
        A[--x] = true;
    }
    F0R(i, l) {
        int x; cin >> x;
        B[--x] = true;
    }
    F0R(i, m) {
        int a, b; cin >> a >> b;
        children[--a].pb(--b);
        children[b].pb(a);
    }

    // Step 1
    SET(dfsLow, INF, n);
    findBridges(0, 0);
    SET(visited, false, n);
    SET(services, 0, n);
    F0R(i, n) {
        if (!visited[i]) dfsNode(i, nodeCtr++);
    }

    map<ii, ii> realBridges;
    for (ii bridge : bridges) {
        nodeChildren[nodeId[bridge.pA]].insert(nodeId[bridge.pB]);
        realBridges[mp(nodeId[bridge.pA], nodeId[bridge.pB])] = mp(max(bridge.pA, bridge.pB), min(bridge.pA, bridge.pB));
    }

    // Step 2
    F0R(i, nodeCtr) inDegree[i] = nodeChildren[i].size();
    SET(visited, false, n);
    F0R(i, nodeCtr) {
        if (inDegree[i] < 2 && (services[i] & 1) == 0) {
            dfsAns(i, 1);
        }
    }
    F0R(i, nodeCtr) inDegree[i] = nodeChildren[i].size();
    SET(visited, false, n);
    F0R(i, nodeCtr) {
        if (inDegree[i] < 2 && (services[i] & 2) == 0) {
            dfsAns(i, 2);
        }
    }

    set<ii> realAns;
    for (ii x : ans) {
        realAns.insert(realBridges[x]);
    }
    cout << realAns.size() << endl;
    for (ii x : realAns) {
        cout << x.pA + 1 << " " << x.pB + 1 << endl;
    }

    return 0;
}