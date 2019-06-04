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

void fastscan(int &n) {
    bool negative = false;
    register int c;
    n = 0;
    c = getchar();
    if (c == '-') {
        negative = true;
        c = getchar();
    }
    for (; (c > 47 && c < 58); c = getchar()) { n = n * 10 + c - 48; }
    if (negative) { n *= -1; }
}

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

int main() {
    setupIO("dining");

    int n, m, k; cin >> n >> m >> k;
    vii children[n];
    F0R(i, m) {
        int a, b, l; cin >> a >> b >> l;
        a--; b--;
        children[a].pb(mp(b, l));
        children[b].pb(mp(a, l));
    }
    priority_queue<ii, vii, greater<ii>> dijkstra;
    dijkstra.push(mp(0, n-1));
    int cost[n]; SET(cost, INF, n);
    cost[n-1] = 0;
    while (!dijkstra.empty()) {
        ii next = dijkstra.top(); dijkstra.pop();
        if (next.pA > cost[next.pB]) continue;
        for (ii child : children[next.pB]) {
            if (cost[child.pA] > next.pA + child.pB) {
                cost[child.pA] = next.pA + child.pB;
                dijkstra.push(mp(cost[child.pA], child.pA));
            }
        }
    }

    priority_queue<ii, vector<ii>, greater<ii>> pq;
    F0R(i, k) {
        int p, y; cin >> p >> y;
        p--;
        pq.push(mp(cost[p] - y, p));
    }

    bool visited[n]; SET(visited, false, n);
    bool can[n]; SET(can, false, n-1);
    while (!pq.empty()) {
        ii next = pq.top(); pq.pop();
        if (visited[next.pB]) continue;
        visited[next.pB] = true;
        int cow = next.pB;
        int addlCost = next.pA - cost[cow];
        if (addlCost <= 0) {
            can[cow] = true;
        }

        for (ii child : children[cow]) {
            pq.push(mp(next.pA + child.pB, child.pA));
        }
    }

    F0R(i, n-1) {
        if (can[i]) cout << 1 << endl;
        else cout << 0 << endl;
    }


    return 0;
}