/*
 * Same solution as editorial.
 *
 * To see where a human can move, construct a tree where all the children of
 * a node is larger than the node. Therefore, we can just walk up the tree for
 * a given start node as long as the node we're going to is greater than equal to L[i].
 * The nodes we can reach are the subtree of our final node.
 *
 * To construct the tree for the human, iterate from largest to smallest node,
 * unioning nodes with their neighbors as long as the neighbor is larger than the
 * node we're currently processing. For each component, keep track of its smallest
 * node.
 *
 * Every time we union two components, put the larger of the two smallest nodes as the
 * child of the smaller of the two smallest nodes.
 */

#include <bits/stdc++.h>
#include "werewolf.h"
using namespace std;

#define pi pair<int, int>
#define f first
#define s second
#define mp make_pair
#define pb push_back

vector<int> adj[200000];
vector<int> adj2[200000];
int smallIdx[200000];
int smallStart[200000];
int smallEnd[200000];
int largeIdx[200000];
int largeStart[200000];
int largeEnd[200000];
int pa[200000];
int parSmall[200000][20];
int parLarge[200000][20];
int sz[200000];
int smallest[200000];
int largest[200000];
int numPoints[200000];

int ctr = 0;
void dfs(int u, int *idx, int *start, int *end) {
    start[u] = ctr;
    for (int v : adj2[u]) {
        dfs(v, idx, start, end);
    }
    end[u] = ctr;
    idx[u] = ctr++;
}

int get(int x) { return x == pa[x] ? x : pa[x] = get(pa[x]); }
void unite(int a, int b) {
    a = get(a), b = get(b);
    if (a == b) return;
    if (sz[a] > sz[b]) swap(a, b);
    pa[a] = b;
    sz[b] += sz[a];
    if (smallest[b] > smallest[a]) {
        // put b as child of a
        adj2[smallest[a]].pb(smallest[b]);
        parSmall[smallest[b]][0] = smallest[a];
    } else {
        adj2[smallest[b]].pb(smallest[a]);
        parSmall[smallest[a]][0] = smallest[b];
    }
    smallest[b] = min(smallest[b], smallest[a]);
}
void unite2(int a, int b) {
    a = get(a), b = get(b);
    if (a == b) return;
    if (sz[a] > sz[b]) swap(a, b);
    pa[a] = b;
    sz[b] += sz[a];
    if (largest[b] < largest[a]) {
        // put b as child of a
        adj2[largest[a]].pb(largest[b]);
        parLarge[largest[b]][0] = largest[a];
    } else {
        adj2[largest[b]].pb(largest[a]);
        parLarge[largest[a]][0] = largest[b];
    }
    largest[b] = max(largest[b], largest[a]);
}

int ft[200001];
int qry(int x) {
    x++;
    int s = 0;
    while (x) {
        s += ft[x];
        x -= x & -x;
    }
    return s;
}
void upd(int k, int v) {
    k++;
    while (k <= 200000) {
        ft[k] += v;
        k += k&-k;
    }
}

// first two are [y1, y2]. second.f = index. second.s = multiplier.
vector<pair<pair<int, int>, pair<int, int>>> queries[200000];
vector<int> points[200000];

vector<int> check_validity(int n, vector<int> X, vector<int> Y,
                                vector<int> S, vector<int> E,
                                vector<int> L, vector<int> R) {
    for (int i = 0; i < (int)X.size(); i++) {
        adj[X[i]].push_back(Y[i]);
        adj[Y[i]].push_back(X[i]);
    }

    for (int i = 0; i < n; i++) {
        pa[i] = i;
        sz[i] = 1;
        smallest[i] = i;
    }

    for (int i = n-1; ~i; i--) {
        for (int v : adj[i]) {
            if (v > i) {
                unite(v, i);
            }
        }
    }

    ctr = 0;
    dfs(0, smallIdx, smallStart, smallEnd);
    parSmall[0][0] = 0;

    for (int i = 1; i < 20; i++) {
        for (int j = 0; j < n; j++) {
            parSmall[j][i] = parSmall[parSmall[j][i-1]][i-1];
        }
    }

    for (int i = 0; i < n; i++) {
        pa[i] = i;
        sz[i] = 1;
        largest[i] = i;
        adj2[i].clear();
    }

    for (int i = 0; i < n; i++) {
        for (int v : adj[i]) {
            if (v < i) {
                unite2(v, i);
            }
        }
    }

    ctr = 0;
    dfs(n-1, largeIdx, largeStart, largeEnd);
    parLarge[n-1][0] = n-1;

    for (int i = 1; i < 20; i++) {
        for (int j = 0; j < n; j++) {
            parLarge[j][i] = parLarge[parLarge[j][i-1]][i-1];
        }
    }

    vector<int> A(S.size(), 0);

    for (int i = 0; i < n; i++) {
        points[smallIdx[i]].pb(i);
    }

    for (int i = 0; i < (int)S.size(); i++) {
        int u = S[i];
        for (int j = 19; ~j; j--) {
            if (parSmall[u][j] >= L[i]) {
                u = parSmall[u][j];
            }
        }
        int smallLeft = smallStart[u], smallRight = smallEnd[u];

        u = E[i];
        for (int j = 19; ~j; j--) {
            if (parLarge[u][j] <= R[i]) {
                u = parLarge[u][j];
            }
        }
        int largeLeft = largeStart[u], largeRight = largeEnd[u];

        queries[smallRight].pb(mp(mp(largeLeft, largeRight), mp(i, 1)));
        if (smallLeft - 1 >= 0)
            queries[smallLeft - 1].pb(mp(mp(largeLeft, largeRight), mp(i, -1)));

        /*
        for (int j = 0; j < n; j++) {
            if (largeLeft <= largeIdx[j] && largeIdx[j] <= largeRight) {
                if (smallLeft <= smallIdx[j] && smallIdx[j] <= smallRight) {
                    A[i] = 1;
                }
            }
        }
        */
    }

    for (int i = 0; i < n; i++) {
        for (int p : points[i]) {
            upd(largeIdx[p], 1);
        }
        for (auto q : queries[i]) {
            numPoints[q.s.f] += q.s.s*(qry(q.f.s)-qry(q.f.f-1));
        }
    }

    for (int i = 0; i < (int)S.size(); i++) {
        A[i] = numPoints[i] > 0;
    }

    return A;
}
