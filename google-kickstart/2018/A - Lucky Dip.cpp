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

int n, k;
ll A[20000];
ll ps[20000];

double memo[50010];
double solve(int k) {
    if (memo[k] != -1) return memo[k];
    if (k == 0) return (double)ps[n-1]/n;
    double best = 0;
    int lo = 0, hi = n, mid;
    while (lo + 1 < hi) {
        mid = (lo + hi) / 2;
        double ans1 = (1.0/n)*ps[mid-1] + (double)(n-mid)/n*solve(k - 1);
        double ans2 = (1.0/n)*ps[mid] + (double)(n-mid-1)/n*solve(k - 1);
        MAX(best, ans1);
        if (ans1 < ans2) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    MAX(best, solve(0));
    return memo[k] = best;
}

int main() {
    int t; cin >> t;
    F0R1(caseNum, t) {
        cin >> n >> k;
        F0R(i, n) cin >> A[i];
        sort(A, A+n);
        reverse(A, A+n);
        ps[0] = A[0];
        FOR(i, 1, n) ps[i] = ps[i - 1] + A[i];
        SET(memo, -1, 50010);
        cout << fixed << setprecision(6);
        cout << "Case #" << caseNum << ": " << solve(k) << endl;
    }

    return 0;
}