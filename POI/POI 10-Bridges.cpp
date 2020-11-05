/*
 * https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/POI/official/2010/editorial/mos.pdf
 *
 * - Binary search on the maximum edge weight
 * - After removing edges that are too large, we are left with a mix of directed and undirected edges
 * - We essentially have to assign directions to the undirected edges such that it's a valid euler cycle
 * - Since the requirement for valid euler cycle is every node has equal in/out, we can actually solve with max flow:
 *   - Make one node in the max flow graph for every node in the original graph
 *     - connect this node to the source node with an edge weight equal to (degree of node in original graph)/2
 *   - Make one node in the max flow graph for every undirected edge in the original graph
 *     - connect this node to sink node with edge weight 1
 *   - If we're able to traverse from node u to node v, connect node u in the max flow graph to the node representing the edge (u, v)
 *   - Run max flow; if max flow is not = # of edges, no euler cycle
 * - Each unit of "flow" basically represents one outgoing edge from a node
 * - You will need to use dinic's for max flow to run in time
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
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define inf 1000000010

#define maxn 1001
int n, m; 
vector<ii> nodeEdges[maxn];
vector<ii> edges;
vector<int> adj[3*maxn];
int res[3*maxn][3*maxn];
int s = 3000, t = 3001;
int level[3*maxn], start[3*maxn];

int sendFlow(int u, int flow, int t) {
    if (u == t) return flow;
    for (; start[u] < adj[u].size(); start[u]++) {
        int v = adj[u][start[u]];
        if (level[v] == level[u]+1 && res[u][v] > 0) {
            int f = sendFlow(v, min(flow, res[u][v]), t);
            if (f > 0) {
                res[u][v] -= f;
                res[v][u] += f;
                return f;
            }
        }
    }
    return 0;
}

bool can(int maxWeight) {
    F0R(i, n) adj[i].clear();
    int needed = 0;
    F0R(i, n) {
        if (nodeEdges[i].size() % 2 != 0) return false;
        res[s][i] = nodeEdges[i].size()/2;
        adj[s].pb(i);
        needed += res[s][i];
        for (auto e : nodeEdges[i]) {
            if (e.s <= maxWeight) {
                adj[i].pb(1000+e.f);
                adj[1000+e.f].pb(i);
                res[i][e.f+1000] = 1;
                res[e.f+1000][i] = 0;
            }
        }
    }
    F0R(i, m) {
        res[1000+i][t] = 1;
        res[t][1000+i] = 1;
        adj[1000+i].pb(t);
        adj[t].pb(1000+i);
    }
    int mf = 0;
    while (true) {
        F0R(i, 3*maxn) level[i] = -1;
        level[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u == t) break;
            for (int v : adj[u]) {
                if (res[u][v] > 0 && level[v] == -1) {
                    level[v] = level[u]+1;
                    q.push(v);
                }
            }
        }
        if (level[t] >= 0) {
            F0R(i, 3*maxn) start[i] = 0;
            while (int flow = sendFlow(s, inf, t)) mf += flow;
        } else {
            break;
        }
    }
    return mf == needed;
}

vector<ii> newAdj[maxn];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c, d; cin >> a >> b >> c >> d; --a; --b;
        nodeEdges[a].pb(mp(i, c));
        nodeEdges[b].pb(mp(i, d));
        edges.pb(mp(a, b));
    }

    int lo = 1, hi = 1000, mid, ans = -1;
    while (lo <= hi) {
        mid = (lo+hi)/2;
        if (can(mid)) {
            ans = mid;
            hi = mid-1;
        } else {
            lo = mid+1;
        }
    }
    if (ans == -1) return cout << "NIE" << endl, 0;
    cout << ans << endl;
    can(ans);

    F0R(i, n) {
        for (int j : adj[i]) {
            j -= 1000;
            if (res[j+1000][i]) {
                if (i == edges[j].f) {
                    assert(edges[j].s != i);
                    newAdj[i].pb(mp(edges[j].s, j));
                } else {
                    assert(edges[j].s == i);
                    newAdj[i].pb(mp(edges[j].f, j));
                }
            }
        }
    }

    vector<int> S;
    vector<int> S2;
    stack<int> st;
    st.push(0);
    while (!st.empty()) {
        int u = st.top();
        if (newAdj[u].empty()) {
            st.pop();
            if (!S2.empty()) {
                S.pb(S2.back());
                S2.pop_back();
            }
        } else {
            S2.pb(newAdj[u].back().s);
            st.push(newAdj[u].back().f);
            newAdj[u].pop_back();
        }
    }
    reverse(all(S));
    int cur = 0;
    for (int v : S) {
        if (edges[v].f == cur) {
            cur = edges[v].s;
        } else if (edges[v].s == cur) {
            cur = edges[v].f;
        } else {
            assert(false);
        }
        cout << v+1 << " ";
    }
    cout << endl;

    return 0;
}
