#include <bits/stdc++.h>

using namespace std;

#define ii pair<int, int>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define all(x) x.begin(), x.end()
#define F0R(i, n) for (int i = 0; i < n; i++)
#define inf 1000000010

vector<ii> adj[100000];
int d1[100000], d2[100000];
bool vis[100000];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, k; cin >> n >> m >> k;
    F0R(i, n) d1[i] = d2[i] = inf;
    F0R(i, m) {
        int a, b, l; cin >> a >> b >> l;
        adj[a].pb(mp(b, l));
        adj[b].pb(mp(a, l));
    }
    priority_queue<ii, vector<ii>, greater<ii>> pq;
    for (int i = 0; i < k; i++) {
        int x; cin >> x;
        d1[x] = d2[x] = 0;
        pq.push(mp(0, x));
    }
    while (!pq.empty()) {
        ii u = pq.top(); pq.pop();
        if (vis[u.s]) continue;
        vis[u.s] = true;
        for (auto v : adj[u.s]) {
            int d = d2[u.s] + v.s;
            if (d1[v.f] > d) {
                d2[v.f] = d1[v.f];
                d1[v.f] = d;
            } else if (d2[v.f] > d) {
                d2[v.f] = d;
            } else {
                continue;
            }
            if (d2[v.f] != inf) pq.push(mp(d2[v.f], v.f));
        }
    }
    cout << d2[0] << endl;

    return 0;
}
