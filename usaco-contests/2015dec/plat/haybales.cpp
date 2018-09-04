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

#define DONE 0
class MinSegmentTree {
private: vl st, lazy, A;
    int n;
    int left (int p) { return p << 1; }
    int right(int p) { return (p << 1) + 1; }

    void build(int p, int L, int R) {
        if (L == R)
            st[p] = A[L];
        else {
            build(left(p) , L              , (L + R) / 2);
            build(right(p), (L + R) / 2 + 1, R          );
            ll p1 = st[left(p)], p2 = st[right(p)];
            st[p] = min(p1, p2);
        } }

    ll rmq(int p, int L, int R, int i, int j) {
        if (lazy[p] != DONE) {
            st[p] += lazy[p];

            if (L != R) {
                lazy[left(p)] += lazy[p];
                lazy[right(p)] += lazy[p];
            }

            lazy[p] = DONE;
        }

        if (i >  R || j <  L) return INF;
        if (L >= i && R <= j) return st[p];

        ll p1 = rmq(left(p) , L              , (L+R) / 2, i, j);
        ll p2 = rmq(right(p), (L+R) / 2 + 1, R          , i, j);

        if (p1 == -1) return p2;
        if (p2 == -1) return p1;
        return min(p1, p2); }

    ll update_point(int p, int L, int R, int idx, int new_value) {
        int i = idx, j = idx;

        if (i > R || j < L)
            return st[p];

        if (L == i && R == j) {
            A[i] = new_value;
            return st[p] = L;
        }

        ll p1, p2;
        p1 = update_point(left(p) , L              , (L + R) / 2, idx, new_value);
        p2 = update_point(right(p), (L + R) / 2 + 1, R          , idx, new_value);

        return st[p] = (A[p1] <= A[p2]) ? p1 : p2;
    }

    ll update_range(int p, int L, int R, int i, int j, int val) {
        if (lazy[p] != DONE) {
            st[p] += lazy[p];

            if (L != R) {
                lazy[left(p)] += lazy[p];
                lazy[right(p)] += lazy[p];
            }

            lazy[p] = DONE;
        }

        if (L > R || L > j || R < i) return st[p];

        if (L >= i && R <= j) {
            st[p] += val;

            if (L != R) {
                lazy[left(p)] += val;
                lazy[right(p)] += val;
            }

            return st[p];
        }

        ll p1, p2;
        p1 = update_range(left(p) , L              , (L + R) / 2, i, j, val);
        p2 = update_range(right(p), (L + R) / 2 + 1, R          , i, j, val);

        return st[p] = min(p1, p2);
    }

public:
    MinSegmentTree(const vl &_A) {
        A = _A; n = (int)A.size();
        st.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
        build(1, 0, n - 1);
    }

    ll rmq(int i, int j) { return rmq(1, 0, n - 1, i, j); }

    ll update_point(int idx, int new_value) {
        return update_point(1, 0, n - 1, idx, new_value); }

    // note: adds val to all elements within range
    //       does not override elements
    ll update_range(int start, int end, int val) {
        return update_range(1, 0, n - 1, start, end, val); }
};

class SumSegmentTree {
private: vl st, lazy, A;
    int n;
    int left (int p) { return p << 1; }
    int right(int p) { return (p << 1) + 1; }

    void build(int p, int L, int R) {
        if (L == R)
            st[p] = A[L];
        else {
            build(left(p) , L              , (L + R) / 2);
            build(right(p), (L + R) / 2 + 1, R          );
            ll p1 = st[left(p)], p2 = st[right(p)];
            st[p] = p1 + p2;
        } }

    ll rmq(int p, int L, int R, int i, int j) {
        if (lazy[p] != DONE) {
            st[p] += lazy[p]*(R-L+1);

            if (L != R) {
                lazy[left(p)] += lazy[p];
                lazy[right(p)] += lazy[p];
            }

            lazy[p] = DONE;
        }

        if (i >  R || j <  L) return 0;
        if (L >= i && R <= j) return st[p];

        ll p1 = rmq(left(p) , L              , (L+R) / 2, i, j);
        ll p2 = rmq(right(p), (L+R) / 2 + 1, R          , i, j);

        return p1+p2; }

    ll update_range(int p, int L, int R, int i, int j, ll val) {
        if (lazy[p] != DONE) {
            st[p] += lazy[p]*(R-L+1);

            if (L != R) {
                lazy[left(p)] += lazy[p];
                lazy[right(p)] += lazy[p];
            }

            lazy[p] = DONE;
        }

        if (L > R || L > j || R < i) return st[p];

        if (L >= i && R <= j) {
            st[p] += val*(R-L+1);

            if (L != R) {
                lazy[left(p)] += val;
                lazy[right(p)] += val;
            }

            return st[p];
        }

        ll p1, p2;
        p1 = update_range(left(p) , L              , (L + R) / 2, i, j, val);
        p2 = update_range(right(p), (L + R) / 2 + 1, R          , i, j, val);

        return st[p] = p1 + p2;
    }

public:
    SumSegmentTree(const vl &_A) {
        A = _A; n = (int)A.size();
        st.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
        build(1, 0, n - 1);
    }

    ll rmq(int i, int j) { return rmq(1, 0, n - 1, i, j); }

    // note: adds val to all elements within range
    //       does not override elements
    ll update_range(int start, int end, int val) {
        return update_range(1, 0, n - 1, start, end, val); }
};

int main() {
    freopen("haybales.in", "r", stdin);
    freopen("haybales.out", "w", stdout);

    int n, q;
    cin >> n >> q;
    vl cows;
    F0R(i, n) {
        ll x; cin >> x;
        cows.push_back(x);
    }
    MinSegmentTree MinST(cows);
    SumSegmentTree SumST(cows);

    F0R(i, q) {
        char c; cin >> c;
        if (c == 'M') {
            int a, b; cin >> a >> b;
            --a; --b;
            cout << MinST.rmq(a, b) << endl;
        } else if (c == 'P') {
            int a, b, x; cin >> a >> b >> x;
            --a; --b;
            MinST.update_range(a, b, x);
            SumST.update_range(a, b, x);
        } else if (c == 'S') {
            int a, b; cin >> a >> b;
            --a; --b;
            cout << SumST.rmq(a, b) << endl;
        }
    }

    return 0;
}
