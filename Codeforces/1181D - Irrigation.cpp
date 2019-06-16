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

class FenwickTree {
private:
    vi ft;

public:
    FenwickTree() {}
    FenwickTree(int n) { ft.assign(n + 1, 0); }

    int rsq(int b) {
        int sum = 0; for (; b; b -= LSOne(b)) sum += ft[b];
        return sum; }

    int rsq(int a, int b) {
        return rsq(b) - (a == 1 ? 0 : rsq(a - 1)); }

    void adjust(int k, int v) {
        for (; k < (int)ft.size(); k += LSOne(k)) ft[k] += v; }
};

int main() {
    setupIO();

    int n, m, q; cin >> n >> m >> q;
    int A[n]; F0R(i, n) cin >> A[i];
    pair<ll, int> B[q];
    F0R(i, q) {
        ll k; cin >> k;
        B[i] = mp(k, i);
    }
    int ans[q];
    sort(B, B+q);
    int C[m]; SET(C, 0, m);
    F0R(i, n) {
        C[A[i]-1]++;
    }
    vii smth; F0R(i, m) smth.pb(mp(C[i], i)); SORT(smth);
    pair<ll, int> D[m];
    ll sum = 0;
    int itr = 0;
    for (ii x : smth) {
        itr++;
        sum += x.pA;
        D[x.pB] = mp((ll)x.pA*itr - sum, x.pB);
    }
    sort(D, D+m);

    int dIdx = 0;
    FenwickTree wtf(m);

    F0R(i, q) {
        ll k = B[i].pA - n;
        while (dIdx < m && D[dIdx].pA < k) {
            wtf.adjust(D[dIdx].pB + 1, 1);
            dIdx++;
        }
        ll other = D[dIdx-1].pA;
        ll realK = (k - other) % dIdx;
        if (realK == 0) realK = dIdx;
        int lo = 1, hi = m+1, mid, xsd = m;
        while (lo < hi) {
            mid = (lo + hi)/2;
            int xx = wtf.rsq(mid);
            if (xx == realK) xsd = mid;
            if (xx < realK) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        ans[B[i].pB] = xsd;
    }

    F0R(i, q) cout << ans[i] << endl;

    return 0;
}