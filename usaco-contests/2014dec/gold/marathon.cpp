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
#include <math.h>
#include <assert.h>

using namespace std;

#define INF 1000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define PI acos(-1.0)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

class SegmentTree {
private: vi st, A;
    int n;
    int left (int p) { return p << 1; }
    int right(int p) { return (p << 1) + 1; }

    void build(int p, int L, int R) {
        if (L == R)
            st[p] = L;
        else {
            build(left(p) , L              , (L + R) / 2);
            build(right(p), (L + R) / 2 + 1, R          );
            int p1 = st[left(p)], p2 = st[right(p)];
            st[p] = (A[p1] >= A[p2]) ? p1 : p2;
        } }

    int rmq(int p, int L, int R, int i, int j) {
        if (i >  R || j <  L) return -1;
        if (L >= i && R <= j) return st[p];

        int p1 = rmq(left(p) , L              , (L+R) / 2, i, j);
        int p2 = rmq(right(p), (L+R) / 2 + 1, R          , i, j);

        if (p1 == -1) return p2;
        if (p2 == -1) return p1;
        return (A[p1] >= A[p2]) ? p1 : p2; }

    int update_point(int p, int L, int R, int idx, int new_value) {
        int i = idx, j = idx;

        if (i > R || j < L)
            return st[p];

        if (L == i && R == j) {
            A[i] = new_value;
            return st[p] = L;
        }

        int p1, p2;
        p1 = update_point(left(p) , L              , (L + R) / 2, idx, new_value);
        p2 = update_point(right(p), (L + R) / 2 + 1, R          , idx, new_value);

        return st[p] = (A[p1] >= A[p2]) ? p1 : p2;
    }

public:
    SegmentTree(const vi &_A) {
        A = _A; n = (int)A.size();
        st.assign(4 * n, 0);
        build(1, 0, n - 1);
    }

    int rmq(int i, int j) { return rmq(1, 0, n - 1, i, j); }

    int update_point(int idx, int new_value) {
        return update_point(1, 0, n - 1, idx, new_value); }
};

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

int dist(ii a, ii b) {
    return abs(a.A - b.A) + abs(a.B - b.B);
}

int main() {
    freopen("marathon.in", "r", stdin);
    freopen("marathon.out", "w", stdout);

    int n, q; cin >> n >> q;
    ii coords[n];
    for (int i = 0; i < n; i++) cin >> coords[i].A >> coords[i].B;
    vector<int> distances; distances.resize(n);
    for (int i = 1; i < n; i++) {
        distances[i] = dist(coords[i - 1], coords[i]);
    }
    FenwickTree ft(n);
    for (int i = 1; i < n; i++) {
        ft.adjust(i, distances[i]);
    }
    vector<int> gainedByRemoving; gainedByRemoving.resize(n);
    for (int i = 1; i < n - 1; i++) {
        gainedByRemoving[i] = ft.rsq(i, i + 1) - dist(coords[i - 1], coords[i + 1]);
    }
    SegmentTree st(gainedByRemoving);

    for (int i = 0; i < q; i++) {
        char op; cin >> op;
        if (op == 'Q') {
            int a, b; cin >> a >> b; a--; b--;
            cout << ft.rsq(a+1, b) - gainedByRemoving[st.rmq(a + 1, b - 1)] << endl;
        } else {
            int idx, x, y; cin >> idx >> x >> y; idx--;
            coords[idx].A = x; coords[idx].B = y;
            if (idx != 0) {
                ft.adjust(idx, dist(coords[idx - 1], coords[idx]) - distances[idx]);
                distances[idx] = dist(coords[idx - 1], coords[idx]);
            }
            if (idx != n - 1) {
                ft.adjust(idx + 1, dist(coords[idx], coords[idx + 1]) - distances[idx + 1]);
                distances[idx+1] = dist(coords[idx], coords[idx + 1]);
            }

            if (idx != n - 1 && idx != 0) {
                gainedByRemoving[idx] = ft.rsq(idx, idx + 1) - dist(coords[idx - 1], coords[idx + 1]);
                st.update_point(idx, gainedByRemoving[idx]);
            }
            if (idx >= 2) {
                gainedByRemoving[idx - 1] = ft.rsq(idx - 1, idx) - dist(coords[idx - 2], coords[idx]);
                st.update_point(idx - 1, gainedByRemoving[idx - 1]);
            }
            if (idx + 2 < n) {
                gainedByRemoving[idx + 1] = ft.rsq(idx + 1, idx + 2) - dist(coords[idx], coords[idx + 2]);
                st.update_point(idx + 1, gainedByRemoving[idx + 1]);
            }
        }
    }
    return 0;
}