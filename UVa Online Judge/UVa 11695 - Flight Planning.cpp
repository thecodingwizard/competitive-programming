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

int n, dist[2500], dist2[2500]; 
set<int> children[2500];
vii edges;

ii getDiam(int start) {
    queue<int> q;
    SET(dist, INF, 2500);
    q.push(start);
    dist[start] = 0;
    int endNode = start;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : children[u]) {
            if (dist[v] == INF) {
                dist[v] = dist[u] + 1;
                q.push(v);
                endNode = v;
            }
        }
    }
    SET(dist, INF, 2500);
    dist[endNode] = 0;
    q.push(endNode);
    int otherEndNode = endNode;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : children[u]) {
            if (dist[v] == INF) {
                dist[v] = dist[u] + 1;
                q.push(v);
                otherEndNode = v;
            }
        }
    }
    SET(dist2, INF, 2500);
    dist2[otherEndNode] = 0;
    q.push(otherEndNode);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int child : children[u]) {
            if (dist2[child] == INF) {
                dist2[child] = dist2[u] + 1;
                q.push(child);
            }
        }
    }
    int diameter = dist[otherEndNode];
    F0R(i, n) {
        if (dist[i] <= (diameter+1)/2 && dist2[i] <= (diameter+1)/2) {
            return mp(diameter, i);
        }
    }
    assert(false);
}

ii removedEdge, addedEdge;
int solve() {
    ii diam = getDiam(0);
    int ans = INF;
    for (ii edge : edges) {
        children[edge.pA].erase(edge.pB);
        children[edge.pB].erase(edge.pA);
        ii diam1 = getDiam(edge.pA), diam2 = getDiam(edge.pB);
        children[diam1.pB].insert(diam2.pB);
        children[diam2.pB].insert(diam1.pB);
        ii diam3 = getDiam(0);
        if (ans > diam3.pA) {
            ans = diam3.pA;
            removedEdge = edge;
            addedEdge = mp(diam1.pB, diam2.pB);
        }
        children[diam2.pB].erase(diam1.pB);
        children[diam1.pB].erase(diam2.pB);
        children[edge.pA].insert(edge.pB);
        children[edge.pB].insert(edge.pA);
    }
    return ans;
}

int main() {
    int N; cin >> N;
    F0R1(caseNum, N) {
        cin >> n;
        F0R(i, n) children[i].clear();
        edges.clear();
        F0R(i, n - 1) {
            int a, b; cin >> a >> b;
            children[--a].insert(--b);
            edges.pb(mp(a, b));
            children[b].insert(a);
        }

        int ans = solve();
        cout << ans << endl << removedEdge.pA+1 << " " << removedEdge.pB+1 << endl << addedEdge.pA+1 << " " << addedEdge.pB+1 << endl;
    }

    return 0;
}
