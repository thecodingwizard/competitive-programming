/*
 * Segment tree, see comments for details
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

struct nVal {
    ll val; int ct;
};

nVal operator+(const nVal &lhs, const nVal &rhs) {
    return nVal{lhs.val + rhs.val, lhs.ct + rhs.ct};
}

bool operator<(const nVal &lhs, const nVal &rhs) {
    // minimize value, then minimize number of people
    if (lhs.val == rhs.val) return lhs.ct > rhs.ct;
    return lhs.val < rhs.val;
}

struct node {
    // nVal = { value, numberOfPeople }
    // x = node range value
    // l = leftmost person cannot be taken
    // r = rightmost person cannot be taken
    // lr = neither left nor right person can be taken
    nVal x = {0,0}, l = {0,0}, r = {0,0}, lr = {0,0};
};

// important: node a must come before node b
node merge(const node &a, const node &b) {
    node c;
    c.x = c.l = c.r = c.lr = { 0, 0 };

    c.l = max(a.l + b.l, a.lr + b.x);
    c.r = max(b.r + a.r, b.lr + a.x);
    c.lr = max(a.l + b.lr, a.lr + b.r);
    c.l = max(c.l, c.lr);
    c.r = max(c.r, c.lr);
    c.x = max(a.x + b.l, b.x + a.r);
    c.x = max(c.x, c.l);
    c.x = max(c.x, c.r);

    return c;
}

node st[300000*4];

void update(int p, int i, int j, int loc, ll val) {
    if (i > loc || j < loc) return;
    if (i == j && i == loc) {
        st[p].x = { val, 1 };
        return;
    }
    update((p << 1), i, (i+j)/2, loc, val);
    update((p << 1) + 1, (i+j)/2+1, j, loc, val);
    st[p] = merge(st[p << 1], st[(p << 1) + 1]);
}

ll query(int p, int i, int j, int k, node cur) {
    if (i == j) {
        if (merge(st[p], cur).x.ct <= k) return merge(st[p], cur).x.val;
        return cur.x.val;
    }
    int rightSz = merge(st[(p << 1) + 1], cur).x.ct;
    if (rightSz >= k) return query((p << 1) + 1, (i+j)/2+1, j, k, cur);
    return query((p << 1), i, (i+j)/2, k, merge(st[(p << 1) + 1], cur));
}

int main() {
    setupIO();

    int n; cin >> n;
    map<ll, int> skillMap;
    ii A[n]; F0R(i, n) cin >> A[i].pA >> A[i].pB;
    sort(A, A+n, [](const ii &x, const ii &y) {
        return x.pB < y.pB;
    });
    F0R(i, n) {
        skillMap[A[i].pB] = i;
    }
    sort(A, A+n);

    int t; cin >> t;
    pair<ii, int> B[t];
    F0R(i, t) {
        int a, b; cin >> a >> b;
        B[i] = mp(mp(a, b), i);
    }
    sort(B, B+t);

    int aIdx = 0;
    ll ans[t];
    F0R(i, t) {
        int a = B[i].pA.pA, k = B[i].pA.pB;
        while (aIdx < n && A[aIdx].pA <= a) {
            // add aIdx
            update(1, 0, n-1, skillMap[A[aIdx].pB], A[aIdx].pB);
            aIdx++;
        }

        ans[B[i].pB] = query(1, 0, n-1, k, node{});
    }
    F0R(i, t) {
        cout << ans[i] << '\n';
    }

    return 0;
}