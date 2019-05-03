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

struct BIT {
    int n = 10010;
    ll tree[10010];

    void update(int idx, ll val) {
        for (; idx < n; idx += LSOne(idx)) {
            tree[idx] += val;
        }
    }

    ll query(int idx) {
        if (idx == 0) return 0;
        ll sum = 0;
        for (; idx > 0; idx -= LSOne(idx)) {
            sum += tree[idx];
        }
        return sum;
    }
};

int n, m; 
int A[10000];
BIT bit[10];

int main() {
    cin >> n >> m;
    F0R(i, n) cin >> A[i];

    F0R(i, m) {
        F0R(j, 10010) bit[i].tree[j] = 0;
    }

    F0R(i, n) {
        bit[A[i] % m].update(i + 1, A[i]);
    }

    int q; cin >> q;
    while (q--) {
        char command; cin >> command;
        if (command == 's') {
            ll l, r, mod; cin >> l >> r >> mod;
            cout << bit[mod].query(r) - bit[mod].query(l - 1) << endl;
        } else if (command == '+') {
            ll p, r; cin >> p >> r;
            bit[A[p - 1] % m].update(p, -A[p - 1]);
            A[p - 1] += r;
            bit[A[p - 1] % m].update(p, A[p - 1]);
            cout << A[p - 1] << endl;
        } else {
            ll p, r; cin >> p >> r;
            bit[A[p - 1] % m].update(p, -A[p - 1]);
            if (A[p - 1] >= r) A[p - 1] -= r;
            bit[A[p - 1] % m].update(p, A[p - 1]);
            cout << A[p - 1] << endl;
        }
    }

    return 0;
}
