#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define ii pair<int, int>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define inf 1000000010

struct segtree {
    int n;
    vector<int> st;
    void init(int _n) {
        n = _n;
        st.assign(4*n, -inf);
    }
    int qry(int p, int i, int j, int L, int R) {
        if (i > R || j < L) return -inf;
        if (L <= i && j <= R) return st[p];
        return max(qry(p*2, i, (i+j)/2, L, R), qry(p*2+1, (i+j)/2+1, j, L, R));
    }
    void upd(int p, int i, int j, int k, int v) {
        if (i > k || j < k) return;
        if (i == k && j == k) {
            st[p] = v;
        } else {
            upd(p*2, i, (i+j)/2, k, v);
            upd(p*2+1, (i+j)/2+1, j, k, v);
            st[p] = max(st[p*2], st[p*2+1]);
        }
    }
} before, before2;
struct segtree2 {
    int n;
    vector<int> st;
    void init(int _n) {
        n = _n;
        st.assign(4*n, -inf);
    }
    int qry(int p, int i, int j, int maxValue) {
        if (st[p] <= maxValue) return j-i+1;
        if (i == j) return 0;
        if (st[p*2] < maxValue) {
            return qry(p*2, i, (i+j)/2, maxValue) + qry(p*2+1, (i+j)/2+1, j, maxValue);
        }
        return qry(p*2, i, (i+j)/2, maxValue);
    }
    void upd(int p, int i, int j, int k, int v) {
        if (i > k || j < k) return;
        if (i == k && j == k) {
            st[p] = v;
        } else {
            upd(p*2, i, (i+j)/2, k, v);
            upd(p*2+1, (i+j)/2+1, j, k, v);
            st[p] = max(st[p*2], st[p*2+1]);
        }
    }
} after;
struct segtree3 {
    int n;
    vector<int> st;
    void init(int _n) {
        n = _n;
        st.assign(4*n, -inf);
    }
    int qry(int p, int i, int j, int maxValue) {
        if (st[p] <= maxValue) return j-i+1;
        if (i == j) return 0;
        if (st[p*2+1] < maxValue) {
            return qry(p*2, i, (i+j)/2, maxValue) + qry(p*2+1, (i+j)/2+1, j, maxValue);
        }
        return qry(p*2+1, (i+j)/2+1, j, maxValue);
    }
    void upd(int p, int i, int j, int k, int v) {
        if (i > k || j < k) return;
        if (i == k && j == k) {
            st[p] = v;
        } else {
            upd(p*2, i, (i+j)/2, k, v);
            upd(p*2+1, (i+j)/2+1, j, k, v);
            st[p] = max(st[p*2], st[p*2+1]);
        }
    }
} after2;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, a; cin >> n >> a;
    assert(a != 1 && a != n);
    before.init(a);
    after.init(n-a);
    before2.init(n-a);
    after2.init(a);
    vector<int> A;
    // 1 = 1st, 10 = 10th
    vector<int> topTen; topTen.resize(11);
    F0R(i, n) {
        int x; cin >> x;
        A.pb(x);
        if (i < a-1) {
            before.upd(1, 0, a-1, i, x);
            after2.upd(1, 0, a-1, i, x);
        } else if (i >= a) {
            after.upd(1, 0, n-a-1, i-a, x);
            before2.upd(1, 0, n-a-1, i-a, x);
        }
        if (x >= n-9) {
            topTen[10-(x-(n-9))] = i;
        }
    }

    int nextD = n+1;
    int q; cin >> q;
    F0R(i, q) {
        char c; cin >> c;
        if (c == 'F') {
            int b; cin >> b; --b;
            if (b == a-1) {
                cout << 0 << endl;
            } else {
                if (b > a-1) {
                    int maxVal = before2.qry(1, 0, n-a-1, 0, b-a);
                    int onTheLeft = after2.qry(1, 0, a-1, maxVal);
                    cout << onTheLeft + b-a << endl;
                } else {
                    int maxVal = before.qry(1, 0, a-1, b, a-2);
                    int onTheRight = after.qry(1, 0, n-a-1, maxVal);
                    cout << onTheRight + a-b-1 << endl;
                }
            }
        } else {
            int i, e; cin >> i >> e;
            for (int start = 10; start >= 1; start--) {
                if (topTen[start] == i-1) {
                    for (int nxt = start; nxt <= 9; nxt++) {
                        topTen[nxt] = topTen[nxt+1];
                    }
                    break;
                }
            }
            for (int start = 10; start > e; start--) topTen[start] = topTen[start-1];
            topTen[e] = i-1;
            for (int start = e; start >= 1; start--) {
                int i = topTen[start];
                int x = nextD++;
                if (i < a-1) {
                    before.upd(1, 0, a-1, i, x);
                    after2.upd(1, 0, a-1, i, x);
                } else if (i >= a) {
                    after.upd(1, 0, n-a-1, i-a, x);
                    before2.upd(1, 0, n-a-1, i-a, x);
                }
            }
        }
    }

    return 0;
}
