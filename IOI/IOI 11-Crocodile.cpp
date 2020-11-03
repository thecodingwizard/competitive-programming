/*
 * Same solution as editorial
 *
 * Run multi-source dijkstra's where the sources are each of the exit nodes
 * For each node, maintain the minimum distance to one exit node and the second minimum distance to another exit node
 * Only add a node to the dijkstra priority queue when its second minimum distance is not infinity
 * Take the node with the minimum second distance from the priority queue each time, then update all its neighboring nodes
 */

#include <bits/stdc++.h>
#include "crocodile.h"

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

int travel_plan(int n, int m, int r[][2], int l[], int k, int p[]) {
    F0R(i, n) d1[i] = d2[i] = inf;
    F0R(i, m) {
        int a = r[i][0], b = r[i][1], L = l[i];
        adj[a].pb(mp(b, L));
        adj[b].pb(mp(a, L));
    }
    priority_queue<ii, vector<ii>, greater<ii>> pq;
    for (int i = 0; i < k; i++) {
        int x = p[i];
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
    return d2[0];
}
