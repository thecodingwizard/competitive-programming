#include <bits/stdc++.h>

using namespace std;

#define ii pair<int, int>
#define f first
#define s second
#define ll long long

const int mod = 998244353;

ii comb(ii a, ii b) {
    return make_pair((ll)a.f*b.f%mod, ((ll)a.s*b.f+b.s)%mod);
}

ii A[200000];
vector<int> adj[200000];
int pa[200000], sz[200000], in[200000], out[200000], root[200000], depth[200000];

struct Seg {
    vector<ii> st;
    int n;
    bool reversed;
    void init(int _n, bool _r) {
        n = _n; reversed = _r;
        st.resize(2*n);
        for (int i = 0; i < n; i++) {
            st[in[i]+n] = A[i];
        }
        for (int i = n-1; i; i--) st[i] = reversed ? comb(st[i<<1|1], st[i<<1]) : comb(st[i<<1], st[i<<1|1]);
    }
    ii qry(int l, int r) {
        // note: function order matters
        ii ra = make_pair(1, 0), rb = make_pair(1, 0);
        for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
            if (l&1) ra = reversed ? comb(st[l++], ra) : comb(ra, st[l++]);
            if (r&1) rb = reversed ? comb(rb, st[--r]) : comb(st[--r], rb);
        }
        return reversed ? comb(rb, ra) : comb(ra, rb);
    }
    void upd(int p, ii v) {
        st[p += n] = v;
        for (p /= 2; p; p /= 2) st[p] = reversed ? comb(st[p*2+1], st[p*2]) : comb(st[p*2], st[p*2+1]);
    }
} st, st2;

void dfs_sz(int u = 0) {
    sz[u] = 1;
    for (auto &v : adj[u]) {
        depth[v] = depth[u]+1;
        pa[v] = u;
        adj[v].erase(find(adj[v].begin(), adj[v].end(),u));
        dfs_sz(v);
        sz[u] += sz[v];
        if (sz[v] > sz[adj[u][0]]) {
            swap(v, adj[u][0]);
        }
    }
}

int ctr = 0;
void dfs_hld(int u = 0) {
    in[u] = ctr++;
    for (auto v : adj[u]) {
        root[v] = (v == adj[u][0] ? root[u] : v);
        dfs_hld(v);
    }
    out[u] = ctr;
}

ii queryPath(int u, int v) {
    ii ra = make_pair(1, 0), rb = make_pair(1, 0);
    bool isReversed = false;
    for (; root[u] != root[v]; v = pa[root[v]]) {
        if (depth[root[u]] > depth[root[v]]) {
            swap(u, v);
            isReversed = !isReversed;
        }
        // cout << isReversed << " " << in[root[v]] << ", " << in[v] << endl;
        if (!isReversed) rb = comb(st.qry(in[root[v]], in[v]), rb); 
        else ra = comb(ra, st2.qry(in[root[v]], in[v]));
    }
    if (depth[u] > depth[v]) {
        swap(u, v);
        isReversed = !isReversed;
    }
    // cout << isReversed << " " << in[u] << ", " << in[v] << endl;
    if (isReversed) rb = comb(st2.qry(in[u], in[v]), rb);
    else ra = comb(ra, st.qry(in[u], in[v]));
    return comb(ra, rb);
}

int main() {
    int n, q; cin >> n >> q;

    for (int i = 0; i < n; i++) {
        cin >> A[i].f >> A[i].s;
    }

    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    depth[0] = 0; pa[0] = 0; root[0] = 0;
    dfs_sz(); dfs_hld();
    st.init(n, false);
    st2.init(n, true);

    for (int i = 0; i < q; i++) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        if (a == 0) {
            st.upd(in[b], make_pair(c, d));
            st2.upd(in[b], make_pair(c, d));
        } else {
            ii res = queryPath(b, c);
            cout << ((ll)d*res.f+res.s)%mod << "\n";
        }
    }

    return 0;
}
