/*
 * Greedy solution: First, determine which costly edges must be added to make the graph connected.
 * Then, greedily add new costly edges until it costs k
 * Finally, add back all the free edges. It's guaranteed that it's possible to add free edges
 * to make the graph connected due to our first step.
 *
 * Note that the time limit is EXTREMELY tight so optimize I/O and use \n, not endl!!
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

int ufRank[100000], parent[100000];

int findSet(int i) {
    return (parent[i] == i) ? i : (parent[i] = findSet(parent[i]));
}

bool isSameSet(int i, int j) {
    return findSet(i) == findSet(j);
}

void unionSet(int i, int j) {
    if (isSameSet(i, j)) return;
    int x = findSet(i), y = findSet(j);
    if (ufRank[x] > ufRank[y]) {
        parent[y] = x;
    } else {
        parent[x] = y;
        if (ufRank[x] == ufRank[y]) ufRank[y]++;
    }
}

int main() {
    setupIO("karb");

    int n, m, k; cin >> n >> m >> k;
    vii free, cost;
    F0R(i, m) {
        int a, b, k; cin >> a >> b >> k;
        --a; --b;
        if (k == 0) free.pb(mp(a, b));
        else cost.pb(mp(a, b));
    }

    // Determine which cost edges must be added to make graph connected
    // Add them
    F0R(i, n) {
        ufRank[i] = 0;
        parent[i] = i;
    }
    vii needed, optional, ans;
    for (ii x : free) {
        if (!isSameSet(x.pA, x.pB)) {
            unionSet(x.pA, x.pB);
        }
    }
    for (ii x : cost) {
        if (!isSameSet(x.pA, x.pB)) {
            unionSet(x.pA, x.pB);
            needed.pb(x);
            ans.pb(x);
            k--;
        } else {
            optional.pb(x);
        }
    }

    F0R(i, n) {
        ufRank[i] = 0;
        parent[i] = i;
    }
    for (ii x : needed) unionSet(x.pA, x.pB);

    // Then, greedily add cost edges until k is reached
    for (ii x : optional) {
        if (k == 0) break;
        if (!isSameSet(x.pA, x.pB)) {
            unionSet(x.pA, x.pB);
            ans.pb(x);
            --k;
        }
    }

    // Add the remaining free edges
    for (ii x : free) {
        if (!isSameSet(x.pA, x.pB)) {
            unionSet(x.pA, x.pB);
            ans.pb(x);
        }
    }

    for (ii x : ans) {
        cout << x.pA+1 << " " << x.pB+1 << '\n';
    }

    return 0;
}