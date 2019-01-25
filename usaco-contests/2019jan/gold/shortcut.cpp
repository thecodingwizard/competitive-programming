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
    setupIO("shortcut");

    int n, m, t; cin >> n >> m >> t;
    int cowCt[n];
    vii adjList[n];
    SET(cowCt, 0, n);
    F0R(i, n) {
        cin >> cowCt[i];
    }
    F0R(i, m) {
        int a, b, t; cin >> a >> b >> t;
        --a; --b;
        adjList[a].pb(mp(b, t));
        adjList[b].pb(mp(a, t));
    }

    int dist[n];
    int parent[n];
    SET(dist, INF, n);

    priority_queue<ii, vii, greater<ii>> q;
    q.push(mp(0, 0));
    dist[0] = 0;
    parent[0] = -1;
    while (!q.empty()) {
        ii next = q.top(); q.pop();
        if (dist[next.pB] < next.pA) continue;

        for (ii child : adjList[next.pB]) {
            int newDist = child.pB + dist[next.pB];
            if (newDist < dist[child.pA]) {
                dist[child.pA] = newDist;
                parent[child.pA] = next.pB;
                q.push(mp(dist[child.pA], child.pA));
            } else if (newDist == dist[child.pA]) {
                bool betterPath = true;
                int altOp = next.pB, curOp = parent[child.pA];
                while (altOp != -1 && curOp != -1) {
                    if (altOp > curOp) {
                        betterPath = false;
                        break;
                    } else if (altOp < curOp) break;
                    altOp = parent[altOp], curOp = parent[curOp];
                }
                if (betterPath) {
                    parent[child.pA] = next.pB;
                    q.push(mp(dist[child.pA], child.pA));
                }
            }
        }
    }

    ll useCt[n];
    SET(useCt, 0, n);
    F0R(i, n) {
        int pasture = i;
        while (pasture != -1) {
            useCt[pasture] += cowCt[i];
            pasture = parent[pasture];
        }
    }

    ll ans = 0;
    F0R(i, n) {
        ans = max(ans, ((ll)(dist[i] - t))*useCt[i]);
    }
    cout << ans << endl;

    return 0;
}
