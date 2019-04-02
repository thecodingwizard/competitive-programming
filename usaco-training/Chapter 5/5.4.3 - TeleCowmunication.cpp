/*
ID: nathan.18
TASK: telecow
LANG: C++11
*/

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

int n, m, s, t;

vi children[200];
int res[200][200];
int parent[200], flow;

void augment(int u, int minEdge) {
    if (u == s*2) {
        flow = minEdge;
    } else {
        augment(parent[u], min(minEdge, res[parent[u]][u]));
        res[parent[u]][u] -= flow;
        res[u][parent[u]] += flow;
    }
}

int getflow() {
    int mf = 0;

    bool visited[200];
    int oldres[200][200];
    F0R(i, n*2) F0R(j, n*2) oldres[i][j] = res[i][j];
    while (true) {
        queue<int> q;
        flow = 0;
        SET(visited, false, 200);
        SET(parent, -1, 200);
        q.push(s*2);
        visited[s*2] = true;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u == t*2+1) {
                break;
            }
            for (int v : children[u]) {
                if (res[u][v] > 0 && !visited[v]) {
                    visited[v] = true;
                    q.push(v);
                    parent[v] = u;
                }
            }
        }
        if (parent[t*2+1] == -1) break;
        augment(t*2+1, INF);
        if (flow == 0) break;
        mf += flow;
    }
    F0R(i, n*2) F0R(j, n*2) res[i][j] = oldres[i][j];

    return mf;
}

int main() {
    setupIO("telecow");

    cin >> n >> m >> s >> t;
    --s; --t;
    SET2D(res, 0, 200, 200);
    F0R(i, n) {
        children[i*2].pb(i*2+1);
        res[i*2][i*2+1] = 1;
    }
    F0R(i, m) {
        int a, b; cin >> a >> b;
        --a; --b;
        children[a*2+1].pb(b*2);
        children[b*2+1].pb(a*2);
        res[a*2+1][b*2] = INF;
        res[b*2+1][a*2] = INF;
    }
    res[s*2][s*2+1] = INF;
    res[t*2][t*2+1] = INF;


    int ans = getflow();
    cout << ans << endl;
    int curAns = ans;
    F0R(i, n) {
        if (i == s || i == t) continue;
        res[i*2][i*2+1] = 0;
        int newAns = getflow();
        if (newAns == curAns - 1) {
            if (curAns == ans) {
                // first
                cout << i+1;
            } else {
                cout << " " << i+1;
            }
            curAns--;
        } else {
            res[i*2][i*2+1] = 1;
        }
    }
    cout << endl;

    return 0;
}
