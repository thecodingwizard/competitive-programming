// 5 min code, 3 min debug (ish)

#include <bits/stdc++.h>

using namespace std;

#define ii pair<int, int>
#define f first
#define s second

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    int v, e, s; cin >> v >> e >> s; --s;
    vector<ii> adj[v];
    for (int i = 0; i < e; i++) {
        int a, b, w; cin >> a >> b >> w; --a; --b;
        adj[a].push_back(make_pair(b, w));
        adj[b].push_back(make_pair(a, w));
    }

    int dist[v];
    for (int i = 0; i < v; i++) {
        dist[i] = -1;
    }

    dist[s] = 0;
    priority_queue<ii, vector<ii>, greater<ii>> pq;
    pq.push(make_pair(0, s));
    while (!pq.empty()) {
        ii u = pq.top(); pq.pop();
        if (u.f != dist[u.s]) continue;
        for (ii v : adj[u.s]) {
            if (dist[v.f] == -1 || dist[v.f] > dist[u.s] + v.s) {
                dist[v.f] = dist[u.s] + v.s;
                pq.push(make_pair(dist[v.f], v.f));
            }
        }
    }

    for (int i = 0; i < v; i++) {
        cout << dist[i] << endl;
    }

    return 0;
}
