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

// Note: This solution is a little bit sketchier than the method described in the analysis.

int n, k;
ii A[100000];
int memo[100000][200];
vii toConsider[101000];

int dp(int cow, int kLeft) {
    if (kLeft < 0) kLeft = 0;
    if (n - cow <= kLeft) return -INF;
    if (memo[cow][kLeft] != INF) return memo[cow][kLeft];
    int len = A[cow].pB - A[cow].pA;
    int best = len;
    for (ii x : toConsider[cow + kLeft + 1]) {
        if (A[cow].pB >= x.pB) {
            MAX(best, len + x.pA - (A[cow].pB - x.pB));
        } else {
            MAX(best, len + x.pA);
        }
    }
    memo[cow][kLeft] = best;
    toConsider[cow + kLeft].pb(mp(memo[cow][kLeft], A[cow].pA));
    return memo[cow][kLeft];
}

int main() {
    setupIO("lifeguards");

    cin >> n >> k;
    F0R(i, n) cin >> A[i].pA >> A[i].pB;
    sort(A, A+n);
    SET2D(memo, INF, 100000, 200);

    F0Rd(i, n) {
        F0R(j, k+1) dp(i, j);
    }

    int best = 0;
    F0R(i, k+1) MAX(best, dp(i, k - i));
    cout << best << endl;

    return 0;
}