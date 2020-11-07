#include <bits/stdc++.h>
using namespace std;
#include "Boblib.h"

void Bob( int V, int U, int C[], int D[] ){
    if (V == 2 && U == 1) {
        InitMap(1, 0);
        return;
    }
    vector<int> adj[V];
    for (int i = 0; i < U; i++) {
        adj[C[i]].push_back(D[i]);
        adj[D[i]].push_back(C[i]);
    }
    map<int, int> realID;
    int excludeBits = -1;
    for (int i = 0; i < V; i++) {
        if (adj[i].size() == 1) {
            if ((int)adj[adj[i][0]].size() == V-11) {
                assert(excludeBits == -1);
                excludeBits = adj[i][0];
                realID[i] = -1;
            }
        }
    }
    assert(excludeBits != -1);
    set<int> bitNodesSet;
    for (int i = 0; i < V; i++) {
        bitNodesSet.insert(i);
    }
    for (int j : adj[excludeBits]) bitNodesSet.erase(j);
    bitNodesSet.erase(excludeBits);
    assert(bitNodesSet.size() == 10);
    int largestBit = *bitNodesSet.begin();
    for (int x : bitNodesSet) {
        if (adj[largestBit].size() > adj[x].size()) largestBit = x;
    }
    vector<int> bitNodes;
    int cur = largestBit;
    while (cur != -1) {
        bitNodes.push_back(cur);
        int nxt = -1;
        for (int v : adj[cur]) {
            if (bitNodesSet.count(v) && find(bitNodes.begin(), bitNodes.end(), v) == bitNodes.end()) {
                assert(nxt == -1);
                nxt = v;
            }
        }
        cur = nxt;
    }
    assert(bitNodes.size() == 10);
    reverse(bitNodes.begin(), bitNodes.end());
    realID[excludeBits] = -1;
    for (int x : bitNodes) realID[x] = -1;
    for (int i = 0; i < V; i++) {
        if (realID[i] != -1) {
            int v = 0;
            for (int j : adj[i]) {
                auto it = find(bitNodes.begin(), bitNodes.end(), j);
                if (it == bitNodes.end()) continue;
                int val = it - bitNodes.begin();
                v |= (1 << val);
            }
            realID[i] = v-1;
            assert(0 <= v-1 && v-1 < V-12);
        }
    }
    vector<int> realAdj[V-12];
    for (int i = 0; i < V; i++) {
        if (realID[i] != -1) {
            for (int j : adj[i]) {
                if (realID[j] == -1) continue;
                int a = realID[i], b = realID[j];
                if (a < b) {
                    realAdj[a].push_back(b);
                }
            }
        }
    }
    int edgeCt = 0;
    for (int i = 0; i < V-12; i++) edgeCt += realAdj[i].size();
	InitMap( V-12, edgeCt );
    for (int i = 0; i < V-12; i++) {
        for (int j : realAdj[i]) {
            MakeMap(i, j);
        }
    }
}

