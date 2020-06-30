/*
 * Same solution as koosaga: https://github.com/koosaga/olympiad/blob/master/Balkan/balkan17_city.cpp
 *
 * Basically, maintain a priority queue where each node stores the original city,
 * the target node, and the attraction of the original city minus the distance to the target node.
 *
 * If we always take the node with the greatest attraction from the priority queue,
 * then we can update all adjacent nodes to that node. If the adjacent node
 * does not yet have a "next city" assigned, then we know the next city
 * that the hero will visit for that node will be the original city in the
 * node we are currently processing (assuming the original city is not the adjacent node).
 *
 * If the adjacent node already has a "next city" assigned and the adjacent node
 * is not equal to the original city, then we don't update the next city value.
 * However, we still push it into the priority queue, because we may need to update
 * the next city for the next city of the adjacent node.
 *
 * It may be more clear just to read the code...
 */

#include <bits/stdc++.h>

using namespace std;

struct node {
    int u, d, originalCity;
    bool operator<(const node &other) const {
        return d == other.d ? originalCity > other.originalCity : d < other.d;
    }
};

int main() {
    int n; long long k; cin >> n >> k;
    priority_queue<node> pq;
    vector<int> adj[n];
    int vis[n];
    int nxt[n][2];
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        pq.push({i, x, i});
        vis[i] = 0;
        nxt[i][0] = -1;
    }
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b; --a; --b;
        adj[a].push_back(b); adj[b].push_back(a);
    }

    while (!pq.empty()) {
        node u = pq.top(); pq.pop();
        for (int v : adj[u.u]) {
            if (v == u.originalCity || nxt[v][0] == u.originalCity) continue;
            if (nxt[v][0] == -1) {
                nxt[v][0] = u.originalCity;
            } else if (!vis[v]) {
                vis[v] = true;
            } else {
                continue;
            }
            pq.push({ v, u.d-1, u.originalCity });
        }
    }

    int x = (k&1) > 0 ? nxt[0][0] : 0;
    for (int i = 1; i < 60; i++) {
        for (int j = 0; j < n; j++) {
            nxt[j][i%2] = nxt[nxt[j][(i-1)%2]][(i-1)%2];
        }
        if ((1LL << i)&k) {
            x = nxt[x][i%2];
        }
    }

    cout << x+1 << endl;

    return 0;
}
