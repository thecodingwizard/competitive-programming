/*
ID: nathan.18
TASK: milk6
LANG: C++
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

int n, m;
ll res[40][40], f;
ll origRes[40][40];
vi p;
vector<pair<ii, ii>> edges;

void augment(int v, ll minEdge) {     // traverse BFS spanning tree from s to t
    if (v == 1) { f = minEdge; return; }  // record minEdge in a global variable f
    else if (p[v] != -1) { augment(p[v], min(minEdge, res[p[v]][v])); // recursive
        res[p[v]][v] -= f; res[v][p[v]] += f; }       // update
}

void copyRes() {
    F0R(i, 40) F0R(j, 40) res[i][j] = origRes[i][j];
}

int main() {
    setupIO("milk6");

    cin >> n >> m;
    SET2D(origRes, 0, 40, 40);
    F0R(i, m) {
        int s, e, c; cin >> s >> e >> c;
        origRes[s][e] += c*1000+1;
        edges.pb(mp(mp(s, e), mp(c, i+1)));
    }

    copyRes();
    ll mf = 0;
    while (true) {
        f = 0;
        vi dist(40, INF);
        dist[1] = 0;
        queue<int> q;
        q.push(1);
        p.assign(40, -1);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (u == n) break;
            for (int v = 1; v <= n; v++)
                if (res[u][v] > 0 && dist[v] == INF)
                    dist[v] = dist[u] + 1, q.push(v), p[v] = u;
        }
        augment(n, INF);
        if (f == 0) break;
        mf += f;
    }

    ll ansMF = mf;
    ll startMF = 0;

    vi ans;

    F0R(edge, m) {
        copyRes();
        ii magic = edges[edge].pA;
        ll weight = edges[edge].pB.pA*1000+1;
        res[magic.pA][magic.pB] -= weight;
        mf = startMF;
        while (true) {
            f = 0;
            vi dist(40, INF);
            dist[1] = 0;
            queue<int> q;
            q.push(1);
            p.assign(40, -1);
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                if (u == n) break;
                for (int v = 1; v <= n; v++)
                    if (res[u][v] > 0 && dist[v] == INF)
                        dist[v] = dist[u] + 1, q.push(v), p[v] = u;
            }
            augment(n, INF);
            if (f == 0) break;
            mf += f;
        }
        if (mf+weight <= ansMF) {
            ans.pb(edge+1);
            origRes[magic.pA][magic.pB] -= weight;
            startMF += weight;
        }
    }

    cout << (ansMF-ans.size())/1000 << " " << ans.size() << endl;
    for (int x : ans) cout << x << endl;

    return 0;
}
