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

int r, c;
int A[100][100];
bool visited[100][100];
vii order;
int dist[100][100];

void topoSort(int i, int j) {
    visited[i][j] = true;
    int dx[4] = { -1, 0, 1, 0 };
    int dy[4] = { 0, -1, 0, 1 };
    F0R(x, 4) {
        int a = i + dx[x], b = j + dy[x];
        if (a < 0 || a >= r || b < 0 || b >= c) continue;
        if (visited[a][b]) continue;
        if (A[i][j] <= A[a][b]) continue;
        topoSort(a, b);
    }
    order.pb(mp(i, j));
}

int main() {
    int t; cin >> t;
    while (t--) {
        string name; cin >> name;
        cin >> r >> c;
        F0R(i, r) {
            F0R(j, c) cin >> A[i][j];
        }
        SET2D(visited, false, 100, 100);
        SET2D(dist, 0, 100, 100);
        order.clear();
        F0R(i, r) {
            F0R(j, c) {
                if (!visited[i][j]) {
                    topoSort(i, j);
                }
            }
        }
        reverse(order.begin(), order.end());
        int ans = 0;
        for (ii x : order) {
            int dx[4] = { -1, 0, 1, 0 };
            int dy[4] = { 0, 1, 0, -1 };
            F0R(i, 4) {
                int a = x.pA + dx[i], b = x.pB + dy[i];
                if (a < 0 || a >= r || b < 0 || b >= c) continue;
                if (A[x.pA][x.pB] <= A[a][b]) continue;
                MAX(dist[a][b], dist[x.pA][x.pB]+1);
                MAX(ans, dist[a][b]);
            }
        }
        cout << name << ": " << ans+1 << endl;
    }

    return 0;
}