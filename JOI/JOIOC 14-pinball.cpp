/*
 * define dpLeft[i] = min cost to get everything to the left of device i
 * to fall into device i. Define similarly dpRight[i].
 *
 * process increasing i, so we start from the top and work our way down.
 *
 * If device i extends all the way to the left, then dpLeft[i] = cost[i].
 *
 * Otherwise, for every j < i where target[j] will land in device i,
 * dpLeft[i] = min(dpLeft[i], dpLeft[j] + cost[i]).
 *
 * Similar transition for dpRight[i].
 *
 * Answer = min(dpLeft[i] + dpRight[i]) for all i.
 *
 * We can speed up with seg tree + coord compress
 */

#include <bits/stdc++.h>

using namespace std;

#define ll long long

const ll inf = 1e18;

map<int, int> cc;

struct SegTree {
    vector<ll> st;
    int n;
    void init(int _n) {
        n = _n; st.assign(2*n, inf);
    }
    void upd(int p, ll v) {
        p += n;
        st[p] = min(st[p], v);
        for (p /= 2; p; p /= 2) st[p] = min(st[2*p], st[2*p+1]);
    }
    ll qry(int l, int r) {
        ll a = inf;
        for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
            if (l&1) a = min(a, st[l++]);
            if (r&1) a = min(a, st[--r]);
        }
        return a;
    }
} lft, rht;

int main() {
    int m, n; cin >> m >> n;
    int L[m], R[m], T[m], C[m];
    for (int i = 0; i < m; i++) cin >> L[i] >> R[i] >> T[i] >> C[i];

    vector<int> pts;
    for (int i = 0; i < m; i++) {
        pts.push_back(L[i]);
        pts.push_back(R[i]);
        pts.push_back(T[i]);
    }
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());

    int np = pts.size();
    lft.init(np); rht.init(np);
    for (int i = 0; i < np; i++) {
        cc[pts[i]] = i;
    }

    ll dpLeft[m], dpRight[m];
    for (int i = 0; i < m; i++) {
        dpLeft[i] = dpRight[i] = inf;

        if (L[i] == 1) dpLeft[i] = C[i];
        if (R[i] == n) dpRight[i] = C[i];

        dpLeft[i] = min(dpLeft[i], C[i] + lft.qry(cc[L[i]], cc[R[i]]));
        dpRight[i] = min(dpRight[i], C[i] + rht.qry(cc[L[i]], cc[R[i]]));

        lft.upd(cc[T[i]], dpLeft[i]);
        rht.upd(cc[T[i]], dpRight[i]);
    }

    ll opt = inf;

    for (int i = 0; i < m; i++) {
        opt = min(opt, dpLeft[i] + dpRight[i] - C[i]);
    }

    if (opt == inf) cout << -1 << endl;
    else cout << opt << endl;

    return 0;
}
