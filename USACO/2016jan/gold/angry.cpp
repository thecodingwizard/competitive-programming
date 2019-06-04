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

void fastscan(int &n) {
    bool negative = false;
    register int c;
    n = 0;
    c = getchar();
    if (c == '-') {
        negative = true;
        c = getchar();
    }
    for (; (c > 47 && c < 58); c = getchar()) { n = n * 10 + c - 48; }
    if (negative) { n *= -1; }
}

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

int n, A[50000];
int R[50000], L[50000];

bool can(ll mid) {
    int r = 0;
    F0R(l, n) {
        for (; r != n - 1 && A[r + 1] - A[l] <= mid; r++);
        if (max(R[r], L[l])*2+2 <= mid) return true;
    }
    return false;
}

int main() {
    setupIO("angry");

    cin >> n;
    F0R(i, n) cin >> A[i];
    sort(A, A + n);

    L[0] = 0;
    int idx = 0;
    FOR(i, 1, n) {
        int best = INF;
        bool first = true;
        while (true) {
            if (first) {
                first = false;
                int nextVal = max(A[i] - A[idx], L[idx] + 1);
                best = nextVal;
            } else if (idx + 1 < i) {
                int nextVal = max(A[i] - A[idx + 1], L[idx + 1] + 1);
                if (nextVal < best) {
                    best = nextVal;
                    idx++;
                } else {
                    break;
                }
            } else {
                break;
            }
        }
        L[i] = best;
    }

    idx = n - 1;
    R[n - 1] = 0;
    F0Rd(i, n - 1) {
        int best = INF;
        bool first = true;
        while (true) {
            if (first) {
                first = false;
                int nextVal = max(A[idx] - A[i], R[idx] + 1);
                best = nextVal;
            } else if (idx - 1 > i) {
                int nextVal = max(A[idx - 1] - A[i], R[idx - 1] + 1);
                if (nextVal < best) {
                    best = nextVal;
                    idx--;
                } else {
                    break;
                }
            } else {
                break;
            }
        }
        R[i] = best;
    }

    ll lo = 0, hi = 2000000000, mid, ans;
    while (lo + 1 < hi) {
        mid = (lo + hi) / 2;
        if (can(mid)) {
            ans = mid;
            hi = mid;
        } else {
            lo = mid;
        }
    }
    cout << fixed << setprecision(1);
    cout << double(ans)/2.0 << endl;
}
