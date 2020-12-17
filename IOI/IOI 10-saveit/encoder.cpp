/*
 * Same solution as editorial
 *
 * Make a random spanning tree. Note that the distance of a node is either the same as the distance
 * of its parent, or its larger than the distance of its parent by one, or its smaller than the
 * distance of its parent by one.
 *
 * Encode the tree, the root node distance, and the three posssible options
 *
 * Also see decoder.cpp
 */

#include "grader.h"
#include "encoder.h"

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define F0R(i, n) for (int i = 0; i < n; ++i)
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define pb push_back
#define inf 1000000010
#define ii pair<int, int>
#define f first
#define s second
#define mp make_pair

void sendNum(int x) {
    assert(x <= 1023);
    F0R(i, 10) {
        if (x&(1<<i)) encode_bit(1);
        else encode_bit(0);
    }
}

vector<int> adj[1000];
int pa[1000];
int dist[36][1000];

void dfs(int u, int p) {
    pa[u] = p;
    for (int v : adj[u]) {
        if (pa[v] == -1) dfs(v, u);
    }
}

ll curNum = 0;
int curSz = 0;
ll curMult = 1;

// 59 bits can represent 37 nodes

void flushCodes() {
    if (curSz > 0) {
        F0R(i, 59) {
            if (curNum & (1LL << i)) encode_bit(1);
            else encode_bit(0);
        }
        curNum = 0;
        curSz = 0;
        curMult = 1;
    }
}

void sendCode(int x) {
    if (curSz == 37) flushCodes();
    assert(0 <= x && x <= 2);
    curNum += curMult*x;
    curMult *= 3;
    curSz++;
}

void encode(int n, int h, int e, int *v1, int *v2){
    F0R(i, e) {
        adj[v1[i]].pb(v2[i]);
        adj[v2[i]].pb(v1[i]);
    }
    F0R(i, n) pa[i] = -1;

    dfs(0, 0);

    FOR(i, 1, n) {
        sendNum(pa[i]);
    }

    F0R(i, 36) {
        F0R(j, n) dist[i][j] = inf;
        dist[i][i] = 0;
        queue<int> q; q.push(i);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (dist[i][v] == inf) {
                    dist[i][v] = dist[i][u]+1;
                    q.push(v);
                }
            }
        }
    }

    F0R(i, h) {
        sendNum(dist[i][0]);
        FOR(j, 1, n) {
            int p = pa[j];
            if (dist[i][j] == dist[i][p]) {
                sendCode(0);
            } else if (dist[i][j] == dist[i][p]+1) {
                sendCode(1);
            } else if (dist[i][j] == dist[i][p]-1) {
                sendCode(2);
            } else {
                cout << i << " " << j << " " << p << endl;
                cout << dist[i][j] << " " << dist[i][p] << endl;
                cerr << "??" << endl;
                exit(1);
            }
        }
        flushCodes();
    }

    return;
}
