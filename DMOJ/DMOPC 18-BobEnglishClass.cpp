/*
 * The solution is similar to finding a centroid of a graph, except
 * we are finding the centroid of the graph of the students.
 *
 * Find a node where, if that node were the root, none of its children
 * would have subtrees with more than k/2 students.
 *
 * The answer is the sum of the distances from every student to that node.
 */

#include <bits/stdc++.h>

using namespace std;

#define ii pair<int, int>
#define f first
#define s second
#define ll long long

int k, n; 
int ct[200000];
vector<ii> adj[200000];
int sz[200000];

int dfsSize(int u, int p) {
    sz[u] = ct[u];
    for (auto v : adj[u]) {
        if (v.f != p) sz[u] += dfsSize(v.f, u);
    }
    return sz[u];
}

int findCentroid(int u, int p) {
    for (auto v : adj[u]) {
        if (v.f == p) continue;
        if (sz[v.f] > k/2) {
            return findCentroid(v.f, u);
        }
    }
    return u;
}

ll dfsAns(int u, int p, ll d) {
    ll ans = (ll)ct[u]*d;
    for (auto v : adj[u]) {
        if (v.f != p) {
            ans += dfsAns(v.f, u, d+v.s);
        }
    }
    return ans;
}

int main() {
    cin >> k >> n;
    for (int i = 0; i < n; i++) ct[i] = 0;
    for (int i = 0; i < k; i++) {
        int x; cin >> x;
        ct[x-1]++;
    }

    for (int i = 0; i < n-1; i++) {
        int a, b, w; cin >> a >> b >> w;
        adj[a-1].push_back({b-1,w});
        adj[b-1].push_back({a-1,w});
    }

    dfsSize(0, 0);
    int c = findCentroid(0, 0);

    cout << dfsAns(c, c, 0) << endl;

    return 0;
}
