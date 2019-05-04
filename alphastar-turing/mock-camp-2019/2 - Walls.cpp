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

vi regions[200];
bool isAdj[200][200];
int dist[200][200];

bool hasEdge(int region, int i, int j) {
    F0R(a, regions[region].size()) {
        if (regions[region][a] == i && regions[region][(a+1)%regions[region].size()] == j) return true;
    }
    return false;
}

bool isIn(int region, int town) {
    for (int x : regions[region]) if (x == town) return true;
    return false;
}

int main() {
    int m, n, l; cin >> m >> n >> l;
    int A[l]; F0R(i, l) cin >> A[i];

    F0R(i, m) {
        int x; cin >> x;
        F0R(j, x) {
            int y; cin >> y;
            regions[i].pb(y);
        }
    }

    reverse(all(regions[m - 1]));
    SET2D(isAdj, false, m, m);
    SET2D(dist, -1, m, m);

    F0R(i, m) {
        F0R(j, m) {
            if (i == j) continue;
            F0R(k, regions[i].size()) {
                int a = regions[i][k], b = regions[i][(k+1)%regions[i].size()];
                if (hasEdge(j, a, b) || hasEdge(j, b, a)) isAdj[i][j] = true;
            }
        }
    }

    F0R(i, m) {
        queue<int> q; q.push(i);
        dist[i][i] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            F0R(j, m) {
                if (!isAdj[u][j]) continue;
                if (dist[i][j] == -1) {
                    dist[i][j] = dist[i][u] + 1;
                    q.push(j);
                }
            }
        }
    }

    int best = INF, bestAns = -1;
    F0R(i, m) {
        int regAns = 0;
        F0R(j, l) {
            int smallest = INF;
            F0R(k, m) {
                if (!isIn(k, A[j])) continue;
                MIN(smallest, dist[k][i]);
            }
            regAns += smallest;
        }
        if (regAns < best) {
            best = regAns;
            bestAns = i + 1;
        }
    }
    cout << best << endl << bestAns << endl;

    return 0;
}
