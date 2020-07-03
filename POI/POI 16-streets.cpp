/*
 * Same solution as luciocf: https://github.com/luciocf/Problems/blob/master/POI/POI%202016/streets.cpp
 *
 * Basically, SCC + topo sort, then assign every node a number coorresponding to
 * topological sort. Then, a node u with topo number ord[u] needs to be able to
 * reach every node v with topo number > ord[u]. Also, every node with topo number
 * < ord[u] needs to be able to reach node u.
 *
 * See luciocf's writeup for a more detailed solution :)
 */

#include <bits/stdc++.h>

using namespace std;

vector<int> adj[500000];
int dfsNum[500000], dfsLow[500000];
int dfsNumCtr = 0;
bool vis[500000];
vector<int> S;
int sccNumCtr;
int sccNum[500000];
vector<int> revSCCNum[500000];
vector<int> sccAdj[500000];
int prv[500000], nxt[500000];
int minPrv[500000], maxNxt[500000];

void tarjanSCC(int u) {
    dfsLow[u] = dfsNum[u] = dfsNumCtr++;
    S.push_back(u); vis[u] = true;
    for (int v : adj[u]) {
        if (dfsNum[v] == -1) tarjanSCC(v);
        if (vis[v]) dfsLow[u] = min(dfsLow[u], dfsLow[v]);
    }
    if (dfsLow[u] == dfsNum[u]) {
        sccNumCtr--;
        while (true) {
            int v = S.back(); S.pop_back(); vis[v] = false;
            revSCCNum[sccNumCtr].push_back(v);
            sccNum[v] = sccNumCtr;
            if (v == u) break;
        }
    }
}

int main() {
    int n, m; cin >> n >> m;
    sccNumCtr = n;

    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
    }
    for (int i = 0; i < n; i++) {
        vis[i] = false;
        dfsNum[i] = -1;
        dfsLow[i] = 0;
        prv[i] = -1, nxt[i] = n+10;
    }

    for (int i = 0; i < n; i++) {
        if (dfsNum[i] == -1) {
            tarjanSCC(i);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int v : adj[i]) {
            if (sccNum[i] != sccNum[v]) {
                sccAdj[sccNum[i]].push_back(sccNum[v]);
            }
        }
    }
    for (int i = sccNumCtr; i < n; i++) {
        sort(sccAdj[i].begin(), sccAdj[i].end());
        sccAdj[i].erase(unique(sccAdj[i].begin(), sccAdj[i].end()), sccAdj[i].end());
    }

    for (int i = sccNumCtr; i < n; i++) {
        for (int v : sccAdj[i]) {
            prv[v] = max(prv[v], i);
            nxt[i] = min(nxt[i], v);
        }
    }

    /*
    for (int i = sccNumCtr; i < n; i++) {
        cout << "SCC " << i << endl;
        for (int v : revSCCNum[i]) cout << v << " ";
        cout << endl;
    }

    for (int i = sccNumCtr; i < n; i++) {
        cout << "prv[" << i << "] = " << prv[i] << ", nxt[" << i << "] = " << nxt[i] << endl;
    }
    */

    minPrv[n-1] = prv[n-1];
    for (int i = n-2; i >= sccNumCtr; i--) {
        minPrv[i] = min(minPrv[i+1], prv[i]);
    }

    maxNxt[sccNumCtr] = nxt[sccNumCtr];
    for (int i = sccNumCtr+1; i < n; i++) {
        maxNxt[i] = max(maxNxt[i-1], nxt[i]);
    }

    vector<int> ans;
    for (int i = sccNumCtr; i < n; i++) {
        bool bad = false;
        if (i<n-1&&minPrv[i+1]<i) bad = true;
        if (i>sccNumCtr&&maxNxt[i-1]>i) bad = true;
        if (!bad) {
            for (int v : revSCCNum[i]) ans.push_back(v);
        }
    }

    sort(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for (int v : ans) cout << v+1 << " ";
    cout << endl;

    return 0;
}
