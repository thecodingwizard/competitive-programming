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

int main() {
    int m, n, a, b, c, d; cin >> m >> n >> a >> b >> c >> d;
    int A[n][m]; F0R(i, n) F0R(j, m) cin >> A[i][j];
    int ps[n+10][m+10]; SET2D(ps, 0, n+10, m+10);
    F0R1(i, n) F0R1(j, m) ps[i][j] = ps[i - 1][j] + ps[i][j - 1] - ps[i - 1][j - 1] + A[i - 1][j - 1];

    int globalBest = 0;
    pair<ii, ii> ans;
    F0R1(x, n - b + 1) {
        int w = 1;
        int best[1001]; SET(best, INF, 1001);
        ii bestAns[1001];
        for (int y = w + 1; y < w + a - c; y++) {
            for (int z = x + 1; z < x + b - d; z++) {
                int res = ps[z + d - 1][y + c - 1] - ps[z + d - 1][y - 1] - ps[z - 1][y + c - 1] + ps[z - 1][y - 1];
                if (res < best[y]) {
                    best[y] = res;
                    bestAns[y] = { y, z };
                }
            }
        }
        F0R1(w, m - a + 1) {
            int y = w + a - c - 1;
            for (int z = x + 1; z < x + b - d; z++) {
                int res = ps[z + d - 1][y + c - 1] - ps[z + d - 1][y - 1] - ps[z - 1][y + c - 1] + ps[z - 1][y - 1];
                if (res < best[y]) {
                    best[y] = res;
                    bestAns[y] = { y, z };
                }
            }
            int res = ps[x + b - 1][w + a - 1] - ps[x + b - 1][w - 1] - ps[x - 1][w + a - 1] + ps[x - 1][w - 1];
            for (int y = w + 1; y < w + a - c; y++) {
                if (globalBest < res - best[y]) {
                    globalBest = res - best[y];
                    ans = { { w, x }, bestAns[y] };
                }
            }
        }
    }
    cout << ans.pA.pA << " " << ans.pA.pB << endl << ans.pB.pA << " " << ans.pB.pB << endl;

    return 0;
}
