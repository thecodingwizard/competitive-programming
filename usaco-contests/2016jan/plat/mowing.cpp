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

using namespace std;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define SORT(vec) sort(vec.begin(), vec.end())

#define INF 1000000010
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define pb push_back
#define PI acos(-1.0)
#define ll long long
#define MOD (int)(2e+9+11)
#define SET(vec, val, size) for (int i = 0; i < size; i++) vec[i] = val;
#define SET2D(arr, val, dim1, dim2) F0R(i, dim1) F0R(j, dim2) arr[i][j] = val;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vl;

#define MAXN (1<<17)
#define MAXV (1<<30)

struct Node {
    int val;
    Node* left;
    Node* right;

    Node() {
        val = 0;
        left = right = NULL;
    }

    Node* getLeft() {
        if (!left) left = new Node;
        return left;
    }

    Node* getRight() {
        if (!right) right = new Node;
        return right;
    }

    void add(int x, int v, int lo, int hi) {
        val += v;
        if (hi - lo == 1) return;
        int mid = (lo + hi)/2;
        if (mid <= x) {
            getRight()->add(x, v, mid, hi);
        } else {
            getLeft()->add(x, v, lo, mid);
        }
    }

    int query(int a, int b, int lo, int hi) {
        if (a <= lo && b >= hi) return val;
        else if (hi <= a || b <= lo) return 0;
        int mid = (lo + hi)/2;
        return (left ? left->query(a, b, lo, mid) : 0) + (right ? right->query(a, b, mid, hi) : 0);
    }
};

Node BIT[MAXN];

void bit_add(int idx, int y, int val) {
    for (; idx < MAXN; idx += LSOne(idx)) {
        BIT[idx].add(y, val, 0, MAXV);
    }
}

int bit_query(int y0, int y1, int idx) {
    int sum = 0;
    for (; idx; idx -= LSOne(idx)) {
        sum += BIT[idx].query(y0, y1, 0, MAXV);
    }
    return sum;
}

int main() {
    freopen("mowing.in", "r", stdin);
    freopen("mowing.out", "w", stdout);

    int n, t; cin >> n >> t;
    ii locations[n]; F0R(i, n) cin >> locations[i].A >> locations[i].B;

    vector<pair<ii, ii>> events, queries;
    F0R(i, n-1) {
        ii p0 = locations[i], p1 = locations[i+1];
        if (p0 > p1) swap(p0, p1);
        if (p0.B == p1.B) {
            // horizontal line
            events.push_back(mp(mp(p0.A+1, p0.B), mp(1, i+1)));
            events.push_back(mp(p1, mp(-1, i+1)));
        } else {
            // vert query line
            queries.push_back(mp(p0, mp(p1.B, i+1)));
        }
    }
    SORT(events); SORT(queries);

    int evIdx = 0;
    int ans = 0;
    for (pair<ii, ii> q : queries) {
        int x = q.A.A;
        for (; evIdx < events.size() && events[evIdx].A.A <= x; evIdx++) {
            bit_add(events[evIdx].B.B, events[evIdx].A.B, events[evIdx].B.A);
        }
        int lo = q.A.B, hi = q.B.A, t1 = q.B.B - t, t2 = q.B.B + t;
        // t or more after this
        if (t2 < MAXN) {
            ans += bit_query(lo + 1, hi, MAXN-1);
            ans -= bit_query(lo + 1, hi, t2);
        }
        // t or more before this
        if (t1 > 0) {
            ans += bit_query(lo + 1, hi, t1);
        }
    }
    cout << ans << endl;

    return 0;
}
