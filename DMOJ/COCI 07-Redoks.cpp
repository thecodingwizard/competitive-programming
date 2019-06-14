/*
 * Lazy seg tree. For each node, store the number of times each digit appears.
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

int n, m;
int A[250000];
struct node {
    int lazy = 0;
    int ct[10];
    int i, j;
    int getSum() {
        int ans = 0;
        F0R(i, 10) ans += ct[i]*i;
        return ans;
    }
    void updLazy() {
        int newCt[10];
        F0R(i, 10) {
            newCt[(i + lazy)%10] = ct[i];
        }
        F0R(i, 10) ct[i] = newCt[i];
    }
};
node st[1000000];

void down(int p) {
    if (st[p].lazy == 0) return;
    st[p].updLazy();
    if (st[p].i != st[p].j) {
        st[(p << 1)].lazy += st[p].lazy;
        st[(p << 1) + 1].lazy += st[p].lazy;
    }
    st[p].lazy = 0;
}

int query(int p, int i, int j, int L, int R) {
    down(p);
    if (i > R || j < L) return 0;
    if (i >= L && j <= R) return st[p].getSum();
    return query((p << 1), i, (i+j)/2, L, R) + query((p << 1) + 1, (i+j)/2+1, j, L, R);
}

void up(int p) {
    down(p << 1); down((p << 1) + 1);
    F0R(i, 10) {
        st[p].ct[i] = st[(p << 1)].ct[i] + st[(p << 1) + 1].ct[i];
    }
}

void build(int p, int i, int j) {
    st[p].i = i; st[p].j = j;
    F0R(i, 10) st[p].ct[i] = 0;
    if (i == j) {
        st[p].ct[A[i]] = 1;
        return;
    }
    build((p << 1), i, (i+j)/2);
    build((p << 1) + 1, (i+j)/2 + 1, j);
    up(p);
}

void update(int p, int i, int j, int L, int R) {
    down(p);
    if (i > R || j < L) return;
    if (i >= L && j <= R) {
        st[p].lazy++;
        return;
    }
    update((p << 1), i, (i+j)/2, L, R);
    update((p << 1) + 1, (i+j)/2 + 1, j, L, R);
    up(p);
}

int main() {
    setupIO();

    cin >> n >> m;
    F0R(i, n) {
        char c; cin >> c;
        A[i] = c - '0';
    }
    build(1, 0, n-1);

    F0R(i, m) {
        int a, b; cin >> a >> b;
        --a; --b;
        cout << query(1, 0, n-1, a, b) << endl;
        update(1, 0, n-1, a, b);
    }

    return 0;
}