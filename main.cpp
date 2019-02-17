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

template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;

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

set<int> children[100100];
int nodes = 0;
int parent[100100];
int size[100100];
map<int, int> dist[100100];
pair<ii, ii> best[100100];

int dfsSize(int node, int parent) {
    size[node] = 1;
    for (int child : children[node]) {
        if (child == parent) continue;
        size[node] += dfsSize(child, node);
    }
    return size[node];
}

int dfsCentroid(int node, int parent, int totSz) {
    for (int child : children[node]) {
        if (child == parent) continue;
        if (size[child] > totSz / 2) return dfsCentroid(child, node, totSz);
    }
    return node;
}

void dfsDist(int node, int depth, int parent, int centroid) {
    dist[centroid][node] = depth;
    for (int child : children[node]) {
        if (child == parent) continue;
        dfsDist(child, depth + 1, node, centroid);
    }
}

int build(int node) {
    dfsSize(node, node);

    int centroid = dfsCentroid(node, node, size[node]);
    for (int child : children[centroid]) {
        children[child].erase(centroid);
    }

    for (int child : children[centroid]) {
        dfsDist(child, 1, child, centroid);
    }

    for (int child : children[centroid]) {
        parent[build(child)] = centroid;
    }

    best[centroid] = { {0, -1}, {0, -1} };
    return centroid;
}

int main() {
    setupIO("newbarn");

    int q; cin >> q;
    vii queries;
    F0R(i, q) {
        char c; int x; cin >> c >> x;
        --x;
        if (c == 'B') {
            if (nodes != 0) {
                children[x].insert(nodes);
                children[nodes].insert(x);
            }
            queries.pb(mp(c, nodes));
            nodes++;
        } else {
            queries.pb(mp(c, x));
        }
    }

    parent[build(0)] = -1;

    int ctr = 0;
    for (ii query : queries) {
        if (query.pA == 'B') {
            ctr++;
            int node = query.pB;
            int target = parent[node];
            int prevTarget = node;
            while (target != -1) {
                int distToTarget = dist[target][node];
                ii a = best[target].pA, b = best[target].pB;
                if (a.pB == -1) {
                    best[target].pA = { distToTarget, prevTarget };
                } else if (b.pB == -1) {
                    best[target].pB = { distToTarget, prevTarget };
                } else if (a.pA < distToTarget) {
                    if (a.pB != prevTarget) best[target] = { { distToTarget, prevTarget }, a };
                    else best[target] = { { distToTarget, prevTarget }, b };
                } else if (b.pA < distToTarget) {
                    if (a.pB != prevTarget) best[target] = { a, { distToTarget, prevTarget } };
                }
                target = parent[target];
            }
        } else {
            int node = query.pB;
            int ans = best[node].pA.pA;
            int target = parent[node];
            int prevTarget = node;
            while (target != -1) {
                int distToTarget = dist[target][node];
                if (ctr > target) {
                    ans = max(ans, distToTarget);
                    if (best[target].pA.pB != prevTarget) ans = max(ans, distToTarget + best[target].pA.pA);
                    else ans = max(ans, distToTarget + best[target].pB.pA)
                    if (best[target].pA != -1 && paths[target][best[target].pA].count(prevTarget) == 0) {
                        ans = max(ans, distToTarget + pathScore[target][best[target].pA]);
                    } else if (best[target].pB != -1 && paths[target][best[target].pB].count(prevTarget) == 0) {
                        ans = max(ans, distToTarget + pathScore[target][best[target].pB]);
                    }
                }
                prevTarget = target;
                target = parent[target];
            }
            cout << ans << endl;
        }
    }

    return 0;
}
