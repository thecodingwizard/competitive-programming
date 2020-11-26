/*
 * https://usaco.guide/solutions/apio-19-bridges
 *
 * Constant factor needs to be optimized... Don't do dumb things...
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

#define BLOCK 1000
#define maxn 100000

int pa[maxn], sz[maxn];
int get(int x) { return pa[x] == x ? x : get(pa[x]); }
vector<ii> ops;
int unite(int a, int b) {
    a = get(a), b = get(b); if (a == b) return 0;
    if (sz[a] > sz[b]) swap(a, b);
    sz[b] += sz[a]; pa[a] = b;
    ops.emplace_back(a, b);
    return 1;
}
void undo() {
    sz[ops.back().s] -= sz[ops.back().f];
    pa[ops.back().f] = ops.back().f;
    ops.pop_back();
}
ii bridge[maxn];
int bridgeWeight[maxn];
int qryAns[maxn];
bool activeBridges[maxn];
vector<int> toUnite[maxn];
vector<pair<int, ii>> commands;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    vector<pair<int, ii>> bridges;
    F0R(i, m) {
        int u, v, d; cin >> u >> v >> d; --u; --v;
        bridge[i] = mp(u, v);
        bridgeWeight[i] = d;
    }

    int q; cin >> q;
    F0R(i, q) {
        int t, a, b; cin >> t >> a >> b;
        --a;
        commands.emplace_back(t, mp(a, b));
    }

    F0R(i, q) qryAns[i] = -1;
    for (int startIdx = 0; startIdx < (int)commands.size(); startIdx += BLOCK) {
        int endIdx = min(startIdx + BLOCK, (int)commands.size());
        vector<int> changedBridges;
        vector<int> queries;
        FOR(i, startIdx, endIdx) {
            if (commands[i].f == 1) {
                activeBridges[commands[i].s.f] = 1;
                changedBridges.pb(commands[i].s.f);
            } else {
                queries.pb(i);
            }
        }
        sort(all(changedBridges));
        changedBridges.erase(unique(all(changedBridges)), changedBridges.end());
        FOR(i, startIdx, endIdx) {
            if (commands[i].f == 1) {
                bridgeWeight[commands[i].s.f] = commands[i].s.s;
            } else {
                for (int x : changedBridges) {
                    if (bridgeWeight[x] >= commands[i].s.s) toUnite[i].pb(x);
                }
            }
        }
        F0R(i, n) { pa[i] = {i}; sz[i] = {1}; }

        vector<int> normalBridges;
        F0R(i, m) {
            if (!activeBridges[i]) {
                normalBridges.pb(i);
            }
        }
        sort(all(normalBridges), [](int l, int r) { return bridgeWeight[l] > bridgeWeight[r]; });
        int bridgeIdx = 0;

        sort(all(queries), [](int l, int r) {
            return commands[l].s.s > commands[r].s.s;
        });
        for (auto qIdx : queries) {
            auto q = mp(mp(commands[qIdx].s.s, commands[qIdx].s.f), qIdx);
            while (bridgeIdx < (int)normalBridges.size() && bridgeWeight[normalBridges[bridgeIdx]] >= q.f.f) {
                unite(bridge[normalBridges[bridgeIdx]].f, bridge[normalBridges[bridgeIdx]].s);
                bridgeIdx++;
            }

            int changes = 0;
            for (int x : toUnite[q.s]) {
                changes += unite(bridge[x].f, bridge[x].s);
            }

            qryAns[q.s] = sz[get(q.f.s)];

            while (changes) {
                undo(); --changes;
            }
        }

        FOR(i, startIdx, endIdx) {
            if (commands[i].f == 1) {
                bridgeWeight[commands[i].s.f] = commands[i].s.s;
                activeBridges[commands[i].s.f] = 0;
            }
        }
    }

    F0R(i, q) if (qryAns[i] != -1) cout << qryAns[i] << "\n";

    return 0;
}
