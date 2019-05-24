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

ll bit[600000];

void bit_add(int loc, int val) {
    for (; loc <= 500000; loc += LSOne(loc)) {
        bit[loc] += val;
    }
}

ll bit_query(int loc) {
    ll ans = 0;
    for (; loc > 0; loc -= LSOne(loc)) {
        ans += bit[loc];
    }
    return ans;
}

int bit2[600000];

void bit2_add(int loc, int val) {
    for (; loc <= 500000; loc += LSOne(loc)) {
        bit2[loc] += val;
    }
}

int bit2_query(int loc) {
    int ans = 0;
    for (; loc > 0; loc -= LSOne(loc)) {
        ans += bit2[loc];
    }
    return ans;
}

int mappedLoc[500000];
ii A[500000], magic[500000];

int main() {
    int n;
    ll w;
    cin >> n >> w;
    F0R(i, n) cin >> A[i].pA >> A[i].pB;
    sort(A, A+n, [](ii lhs, ii rhs) {
        return ((double)lhs.pA)/lhs.pB > ((double)rhs.pA)/rhs.pB;
    });
    F0R(i, n) {
        magic[i] = { A[i].pB, i };
    }
    sort(magic, magic + n);
    F0R(i, n) {
        mappedLoc[magic[i].pB] = i;
    }
    F0R(i, n) {
        bit_add(mappedLoc[i] + 1, A[i].pB);
        bit2_add(mappedLoc[i] + 1, 1);
    }

    int ans = 0;
    F0R(i, n) {
        double pricePerQ = ((double)A[i].pA)/A[i].pB;
        double numCanTake = ((double)w)/pricePerQ;

        int lo = 0, hi = n, mid, curAns;
        while (lo < hi) {
            mid = (lo + hi)/2;
            ll num = bit_query(mid + 1);
            if (num <= numCanTake) {
                curAns = mid;
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }

        MAX(ans, bit2_query(curAns + 1));
        bit_add(mappedLoc[i] + 1, -A[i].pB);
        bit2_add(mappedLoc[i] + 1, -1);
    }
    cout << ans << endl;

    return 0;
}