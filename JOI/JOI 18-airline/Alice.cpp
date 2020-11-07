/*
 * https://ivaniscoding.wordpress.com/2018/08/27/communication-4-airline-route-map
 *
 * oj.uz judge doesn't allow InitG(1, 0) for some reason...
 */

#include <bits/stdc++.h>
using namespace std;
#include "Alicelib.h"

void Alice( int N, int M, int A[], int B[] ){
    if (N == 1 && M == 0) {
        InitG(2, 1);
        MakeG(0, 0, 1);
        return;
    }

    vector<int> adj[N+12];
    for (int i = 0; i < 9; i++) {
        adj[i].push_back(i+1);
    }
    for (int i = 12; i < N+12; i++) {
        adj[11].push_back(i);
        for (int j = 0; j < 10; j++) {
            if ((i-11) & (1 << j)) {
                adj[i].push_back(j);
            }
        }
    }
    for (int i = 0; i < M; i++) {
        adj[A[i]+12].push_back(B[i]+12);
    }
    adj[10].push_back(11); // special identifying node

    int edgeCt = 0;
    for (int i = 0; i < N+12; i++) edgeCt += adj[i].size();
    InitG(N+12, edgeCt);
    int ctr = 0;
    for (int i = 0; i < N+12; i++) {
        for (int j : adj[i]) {
            MakeG(ctr++, i, j);
        }
    }
}

