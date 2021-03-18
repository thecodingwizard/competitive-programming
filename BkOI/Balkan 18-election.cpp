/*
 * Same solution as editorial
 */

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

#define maxn 500010

int ans[maxn];
int maxPrefix[4*maxn], sum[4*maxn];

// first is sum, second is max prefix
ii qry(int p, int i, int j, int L, int R) {
    if (i > R || j < L) return mp(0, -inf);
    if (L <= i && j <= R) {
        return mp(sum[p], maxPrefix[p]);
    }
    ii lft = qry(p*2, i, (i+j)/2, L, R);
    ii rht = qry(p*2+1, (i+j)/2+1, j, L, R);
    return mp(lft.f + rht.f, max(lft.s, lft.f + rht.s));
}

void upd(int p, int i, int j, int k, int v) {
    if (i > k || j < k) return;
    if (i == j && j == k) {
        maxPrefix[p] = v;
        sum[p] = v;
        return;
    }
    upd(p*2, i, (i+j)/2, k, v);
    upd(p*2+1, (i+j)/2+1, j, k, v);
    maxPrefix[p] = max(maxPrefix[p*2], sum[p*2]+maxPrefix[p*2+1]);
    sum[p] = sum[p*2]+sum[p*2+1];
}

int bit[maxn];

int get(int k) {
    int s = 0;
    while (k) {
        s += bit[k];
        k -= k&-k;
    }
    return s;
}
void add(int k, int v) {
    while (k < maxn) {
        bit[k] += v;
        k += k&-k;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    string s; cin >> s; s = " " + s;

    int q; cin >> q;
    vector<pair<ii, int>> queries;

    F0R(i, q) {
        int l, r; cin >> l >> r;
        queries.pb(mp(mp(l, r), i));
    }
    sort(all(queries), [](pair<ii, int> a, pair<ii, int> b) { return a.f.s < b.f.s; });

    int idx = 0;
    stack<int> removedT;
    for (int i = 1; i <= n; i++) {
        if (s[i] == 'C') {
            upd(1, 1, n, i, -1);
            if (!removedT.empty()) {
                int tgt = removedT.top();
                add(tgt, -1);
                upd(1, 1, n, tgt, 1);
                removedT.pop();
            }
        } else {
            removedT.push(i);
            add(i, 1);
        }
        
        while (idx < q && queries[idx].f.s == i) {
            // process query idx
            int toRemove = get(queries[idx].f.s) - get(queries[idx].f.f-1);

            int extraRemove = qry(1, 1, n, queries[idx].f.f, queries[idx].f.s).s;

            ans[queries[idx].s] = toRemove + max(extraRemove, 0);
            idx++;
        }
    }

    F0R(i, q) cout << ans[i] << endl;

    return 0;
}
