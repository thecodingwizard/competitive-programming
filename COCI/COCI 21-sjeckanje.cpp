/*
 * https://dmoj.ca/problem/coci20c5p5, click "Read Editorial"
 *
 * For each segment tree node, store the leftmost value, rightmost value,
 * and maximal value assuming the endpoints are increasing or decreasing (four possibilities)
 *
 * For nodes of size one, the endpoints (which are the same number)
 * are either both increasing or both decreasing
 * but can't be both increasing and decreasing
 */

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const ll inf = (1LL << 59);

int n, q; 
vector<ll> A;

const int maxst = 800000;

// 0 = increasing, 1 = decreasing
ll lhs[maxst], rhs[maxst], val[maxst][2][2];

void merge(int p, int i, int j) {
    lhs[p] = lhs[p*2];
    rhs[p] = rhs[p*2+1];

    // two separate things
    for (int a = 0; a < 2; a++) {
        for (int b = 0; b < 2; b++) {
            val[p][a][b] = 0;
            for (int c = 0; c < 2; c++) {
                for (int d = 0; d < 2; d++) {
                    val[p][a][b] = max(val[p][a][b], val[p*2][a][c] + val[p*2+1][d][b]);
                }
            }
        }
    }

    // one continuous increasing in the middle
    if (lhs[p*2+1] > 0) {
        for (int a = 0; a < 2; a++) {
            for (int b = 0; b < 2; b++) {
                val[p][a][b] = max(val[p][a][b], val[p*2][a][0] + val[p*2+1][0][b] + lhs[p*2+1]);
            }
        }
    }

    // one decreasing increasing in the middle
    if (lhs[p*2+1] < 0) {
        for (int a = 0; a < 2; a++) {
            for (int b = 0; b < 2; b++) {
                val[p][a][b] = max(val[p][a][b], val[p*2][a][1] + val[p*2+1][1][b] - lhs[p*2+1]);
            }
        }
    }
}

void build(int p, int i, int j) {
    if (i == j) {
        lhs[p] = A[i];
        rhs[p] = A[i];
        for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++) val[p][i][j] = -inf;
        val[p][0][0] = val[p][1][1] = 0;
    } else {
        build(p*2, i, (i+j)/2);
        build(p*2+1, (i+j)/2+1, j);
        merge(p, i, j);
    }
}

void pans() {
    ll ans = 0;
    for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++) ans = max(ans, val[1][i][j]);
    cout << ans << endl;
}

void upd(int p, int i, int j, int k, int v) {
    if (i > k || j < k) return;
    if (i == j) {
        lhs[p] += v; rhs[p] += v;
    } else {
        upd(p*2, i, (i+j)/2, k, v);
        upd(p*2+1, (i+j)/2+1, j, k, v);
        merge(p, i, j);
    }
}

int main() {
    cin >> n >> q;
    A.resize(n);

    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    for (int i = n-1; ~i; i--) {
        A[i] = A[i] - (i==0?0:A[i-1]);
    }

    build(1, 0, n-1);

    for (int i = 0; i < q; i++) {
        int l, r, x; cin >> l >> r >> x;
        upd(1, 0, n-1, l-1, x);
        if (r < n) upd(1, 0, n-1, r, -x);
        pans();
    }

    return 0;
}
