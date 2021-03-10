#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define vi vector<int>
#define pb push_back
#define mp make_pair
#define ii pair<int, int>
#define f first
#define s second
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()

const int inf = 1e9+10;

int main() {
    int t; cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        vector<int> adj[n];
        set<ii> edges;
        F0R(i, m) {
            int a, b; cin >> a >> b;
            --a; --b;
            adj[a].pb(b); adj[b].pb(a);
            edges.insert(mp(min(a, b), max(a, b)));
        }

        vector<int> evenDist(n, inf);
        vector<int> oddDist(n, inf);
        queue<ii> q;
        evenDist[0] = 0; q.push(mp(0, 0));
        while (!q.empty()) {
            ii u = q.front(); q.pop();
            for (int v : adj[u.f]) {
                int newDist = (u.s == 0 ? evenDist[u.f] : oddDist[u.f]) + 1;
                if (newDist % 2 == 1) {
                    if (oddDist[v] == inf) {
                        oddDist[v] = newDist;
                        q.push(mp(v, 1));
                    }
                } else {
                    if (evenDist[v] == inf) {
                        evenDist[v] = newDist;
                        q.push(mp(v, 0));
                    }
                }
            }
        }

        if (oddDist[0] == inf) {
            cout << n-1 << endl;
            continue;
        }

        map<int, int> nodes[2*n+10];
        F0R(i, n) {
            ii x = mp(min(evenDist[i], oddDist[i]), max(evenDist[i], oddDist[i]));
            nodes[x.f+x.s][x.f]++;
            //cout << i << ": " << min(evenDist[i], oddDist[i]) << " " << max(evenDist[i], oddDist[i]) << endl;
        }

        int needed = 0;
        set<ii> exists;

        for (int sum = 0; sum < 2*n+10; sum++) {
            int edgesFromParent = 0;
            int prevNode = -1;
            for (auto nodeSet : nodes[sum]) {
                ii x = mp(nodeSet.f, sum-nodeSet.f);
                int ct = nodeSet.s;
                if (prevNode != x.f-1) {
                    edgesFromParent = 0;
                }
                prevNode = x.f;

                if (!exists.count(mp(x.f-1, x.s-1))) {
                    if (x.f != 0) {
                        needed += max(0, ct - edgesFromParent);
                        if (x.f == x.s-1) {
                            needed += (ct+1)/2;
                        } else {
                            needed += ct;
                            edgesFromParent = ct;
                        }
                    } else {
                        if (x.f == x.s-1) needed++;
                    }
                } else {
                    if (x.f == x.s-1) {
                        int hasParent = min(ct, edgesFromParent);
                        int noParent = max(0, ct - edgesFromParent);
                        needed += noParent;
                        needed += (hasParent+1)/2;
                    } else {
                        needed += ct;
                        edgesFromParent = min(ct, edgesFromParent);
                    }
                }
                exists.insert(x);
            }
        }

        cout << needed << endl;
    }

    return 0;
}
