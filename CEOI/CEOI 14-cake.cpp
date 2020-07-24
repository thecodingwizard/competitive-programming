/*
 * see https://github.com/stefdasca/CompetitiveProgramming/blob/master/CEOI/CEOI%2014-cake.cpp
 *
 * Can use max seg tree to solve this problem; find max element between i and a (including i),
 * then binary search for the position of the first element on the opposite side of a that is
 * greater than the max element
 */

#include <bits/stdc++.h>

using namespace std;

struct SegTree {
    int n;
    vector<int> st;
    void init(int _n) {
        n = _n;
        st.assign(4*n, 0);
    }
    void upd(int p, int i, int j, int k, int v) {
        if (k < i || k > j) return;
        if (i == j) {
            st[p] = v;
        } else {
            upd(p << 1, i, (i+j)/2, k, v);
            upd((p << 1) + 1, (i+j)/2+1, j, k, v);
            st[p] = max(st[p*2],st[p*2+1]);
        }
    }
    void upd(int p, int v) {
        upd(1, 0, n-1, p, v);
    }
    int qry(int p, int i, int j, int L, int R) {
        if (R < i || L > j) return 0;
        if (L <= i && j <= R) return st[p];
        return max(qry(p << 1, i, (i+j)/2, L, R), qry((2*p+1), (i+j)/2+1, j, L, R));
    }
    int qry(int i, int j) {
        return qry(1, 0, n-1, i, j);
    }
    int qry2(int p, int i, int j, int mx) {
        if (i == j) {
            if (st[p] > mx) return i;
            return -1;
        }
        if (st[p] <= mx) return -1;
        if (st[p*2] > mx) return qry2(p << 1, i, (i+j)/2, mx);
        return qry2(p*2+1, (i+j)/2+1, j, mx);
    }
    int qry2(int mx) {
        int res = qry2(1, 0, n-1, mx);
        assert(res != -1);
        return res;
    }
} lft, rht;

int main() {
    cin.tie(0); ios_base::sync_with_stdio(0);

    int n, a; cin >> n >> a; --a;
    int A[n];
    int loc[11]; for (int i = 1; i <= 10; i++) loc[i] = -1;
    lft.init(a+1); rht.init(n-a);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        if (A[i] >= n-9) {
            loc[n+1-A[i]] = i;
        }
        if (i < a) {
            lft.upd(a-1-i, A[i]);
        } else if (i > a) {
            rht.upd(i-a-1, A[i]);
        }
    }
    lft.upd(a, 1e9);
    rht.upd(n-a-1, 1e9);
    int idx = n+1;
    int q; cin >> q;
    for (int qi = 0; qi < q; qi++) {
        char c; cin >> c;
        if (c == 'E') {
            int i, e; cin >> i >> e; --i;

            for (int x = 10; x >= 1; x--) {
                if (loc[x] == i) {
                    for (int y = x; y <= 9; y++) {
                        loc[y] = loc[y+1];
                    }
                    break;
                }
            }

            for (int x = 9; x >= e; x--) {
                loc[x+1] = loc[x];
            }
            loc[e] = i;
            for (int x = 10; x >= 1; x--) {
                int l = loc[x];
                if (l == -1) continue;
                if (l < a) lft.upd(a-1-l, idx++);
                else if (l > a) rht.upd(l-a-1, idx++);
                A[l] = idx-1;
            }
        } else {
            int b; cin >> b; --b;
            if (b == a) cout << 0 << "\n";
            else {
                if (b < a) {
                    int mx = lft.qry(0,a-1-b);
                    int idx = rht.qry2(mx);
                    cout << a-b+idx << "\n";
                } else {
                    int mx = rht.qry(0,b-a-1);
                    int idx = lft.qry2(mx);
                    cout << b-a+idx << "\n";
                }
            }
        }
    }
    return 0;
}
