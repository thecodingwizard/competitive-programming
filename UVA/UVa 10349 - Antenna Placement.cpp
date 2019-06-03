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

int h, w, nodeCt;
bool A[40][10]; // true if '*'
bool visited[40][10];
vii children[40][10];
ii match[40][10];

void dfs(int x, int y, bool source) {
    nodeCt++;
    visited[x][y] = true;
    int dx[4] = { -1, 0, 1, 0 };
    int dy[4] = { 0, 1, 0, -1 };
    F0R(i, 4) {
        int x1 = x + dx[i], y1 = y + dy[i];
        if (x1 < 0 || x1 >= h || y1 < 0 || y1 >= w) continue;
        if (!visited[x1][y1] && A[x1][y1]) {
            if (source) children[x][y].pb(mp(x1, y1));
            else children[x1][y1].pb(mp(x, y));
            dfs(x1, y1, !source);
        }
    }
}

int augment(ii u) {
    if (visited[u.pA][u.pB]) return 0;
    visited[u.pA][u.pB] = true;
    for (ii v : children[u.pA][u.pB]) {
        if (match[v.pA][v.pB].pA == -1 || augment(match[v.pA][v.pB])) {
            match[v.pA][v.pB] = u; return 1;
        }
    }
    return 0;
}

int main() {
    int t; cin >> t;
    while (t--) {
        cin >> h >> w;
        F0R(i, h) {
            F0R(j, w) {
                char c; cin >> c;
                A[i][j] = c == '*';
                children[i][j].clear();
            }
        }

        int mcbm = 0;
        nodeCt = 0;
        SET2D(visited, false, 40, 10);
        F0R(x, h) {
            F0R(y, w) {
                if (A[x][y] && !visited[x][y]) {
                    dfs(x, y, true);
                }
            }
        }
        F0R(i, h) F0R(j, w) match[i][j] = { -1, -1 };
        F0R(i, h) {
            F0R(j, w) {
                // Note: can be optimized, don't have to actually visit every node
                SET2D(visited, false, 40, 10);
                mcbm += augment({ i, j });
            }
        }
        cout << nodeCt - mcbm << endl;
    }

    return 0;
}
