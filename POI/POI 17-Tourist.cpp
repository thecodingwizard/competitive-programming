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
vector<int> adj[maxn];
vector<int> sccAdj[maxn];

bool vis[maxn];
int dfsLow[maxn], dfsNum[maxn], sccNum[maxn];
int sccSize[maxn];
int sccRoot[maxn];
int nextInSCC[maxn];
bool iToJ[maxn][maxn];
int ctr = 0;
int numSCC = 0;
vector<int> S;
void tarjan(int u) {
    vis[u] = true;
    dfsLow[u] = dfsNum[u] = ctr++;
    S.pb(u);

    for (int v : adj[u]) {
        if (dfsNum[v] == -1) {
            tarjan(v);
        }
        if (vis[v]) {
            dfsLow[u] = min(dfsLow[u], dfsLow[v]);
        }
    }

    if (dfsLow[u] == dfsNum[u]) {
        //cerr << "New scc: " << numSCC << endl;
        int prev = u;
        while (true) {
            int v = S.back(); S.pop_back(); vis[v] = false;
            sccNum[v] = numSCC;
            sccSize[numSCC]++;
            nextInSCC[v] = prev;
            prev = v;
            //cerr << v << " ";
            if (v == u) break;
        }
        //cerr << endl;
        sccRoot[numSCC] = u;
        ++numSCC;
    }
}

ii opt[maxn];
void dfsScc(int u) {
    if (vis[u]) return;
    for (int v : sccAdj[u]) {
        dfsScc(v);
        opt[u] = max(opt[u], mp(opt[v].f + sccSize[v], v));
    }
}

void printSCC(int node) {
    cout << " " << node+1;
    int cur = nextInSCC[node];
    while (cur != node) {
        cout << " " << cur+1;
        cur = nextInSCC[cur];
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
            if (jToI) {
                adj[j].pb(i+1);
            } else {
                adj[i+1].pb(j);
            }
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
    
    for (int i = 0; i < numSCC; i++) {
        for (int j = i+1; j < numSCC; j++) {
            if (iToJ[i][j]) {
                sccAdj[i].pb(j);
            } else {
                sccAdj[j].pb(i);
            }
        }
    }

    for (int i = 0; i < numSCC; i++) {
        opt[i] = mp(0, -1);
        vis[i] = false;
    }
    for (int i = 0; i < numSCC; i++) {
        dfsScc(i);
    }

    for (int i = 0; i < n; i++) {
        cout << opt[sccNum[i]].f+sccSize[sccNum[i]];
        int cur = i;
        while (cur != -1) {
            printSCC(cur);
            cur = opt[sccNum[cur]].s;
            if (cur != -1) {
                cur = sccRoot[cur];
            }
        }
        cout << "\n";
    }

    return 0;
}
