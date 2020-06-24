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


