/*
 * Note that queries are ONLINE, not offline.
 *
 * Same solution as editorial; use HLD. When adding a bridge from a to b,
 * merge smaller -> larger (so if a's component is smaller than b, then rebuild
 * HLD on a's component and make a a child of b).
 *
 * When queries get too slow (over sqrt(n) steps needed for each query) rebuild
 * the entire HLD for that component.
 *
 * Can use one very big fenwick tree...
 */
#include <bits/stdc++.h>

using namespace std;

struct UnionFind {
    vector<int> pa, sz;
    void init(int n) {
        for (int i = 0; i < n; i++) {
            pa.push_back(i);
            sz.push_back(1);
        }
    }
    int find(int x) {
        return pa[x] == x ? x : pa[x] = find(pa[x]);
    }
    void merge(int a, int b) {
        a = find(a); b = find(b);
        if (sz[a] > sz[b]) swap(a, b);
        pa[a] = b;
        sz[b] += sz[a];
    }
} uf;

const int mxn = 3000000;
struct BIT {
    vector<int> ft;
    void init() {
        ft.assign(mxn, 0);
    }
    int qry(int x) {
        if (x == 0) return 0;
        int sum = 0;
        for (; x; x -= x&-x) sum += ft[x];
        return sum;
    }
    void upd(int x, int v) {
        for (; x <= mxn; x += x&-x) ft[x] += v;
    }
} bit;

int A[30000], root[30000], par[30000], depth[30000], pos[30000], sz[30000];
vector<int> adj[30000];

bool needsRebuild;

template<class BinaryOp>
void processPath(int x, int y, BinaryOp op) {
    int steps = 0;
    for (; root[x] != root[y]; y = par[root[y]]) {
        if (depth[root[x]] > depth[root[y]]) swap(x, y);
        op(pos[root[y]], pos[y]);
        steps++;
    }
    needsRebuild = steps >= 175;
    if (depth[x] > depth[y]) swap(x, y);
    op(pos[x], pos[y]);
}

int ctr;
void dfsSz(int x) {
    sz[x] = 1;
    for (int &y : adj[x]) {
        if (par[x] == y) swap(y, adj[x][adj[x].size()-1]);
    }
    for (int &y : adj[x]) {
        if (par[x] == y) continue;
        par[y] = x; depth[y] = depth[x] + 1;
        dfsSz(y); sz[x] += sz[y];
        if (sz[y] > sz[adj[x][0]]) swap(y, adj[x][0]);
    }
}
void dfsHld(int x, bool fresh = false) {
    if (!fresh) bit.upd(pos[x], -A[x]);
    pos[x] = ctr++;
    assert(ctr < mxn);
    bit.upd(pos[x], A[x]);
    for (int y : adj[x]) {
        if (par[x] == y) continue;
        root[y] = (y == adj[x][0] ? root[x] : y);
        dfsHld(y);
    }
}

// connect a to b
void connect(int a, int b) {
    depth[a] = depth[b] + 1;
    root[a] = a; par[a] = b;
    adj[b].push_back(a);
    adj[a].push_back(b);
    dfsSz(a); dfsHld(a);
    //cout << "merge" << " " << a << " with " << b << endl;
    //for (int i = 0; i < 5; i++) cout << "root[" << i << "] = " << root[i] << endl;
    //for (int i = 0; i < 5; i++) cout << "pos[" << i << "] = " << pos[i] << endl;
}

int queryPath(int x, int y) {
    int res = 0;
    processPath(x, y, [&res](int l, int r) {
        //cout << "qry " << l << " " << r << " " << bit.qry(r) - bit.qry(l-1) << endl;
        res += bit.qry(r) - bit.qry(l-1);
    });
    return res;
}

int main() {
    int n; 
    cin >> n; ctr = n+1;
    uf.init(n);
    bit.init();
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        par[i] = root[i] = i;
        depth[i] = 1;
        pos[i] = i+1;
        bit.upd(i+1, A[i]);
    }

    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        string s; cin >> s;
        if (s == "bridge") {
            int a, b; cin >> a >> b; --a; --b;
            if (uf.find(a) == uf.find(b)) {
                cout << "no" << endl;
            } else {
                if (uf.sz[uf.find(a)] > uf.sz[uf.find(b)]) swap(a, b);
                connect(a, b);
                uf.merge(a, b);
                cout << "yes" << endl;
            }
        } else if (s == "penguins") {
            int a, x; cin >> a >> x; --a;
            bit.upd(pos[a], -A[a]);
            A[a] = x;
            bit.upd(pos[a], A[a]);
        } else {
            int a, b; cin >> a >> b; --a; --b;
            if (uf.find(a) != uf.find(b)) cout << "impossible" << endl;
            else {
                cout << queryPath(a, b) << endl;
            }
            if (needsRebuild) {
                depth[a] = 0, root[a] = a, par[a] = a; dfsSz(a); dfsHld(a);
            }
        }
    }

    return 0;
}
