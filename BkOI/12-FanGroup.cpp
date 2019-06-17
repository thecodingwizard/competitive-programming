/*
 * Idea taken from https://github.com/nikolapesic2802/Programming-Practice/blob/master/Fan%20Groups/main.cpp
 *
 * SCC compression, Topo Sort
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

void bad() {
    cout << "-1" << endl;
    exit(0);
}

int n, m;
set<int> children[20000];
set<ii> fightEdges;
int dfsNum[20000], dfsLow[20000], nodeCtr = 0;
bool inStack[20000];
int sccNum[20000]; int sccCtr = 0;
vi sccNodes[20000];
vi S;

void tarjanSCC(int u) {
    dfsNum[u] = dfsLow[u] = nodeCtr++;
    inStack[u] = true;
    S.pb(u);
    for (int v : children[u]) {
        if (dfsNum[v] == -1) {
            tarjanSCC(v);
            dfsLow[u] = min(dfsLow[u], dfsLow[v]);
        } else if (inStack[v]) {
            dfsLow[u] = min(dfsLow[u], dfsNum[v]);
        }
    }
    if (dfsNum[u] == dfsLow[u]) {
        // Start of SCC
        while (S.back() != u) {
            int v = S.back(); S.pop_back(); inStack[v] = false;
            sccNum[v] = sccCtr;
            sccNodes[sccCtr].pb(v);
        }
        S.pop_back(); inStack[u] = false;
        sccNodes[sccCtr].pb(u);
        sccNum[u] = sccCtr++;
    }
}

set<int> sccChildren[20000];
int inDegree[20000];

int control[20000];
vi controlNodes[20000];
int groupCtr = 0;
void dfsControl(int u) {
    control[u] = groupCtr;
    controlNodes[groupCtr].pb(u);
    for (int v : sccChildren[u]) {
        if (control[v] == -1) dfsControl(v);
        else {
            if (control[v] != groupCtr) {
                // oops, this node is already under control. A fight must have broken out!
                bad();
            }
        }
    }
}

bool visited[20000];
set<int> finalChildren[20000];

vi toposorted;
void topoSort(int u) {
    visited[u] = true;
    for (int v : finalChildren[u]) {
        if (!visited[v]) topoSort(v);
    }
    toposorted.pb(u);
}

int main() {
    setupIO();

    cin >> n >> m;
    // First, we only consider edges with weight zero
    F0R(i, m) {
        int a, b, c; cin >> a >> b >> c;
        --a; --b;
        if (c) {
            fightEdges.insert(mp(a, b));
        } else {
            children[a].insert(b);
        }
    }

    // Step 1: Merge SCC's
    SET(dfsNum, -1, n);
    SET(dfsLow, -1, n);
    SET(inStack, false, n);
    F0R(i, n) {
        if (dfsNum[i] == -1) tarjanSCC(i);
    }
    SET(inDegree, 0, n);
    F0R(i, n) {
        for (int v : children[i]) {
            if (sccNum[i] != sccNum[v]) {
                sccChildren[sccNum[i]].insert(sccNum[v]);
                inDegree[sccNum[v]]++;
            }
        }
    }

    // Step 2: Check if graph is valid.
    // From every node with indegree zero, assume a group takes control of it and run a dfs.
    // Make sure that each node is only visited once, otherwise a fight must have broken out
    // and we output -1.
    SET(control, -1, n);
    F0R(i, sccCtr) {
        if (inDegree[i] == 0) {
            dfsControl(i);
            groupCtr++;
        }
    }

    // Step 3: Add back fight edges. (Reversed, topo sort)
    // Within each "group" from the DFS above, there can be no fight edges within it.
    for (ii edge : fightEdges) {
        int a = sccNum[edge.pA], b = sccNum[edge.pB];
        if (control[a] == control[b]) {
            bad();
        }
        finalChildren[control[b]].insert(control[a]);
    }

    // Step 4: Topo Sort
    SET(visited, false, groupCtr);
    F0R(i, groupCtr) {
        if (!visited[i]) topoSort(i);
    }
    reverse(all(toposorted));

    vi ans;
    for (int i : toposorted) {
        for (int x : controlNodes[i]) {
            for (int y : sccNodes[x]) ans.pb(y);
        }
    }

    cout << ans[0]+1;
    FOR(i, 1, ans.size()) cout << " " << ans[i]+1;
    cout << endl;

    return 0;
}