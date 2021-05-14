#include <bits/stdc++.h>
#include "citymapping.h"
using namespace std;

using ll = long long;
#define ii pair<int, int>
#define f first
#define s second
#define mp make_pair
#define pb push_back
#define all(x) x.begin(), x.end()

vector<ii> adj[1010];
ll sz[1010];
ii pa[1010];
vector<pair<int, ii>> edges;

ll dfsSize(int u, int a1, int a2) {
    sz[u] = 1;
    for (ii v : adj[u]) {
        if (v.f == a1 || v.f == a2) continue;
        sz[u] += dfsSize(v.f, a1, a2);
    }
    return sz[u];
}

pair<int, ll> getEndpoint(int u, int a1, int a2) {
    int best = -1;
    ll bestDist = 0;
    for (ii v : adj[u]) {
        if (v.f == a1 || v.f == a2) continue;
        if (best == -1 || sz[best] < sz[v.f]) {
            best = v.f;
            bestDist = v.s;
        }
    }
    if (best == -1) return mp(u, 0);
    pair<int, ll> ret = getEndpoint(best, a1, a2);
    ret.s += bestDist;
    return ret;
}

void solve(int root, int avoid, int avoid2, int target, ll rootToTarget) {
    dfsSize(root, avoid, avoid2);
    pair<int, ll> endpoint = getEndpoint(root, avoid, avoid2);
    //cout << root << " " << endpoint.f << endl;
    if (endpoint.f == root) {
        edges.pb(mp(rootToTarget, mp(root, target)));
        adj[root].pb(mp(target, rootToTarget));
        pa[target] = mp(root, rootToTarget);
        //cout << "attaching " << target << " to " << root << " with weight " << rootToTarget << endl;
    } else {
        ll d = (rootToTarget + get_distance(endpoint.f, target) - endpoint.s) / 2;
        int prevNode = -1;
        int node = endpoint.f;
        ll nodeDist = endpoint.s;
        while (nodeDist > rootToTarget - d) {
            assert(pa[node].f != -1);
            nodeDist -= pa[node].s;
            prevNode = node;
            node = pa[node].f;
        }
        assert(nodeDist == rootToTarget - d);
        solve(node, prevNode, avoid, target, d);
    }
}

void find_roads(int N, int Q, int A[], int B[], int W[]) {
    int root = 1;
    pa[1] = mp(-1, -1);

    vector<pair<ll, int>> nodes;
    for (int i = 2; i <= N; i++) {
        nodes.pb(mp(get_distance(root, i), i));
    }
    sort(all(nodes));

    for (pair<ll, int> x : nodes) {
        //cout << "sovling for " << x.s << endl;
        solve(root, -1, -1, x.s, x.f);
    }

    for (int i = 0; i < N-1; i++) {
        A[i] = edges[i].s.f;
        B[i] = edges[i].s.s;
        W[i] = edges[i].f;
    }

	return;
}
