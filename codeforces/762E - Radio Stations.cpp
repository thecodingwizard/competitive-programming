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

struct Tower {
    int r, x, f, i;
};

bool operator<(const Tower &lhs, const Tower &rhs) {
    if (lhs.r == rhs.r) return lhs.i < rhs.i;
    return lhs.r > rhs.r;
}

int tree[400000];
int tree2[400000];
Tower A[100000], B[100000];
int idxSortedByX[100000];

int query(int p, int i, int j, int qLeft, int qRight) {
    if (B[i].x > qRight || B[j].x < qLeft) return 0;
    if (B[i].x >= qLeft && B[j].x <= qRight) return tree[p];
    int mid = (i + j) / 2;
    return query((p << 1), i, mid, qLeft, qRight) + query((p << 1) + 1, mid + 1, j, qLeft, qRight);
}

void update(int p, int i, int j, int targIdx, int val) {
    if (i > targIdx || j < targIdx) return;
    if (i == j && i == targIdx) {
        tree[p] += val;
        return;
    }
    tree[p] += val;
    int mid = (i + j) / 2;
    update((p << 1), i, mid, targIdx, val);
    update((p << 1) + 1, mid + 1, j, targIdx, val);
}

int query2(int p, int i, int j, int qLeft, int qRight) {
    if (B[i].x > qRight || B[j].x < qLeft) return 0;
    if (B[i].x >= qLeft && B[j].x <= qRight) return tree2[p];
    int mid = (i + j) / 2;
    return query2((p << 1), i, mid, qLeft, qRight) + query2((p << 1) + 1, mid + 1, j, qLeft, qRight);
}

void update2(int p, int i, int j, int targIdx, int val) {
    if (i > targIdx || j < targIdx) return;
    if (i == j && i == targIdx) {
        tree2[p] += val;
        return;
    }
    tree2[p] += val;
    int mid = (i + j) / 2;
    update2((p << 1), i, mid, targIdx, val);
    update2((p << 1) + 1, mid + 1, j, targIdx, val);
}

int main() {
    int n, k; cin >> n >> k;
    F0R(i, n) {
        int x, r, f; cin >> x >> r >> f;
        A[i] = Tower{r, x, f, -1};
    }
    sort(A, A+n);
    int idxSortedByK[n]; F0R(i, n) idxSortedByK[i] = i;
    sort(idxSortedByK, idxSortedByK + n, [](const int lhs, const int rhs) {
        return A[lhs].f < A[rhs].f;
    });
    F0R(i, n) idxSortedByX[i] = i;
    sort(idxSortedByX, idxSortedByX + n, [](const int lhs, const int rhs) {
        return A[lhs].x < A[rhs].x;
    });

    F0R(i, n) {
        A[idxSortedByX[i]].i = i;
        B[i] = A[idxSortedByX[i]];
    }

    SET(tree, 0, 2*n);
    SET(tree2, 0, 2*n);

    set<Tower> validStuff;

    ll ans = 0;
    vi undoOps;
    vi undoOps2;
    int lPtr = 0, rPtr = 0;
    validStuff.clear();
    F0R1(targK, 10000) {
        while (rPtr < n && A[idxSortedByK[rPtr]].f <= targK) {
            validStuff.insert(A[idxSortedByK[rPtr]]);
            rPtr++;
        }
        while (lPtr < n && A[idxSortedByK[lPtr]].f < targK - k) {
            validStuff.erase(A[idxSortedByK[lPtr]]);
            lPtr++;
        }

        for (const Tower &tower : validStuff) {
            int r = tower.r, x = tower.x, ki = tower.f, i = tower.i;
            int queryLeft = x - r, queryRight = x + r;
            if (ki == targK) {
                ans += query2(1, 0, n - 1, queryLeft, queryRight);
            }
            ans += query(1, 0, n - 1, queryLeft, queryRight);
            if (ki == targK) {
                update(1, 0, n - 1, i, 1);
                undoOps.pb(i);
            } else {
                update2(1, 0, n - 1, i, 1);
                undoOps2.pb(i);
            }
        }
        for (int x : undoOps) {
            update(1, 0, n - 1, x, -1);
        }
        for (int x : undoOps2) {
            update2(1, 0, n - 1, x, -1);
        }
        undoOps.clear();
        undoOps2.clear();
    }
    cout << ans << endl;

    return 0;
}