/*
 * The key observation is that since the roads don't intersect at their endpoints, each left
 * endpoint will be able to reach a contiguous range of right endpoints.
 *
 * In O(n) time, it's possible to remove all left nodes that aren't connected to right nodes,
 * and all right nodes that aren't connected to left nodes.
 *
 * Let's define the following:
 * - highest[i] = what is the highest right node that can be reached from left node i? (highest = maximum y-coordinate)
 * - lowest[i] = what is the lowest right node that can be reached from left node i? (lowest = minimum y-coordinate)
 *
 * If we can figure out highest[i] and lowest[i] for each left node, then the answer for the left
 * node i is just highest[i] - lowest[i] + 1, since each left node can reach all right nodes in a contiguous range.
 * There is an exception to this rule if the left node can't reach *any* right nodes, but this can be handled separately.
 *
 * How do we figure out highest[i] and lowest[i] in O(n) time?
 *
 * Notice that if node A's y-coordinate is higher than node B's y-coordinate, then the following holds
 * (assuming both node A and node B are connected to at least one right node):
 *
 * highest[A] >= highest[B]
 * lowest[A] <= lowest[B]
 *
 * Hence, we can determine highest and lowest by processing the left nodes from increasing/decreasing y coordinate values.
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

int n, m, cols, rows;
ii A[300000];
int status[300000]; // 0 = left, 1 = right, 2 = neither
vi children[300000], reverseChildren[300000];
int num[300000]; // If it's a *reachable* right endpoint, numbered from 1 ... n from bottom to top.
int highest[300000], lowest[300000];

bool reachable[300000];
void dfsReachable(int u) {
    if (reachable[u]) return;
    reachable[u] = true;
    for (int v : children[u]) {
        dfsReachable(v);
    }
}

bool reverseReachable[300000];
void dfsReverseReachable(int u) {
    if (reverseReachable[u]) return;
    reverseReachable[u] = true;
    for (int v : reverseChildren[u]) {
        dfsReverseReachable(v);
    }
}

bool visited[300000];
int maxHeight = 0;
void dfsHighest(int u) {
    if (status[u] == 1) MAX(maxHeight, num[u]);
    if (visited[u]) return;
    visited[u] = true;
    for (int v : children[u]) {
        dfsHighest(v);
    }
}

int minHeight = INF;
void dfsLowest(int u) {
    if (status[u] == 1) MIN(minHeight, num[u]);
    if (visited[u]) return;
    visited[u] = true;
    for (int v : children[u]) dfsLowest(v);
}

int main() {
    setupIO();

    cin >> n >> m >> cols >> rows;

    vii leftEndpoints;
    F0R(i, n) {
        cin >> A[i].pA >> A[i].pB;
        if (A[i].pA == 0) {
            status[i] = 0;
            leftEndpoints.pb(mp(A[i].pB, i));
        } else if (A[i].pA == cols) status[i] = 1;
        else status[i] = 2;
    }

    F0R(i, m) {
        int c, d, k; cin >> c >> d >> k;
        --c; --d;
        children[c].pb(d);
        reverseChildren[d].pb(c);
        if (k == 2) {
            children[d].pb(c);
            reverseChildren[c].pb(d);
        }
    }

    // Step 1: Number *reachable* endpoints from 1...n
    // and remove unreachable endpoint nodes
    SET(reachable, false, 300000);
    SET(reverseReachable, false, 300000);
    F0R(i, n) {
        if (status[i] == 0) {
            dfsReachable(i);
        }
        if (status[i] == 1) {
            dfsReverseReachable(i);
        }
    }
    vii reachableEndpoints;
    F0R(i, n) {
        if (status[i] == 1 && reachable[i]) reachableEndpoints.pb(mp(A[i].pB, i));
    }
    SORT(reachableEndpoints);
    F0R(i, reachableEndpoints.size()) num[reachableEndpoints[i].pB] = i;

    // Step 2: From bottom to top, find the max place you can reach.
    // Note that it's always increasing
    SORT(leftEndpoints);
    SET(visited, false, 300000);
    for (ii x : leftEndpoints) {
        dfsHighest(x.pB);
        highest[x.pB] = maxHeight;
    }

    // Step 3: From top to bottom, find the lowest place that you can reach.
    // Note that it's always decreasing.
    reverse(all(leftEndpoints));
    SET(visited, false, 300000);
    for (ii x : leftEndpoints) {
        dfsLowest(x.pB);
        lowest[x.pB] = minHeight;
    }

    // Step 4: The answer for each endpoint is highest - lowest + 1
    // Edge case: If I'm not connected to any right endpoint
    for (ii x : leftEndpoints) {
        if (!reverseReachable[x.pB]) cout << 0 << endl;
        else cout << highest[x.pB] - lowest[x.pB] + 1 << endl;
    }

    return 0;
}