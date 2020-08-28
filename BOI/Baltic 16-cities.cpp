/*
 * Steiner Trees: https://www.youtube.com/watch?v=BG4vAoV5kWw
 *
 * My code baaaarely pased in the time limit, which is pretty generous :O
 */

#include <bits/stdc++.h>
using namespace std;

#define ii pair<int, int>
#define f first
#define s second
#define inf 100000000000010
#define ll long long
#define li pair<ll, int>

int main() {
    cin.tie(0); ios_base::sync_with_stdio(0);
    int n, k, m; cin >> n >> k >> m;
    vector<int> A(k); for (int &x : A) { cin >> x; --x; }
    vector<vector<ii>> adj(n);
    for (int i = 0; i < m; i++) {
        int a, b, w; cin >> a >> b >> w; --a; --b;
        adj[a].push_back(make_pair(b, w));
        adj[b].push_back(make_pair(a, w));
    }
    ll cost[k][n];
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) cost[i][j] = inf;
        cost[i][A[i]] = 0;
        priority_queue<li, vector<li>, greater<li>> pq; pq.push(make_pair(0, A[i]));
        while (!pq.empty()) {
            li u = pq.top(); pq.pop();
            if (cost[i][u.s] < u.f) continue;
            for (ii v : adj[u.s]) {
                if (cost[i][v.f] > u.f + v.s) {
                    cost[i][v.f] = u.f + v.s;
                    pq.push(make_pair(u.f+v.s, v.f));
                }
            }
        }
    }
    ll dist[n][(1 << k)];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (1 << k); j++) {
            dist[i][j] = inf;
        }
    }
    priority_queue<pair<ll, ii>, vector<pair<ll, ii>>, greater<pair<ll, ii>>> pq;
    for (int i = 0; i < k; i++) {
        dist[A[i]][(1 << i)] = 0;
        pq.push(make_pair(0, make_pair(A[i], (1 << i))));
    }
    while (!pq.empty()) {
        pair<ll, ii> top = pq.top(); pq.pop();
        ii u = top.s;
        if (dist[u.f][u.s] < top.f) continue;

        for (ii v : adj[u.f]) {
            ii nxt = make_pair(v.f, u.s);
            ll d = dist[u.f][u.s] + v.s;
            if (dist[nxt.f][nxt.s] > d) {
                dist[nxt.f][nxt.s] = d;
                pq.push(make_pair(d, nxt));
            }
        }

        for (int i = 0; i < k; i++) {
            ii nxt = make_pair(u.f, u.s|(1 << i));
            ll d = dist[u.f][u.s] + cost[i][u.f];
            if (dist[nxt.f][nxt.s] > d) {
                dist[nxt.f][nxt.s] = d;
                pq.push(make_pair(d, nxt));
            }
        }
    }
    ll best = inf;
    int msk = (1 << k) - 1;
    for (int i = 0; i < n; i++) {
        best = min(best, dist[i][msk]);
    }
    cout << best << endl;

    return 0;
}
