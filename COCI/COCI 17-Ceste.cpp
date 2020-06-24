/*
 * To solve this problem, we can actually just use a modified dijkstra's.
 *
 * We will run dijkstra's on cost, processing nodes in increasing order of cost.
 * However, we will modify it slightly to allow visiting nodes more than once, even
 * if it results in a higher cost. As cost increases, we will expect time to decrease.
 * So, we keep track of the min time processed so far for every node. If, during
 * dijkstra's, we encounter a state where our current time is greater than the minimum
 * time encountered so far, we skip that state, because it is suboptimal (the time
 * is greater than a previous time, and the cost is greater than the cost for that
 * previous time because dijkstra's guarantees we process nodes in increasing cost).
 *
 * Surprisingly, this code runs in time. Another way to imagine this algorithm is
 * that we make each node (cost, time).
 *
 * A similar problem is BOI 11 timeismoney. In that problem, instead of finding SSSP,
 * you are tasked to find a MST. The editorial for that problem is very interesting.
 * Apparently the strategy for that editorial is applicable to this problem as well,
 * though I am unsure if it will pass in time. Regardless, this dijkstra's solution
 * somehow manages to pass in time.
 */

#include <bits/stdc++.h>

using namespace std;

#define ll long long

struct edge {
    int to, time, cost;
};

struct state {
    int id, cost, time;
    bool operator<(const state &other) const {
        return cost == other.cost ? time > other.time : cost > other.cost;
    }
};

int main() {
    int n, m; cin >> n >> m;
    vector<edge> adj[2000];
    for (int i = 0; i < m; i++) {
        int a, b, t, c; cin >> a >> b >> t >> c;
        --a; --b;
        adj[a].push_back({b,t,c});
        adj[b].push_back({a,t,c});
    }

    int minTime[2000]; for (int i = 0; i < n; i++) minTime[i] = 1e9+10;
    ll best[2000]; for (int i = 0; i < n; i++) best[i] = 9e18+10;
    int mx = 2000*2000;

    minTime[0] = best[0] = 0;
    priority_queue<state> pq;
    pq.push({0,0,0});
    while (!pq.empty()) {
        state u = pq.top(); pq.pop();
        if (u.time > minTime[u.id]) continue;
        minTime[u.id] = u.time;
        best[u.id] = min(best[u.id], (ll)u.time*u.cost);
        for (edge v : adj[u.id]) {
            if (u.time + v.time <= mx && u.time + v.time < minTime[v.to]) {
                pq.push({v.to,u.cost+v.cost,u.time+v.time});
            }
        }
    }

    for (int i = 1; i < n; i++) {
        if (best[i] == 9e18+10) cout << -1 << endl;
        else cout << best[i] << endl;
    }

    return 0;
}


