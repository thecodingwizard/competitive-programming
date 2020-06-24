#include <bits/stdc++.h>

using namespace std;

int st[4*200000];
int A[200000];

// p = st[p], the index of the seg tree
// [i, j] is the range covered by st[p]
void build(int p, int i, int j) {
    if (i == j) {
        st[p] = A[i];
        return;
    }
    build((p << 1), i, (i+j)/2);
    build((p << 1) + 1, (i+j)/2+1, j);
    st[p] = min(st[p<<1], st[(p<<1)+1]);
}

// p, i, j is same as build
// We want to update A[k] = v
void upd(int p, int i, int j, int k, int v) {
    // if our current range doesn't cover k, ignore this update
    if (k < i || k > j) return;
    if (i == j) {
        st[p] = v;
        return;
    }
    upd(p << 1, i, (i+j)/2, k, v);
    upd((p << 1) + 1, (i+j)/2+1, j, k, v);
    st[p] = min(st[p<<1], st[(p<<1)+1]);
}

// p, i, j same as build
// L, R is the range, inclusive, that we want to query
int qry(int p, int i, int j, int L, int R) {
    // if the queried range is outside my range, return 0
    if (L > j || R < i) return 1e9+10;
    // if our range is entirely within L, R return st[p]
    if (L <= i && j <= R) return st[p];
    return min(qry(p << 1, i, (i+j)/2, L, R), qry((p << 1) + 1, (i+j)/2+1, j, L, R));
}

int main() {
    int n, q; cin >> n >> q;
    for (int i = 0; i < n; i++) cin >> A[i];

    build(1, 0, n-1);

    for (int i = 0; i < q; i++) {
        int cmd; cin >> cmd;
        if (cmd == 1) {
            int k, u; cin >> k >> u; --k;
            upd(1, 0, n-1, k, u);
        } else {
            int a, b; cin >> a >> b; --a; --b;
            cout << qry(1, 0, n-1, a, b) << endl;
        }
    }

    return 0;
}
