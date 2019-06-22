/*
 * Binary search on seg tree with range updates and range minimum queries
 *
 * For each dish, do -1 from 1...dish_val
 * For each pupil, do +1 from 1...pupil_cash
 *
 * Then binary search for the largest number where the value is < 0
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

#define MAXN 1000010

int st[MAXN*4], lazy[MAXN*4];

void down(int p, int i, int j) {
    if (lazy[p] == 0) return;
    st[p] += lazy[p];
    if (i != j) {
        lazy[p << 1] += lazy[p];
        lazy[(p << 1) + 1] += lazy[p];
    }
    lazy[p] = 0;
}

void upd(int p, int i, int j, int k, int v) {
    down(p, i, j);
    if (i > k) return;
    if (j <= k) {
        lazy[p] += v;
        return;
    }
    int mid = (i + j) / 2;
    upd(p << 1, i, mid, k, v);
    upd((p << 1) + 1, mid + 1, j, k, v);
    down(p << 1, i, mid); down((p << 1) + 1, mid + 1, j);
    st[p] = min(st[(p << 1)], st[(p << 1) + 1]);
}

int qry(int p, int i, int j) {
    down(p, i, j);
    if (st[p] >= 0) return -1;
    if (i == j) return i;
    int right = qry((p << 1) + 1, (i+j)/2+1, j);
    if (right != -1) return right;
    return qry((p << 1), i, (i+j)/2);
}

int main() {
    setupIO();
    SET(st, 0, MAXN*4);
    SET(lazy, 0, MAXN*4);

    int n, m; cin >> n >> m;
    int A[n];
    F0R(i, n) {
        cin >> A[i];
        upd(1, 0, MAXN, A[i], -1);
    }
    int B[m];
    F0R(i, m) {
        cin >> B[i];
        upd(1, 0, MAXN, B[i], 1);
    }
    int q; cin >> q;
    F0R(i, q) {
        int cmd, tgt, val; cin >> cmd >> tgt >> val; --tgt;
        if (cmd == 1) {
            upd(1, 0, MAXN, A[tgt], 1);
            A[tgt] = val;
            upd(1, 0, MAXN, A[tgt], -1);
        } else {
            upd(1, 0, MAXN, B[tgt], -1);
            B[tgt] = val;
            upd(1, 0, MAXN, B[tgt], 1);
        }
        cout << qry(1, 0, MAXN) << endl;
    }

    return 0;
}