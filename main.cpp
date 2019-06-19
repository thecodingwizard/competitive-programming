/*
 * Weak test data, this code should not get AC (It should TLE/WA).
 *
 * I sorted by x-coordinate and did coordinate compression on y.
 *
 * Then swept from left to right for x-coordinate and considered that to be bottom left corner.
 * For every other coordinate to the right of it and above it (note this step is wrong, should WA),
 * add it to a fenwick tree and consider that point as the top right corner. If the number of
 * points in this rectangle is exactly t, then exit program early (note this should still cause TLE).
 *
 * O(n^2) + incorrect algorithm but weak test data :/
 */

#include <bits/stdc++.h>

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
#define LL_INF 4500000000000000000LL
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

void setupIO(const string &PROB = "") {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if (PROB.length() != 0) {
        ifstream infile(PROB + ".in");
        if (infile.good()) {
            freopen((PROB + ".in").c_str(), "r", stdin);
            freopen((PROB + ".out").c_str(), "w", stdout);
        }
    }
}

/* ============================ */

int ft[10001];

void adjust(int k, int v) {
    for (; k <= 10000; k += LSOne(k)) ft[k] += v;
}

int query(int k) {
    int a = 0;
    for (; k > 0; k -= LSOne(k)) a += ft[k];
    return a;
}

int main() {
    setupIO();
    int n, t; cin >> n >> t;
    assert(n <= 10000); // Bounds seem to be wrong, should be <= 10,000 not 20,000
    pair<ii, int> A[n];
    F0R(i, n) {
        cin >> A[i].pA.pA >> A[i].pA.pB;
        A[i].pB = i + 1;
    }
    sort(A, A+n);
    set<int> yVals;
    F0R(i, n) yVals.insert(A[i].pA.pB);
    map<int, int> yMap;
    int idx = 1;
    for (int x : yVals) yMap[x] = idx++;
    F0R(i, n) A[i].pA.pB = yMap[A[i].pA.pB];

    SET(ft, 0, n+1);

    int best = INF;
    ii bestAns;
    F0R(i, n) {
        FOR(j, i, n) {
            adjust(A[j].pA.pB, 1);
            int op = abs(query(A[j].pA.pB) - query(A[i].pA.pB)) + 1;
            if (op >= t) {
                if (op - t < best) {
                    best = op - t;
                    bestAns = mp(A[i].pB, A[j].pB);
                }
            }
        }
        FOR(j, i, n) {
            adjust(A[j].pA.pB, -1);
        }
    }
    cout << bestAns.pA << " " << bestAns.pB << endl;

    return 0;
}