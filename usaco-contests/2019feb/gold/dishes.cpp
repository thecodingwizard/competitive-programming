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

int n, A[100000];
int val[100100];

bool can(int num) {
    if (num > n) {
        exit(0);
    }
    vi needed;
    F0R(i, num) {
        needed.pb(A[i]);
    }
    SORT(needed);
    int idx = 0;
    set<pair<ii, bool>> dishes;
    F0R(i, num) {
        auto it = dishes.upper_bound(mp(mp(A[i], INF), false));
        if (it == dishes.end()) {
            dishes.insert(mp(mp(A[i], -1), true));
            val[A[i]] = -1;
        } else if (it->pB) {
            dishes.insert(mp(mp(A[i], it->pA.pA), true));
            val[A[i]] = it->pA.pA;
            dishes.insert(mp(mp(it->pA.pA, it->pA.pB), false));
            dishes.erase(it);
        } else {
            return false;
        }

        while (true) {
            it = dishes.begin();
            if (it == dishes.end() || it->pA.pA != needed[idx]) break;
            int below = it->pA.pB;
            dishes.erase(it);
            if (below != -1) {
                dishes.erase(mp(mp(below, val[below]), false));
                dishes.insert(mp(mp(below, val[below]), true));
            }
            idx++;
        }
        if (!(dishes.empty() || idx < needed.size())) {
            exit(0);
        }
    }
    return true;
}

int main() {
    setupIO("dishes");

    cin >> n;
    F0R(i, n) cin >> A[i];

    int lo = 0, hi = n+1, mid, ans;
    while (lo + 1 < hi) {
        mid = (lo + hi)/2;
        if (can(mid)) {
            ans = mid;
            lo = mid;
        } else {
            hi = mid;
        }
    }
    cout << ans << endl;

    return 0;
}
