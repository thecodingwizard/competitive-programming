/*
ID: nathan.18
TASK: ditch
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
#define READGRID(arr, dim) F0R(i, dim) F0R(j, dim) cin >> arr[i][j];
typedef pair<int, int> ii;
typedef pair<ii, int> iii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vl;

ll res[200][200], mf, f;
int s, t;
vi p;
vi children[200];

void augment(int v, ll minEdge) {
    if (v == s) { f = minEdge; return; }
    else if (p[v] != -1) { augment(p[v], min(minEdge, res[p[v]][v]));
        res[p[v]][v] -= f; res[v][p[v]] += f; }
}

int main() {
    freopen("ditch.in", "r", stdin);
    freopen("ditch.out", "w", stdout);

    int n, m; cin >> n >> m;
    SET2D(res, 0, 200, 200);
    F0R(i, n) {
        int s, e, c; cin >> s >> e >> c;
        res[--s][--e] += c;
        children[s].push_back(e);
        children[e].push_back(s);
    }

    s = 0, t = m-1;

    mf = 0;
    while (1) {
        f = 0;
        vi dist(200, INF); dist[s] = 0; queue<int> q; q.push(s);
        p.assign(200, -1);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u == t) break;
            for (int child : children[u])
                if (res[u][child] > 0 && dist[child] == INF)
                    dist[child] = dist[u] + 1, q.push(child), p[child] = u;
        }
        augment(t, INF);
        if (f == 0) break;
        mf += f;
    }

    cout << mf << endl;

    return 0;
}