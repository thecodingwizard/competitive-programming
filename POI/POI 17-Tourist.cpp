#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define ii pair<int, int>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define inf 1000000010

#define maxn 2000

int n; 

bool vis[maxn];
int dfsLow[maxn], dfsNum[maxn], sccNum[maxn];
int sccSize[maxn];
int sccRoot[maxn];
int nextInSCC[maxn];
int prevInSCC[maxn];
bool iToJ[maxn][maxn];
int ctr = 0;
int numSCC = 0;
int S[maxn+10];
int sctr = 0;
vector<int> sccs[maxn];
void tarjan(int u) {
    vis[u] = true;
    dfsLow[u] = dfsNum[u] = ctr++;
    S[sctr++] = u;

    for (int v = 0; v < n; v++) {
        if (!iToJ[u][v]) continue;
        if (dfsNum[v] == -1) {
            tarjan(v);
        }
        if (vis[v]) {
            dfsLow[u] = min(dfsLow[u], dfsLow[v]);
        }
    }

    if (dfsLow[u] == dfsNum[u]) {
        // cerr << "New scc: " << numSCC << endl;
        while (true) {
            int v = S[--sctr]; vis[v] = false;
            sccNum[v] = numSCC;
            sccSize[numSCC]++;
            sccs[numSCC].pb(v);
            // cerr << v << " ";
            if (v == u) break;
        }
        reverse(all(sccs[numSCC]));
        // cerr << endl;
        sccRoot[numSCC] = u;
        ++numSCC;
    }
}

ii opt[maxn];
void dfsScc(int u) {
    if (vis[u]) return; vis[u] = true;
    for (int v = 0; v < numSCC; v++) {
        if (!iToJ[sccRoot[u]][sccRoot[v]]) continue;
        dfsScc(v);
        opt[u] = max(opt[u], mp(opt[v].f + sccSize[v], v));
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j <= i; j++) {
            bool jToI; cin >> jToI;
            iToJ[i+1][j] = !jToI;
            iToJ[j][i+1] = jToI;
        }
    }
    for (int i = 0; i < n; i++) {
        dfsNum[i] = -1;
    }

    // calculate SCC's
    for (int i = 0; i < n; i++) {
        if (dfsNum[i] == -1) {
            tarjan(i);
        }
    }

    for (int i = 0; i < numSCC; i++) {
        int prev = 0;
        prevInSCC[sccs[i][0]] = -1;
        for (int j = 1; j < sz(sccs[i]); j++) {
            if (iToJ[sccs[i][prev]][sccs[i][j]]) {
                nextInSCC[sccs[i][prev]] = sccs[i][j];
                prevInSCC[sccs[i][j]] = sccs[i][prev];
                prev = j;
            } else {
                for (int k = j-1; ~k; k--) {
                    if (iToJ[sccs[i][k]][sccs[i][j]]) {
                        int oldNext = nextInSCC[sccs[i][k]];
                        nextInSCC[sccs[i][k]] = sccs[i][j];
                        prevInSCC[sccs[i][j]] = sccs[i][k];
                        assert(iToJ[sccs[i][j]][oldNext]);
                        nextInSCC[sccs[i][j]] = oldNext;
                        prevInSCC[oldNext] = sccs[i][j];
                        break;
                    }
                }
            }
        }
        // SOMETHING HERE IS TIMING OUT
        prev = sccs[i][prev];
        if (prev != sccs[i][0]) {
            while (!iToJ[prev][sccs[i][0]]) {
            // cerr << prev << " " << nextInSCC[prev] << endl;
                if (prevInSCC[prev] == -1) {
                    // return 0;
                    assert(false);
                }
                int k = prevInSCC[prevInSCC[prev]];
                while (!iToJ[k][prev] || !iToJ[prev][nextInSCC[k]]) {
                    k = prevInSCC[k];
                    if (k == -1) {
                        // return 0;
                        assert(false);
                    }
                }
                assert(iToJ[k][prev]);
                int nextPrev = prevInSCC[prev];
                int oldNext = nextInSCC[k];
                nextInSCC[k] = prev;
                prevInSCC[prev] = k;
                assert(oldNext != prev);
                if (!iToJ[prev][oldNext]) {
                    // return 0;
                    assert(false);
                }
                nextInSCC[prev] = oldNext;
                prevInSCC[oldNext] = prev;
                prev = nextPrev;
                if (prev == -1) {
                    // return 0;
                    assert(false);
                }
            }
            assert(iToJ[prev][sccs[i][0]]);
        }
        nextInSCC[prev] = sccs[i][0];
        prevInSCC[sccs[i][0]] = prev;
    }

    /*
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (sccNum[i] != sccNum[j]) {
                if (iToJ[i][j] != iToJ[sccRoot[sccNum[i]]][j]) {
                    cerr << i << " "<< j << " "<< sccRoot[sccNum[i]] << " " << iToJ[i][j] << " " << iToJ[sccRoot[sccNum[i]]][j] << endl;
                    assert(false);
                }
            }
        }
    }
    */
    
    // for (int i = 0; i < numSCC; i++) {
    //     for (int j = i+1; j < numSCC; j++) {
    //         if (iToJ[sccRoot[i]][sccRoot[j]]) {
    //             sccAdj[i].pb(j);
    //         } else {
    //             sccAdj[j].pb(i);
    //         }
    //     }
    // }

    // for (int i = 0; i < numSCC; i++) {
    //     opt[i] = mp(0, -1);
    //     vis[i] = false;
    // }
    // for (int i = 0; i < numSCC; i++) {
    //     dfsScc(i);
    // }

    // string output;
    // for (int i = 0; i < n; i++) {
    //     output += to_string(opt[sccNum[i]].f+sccSize[sccNum[i]]);
    //     int cur = i;
    //     int iterations = 0;
    //     while (cur != -1) {
    //         output += " " + to_string(cur+1);
    //         // cerr << " " << cur+1;
    //         int node = nextInSCC[cur];
    //         while (node != cur) {
    //             iterations++;
    //             assert(iterations <= n);
    //             output += " " + to_string(node+1);
    //         // cerr << " " << node+1;
    //             node = nextInSCC[node];
    //         }

    //         cur = opt[sccNum[cur]].s;
    //         if (cur != -1) {
    //             cur = sccRoot[cur];
    //         }
    //     }
    //     cerr << endl;
    //     output += "\n";
    // }
    // cout << output;

    return 0;
}
