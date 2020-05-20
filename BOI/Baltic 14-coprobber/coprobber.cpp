/*
 * same solution as editorial
 * 
 * Define police(i, j) = police on i, robber on j, it's police turn.
 * True if police wins, false if robber wins.
 *
 * Define robber(i, j) = police on i, robber on j, it's robber's turn.
 * True if police wins, false if robber wins.
 *
 * police(i, j) = true if i==j or if robber(x, j) is true for
 * ANY x that's connected to i
 *
 * robber(i, j) = true if i==j or if police(i, x) is true for
 * ALL x that's connected to j
 *
 * Normal recursive DP doesn't work because there are cycles, so instead,
 * start from the end "true" states. police(i, i) and robber(i, i) are true
 * for all i. Do a bfs from those states in order to determine which other
 * states are also true.
 *
 * For example, if robber(i, j) is true, then police(x, j) is true for
 * any x connected to i.
 *
 * If police(i, j) is true, then robber(i, x) *might* be true for all x
 * connected to j. We can maintain an array that counts the number of true
 * police(i, j) connected to every robber(x, y). If number equals the degree of y,
 * then no matter where robber moves the police wins, so robber(x, y) is true as well.
 */

#include <bits/stdc++.h>
using namespace std;

#include "coprobber.h"

#define ll long long
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define F0R(i, b) FOR(i, 0, b)
#define ii pair<int, int>
#define pA first
#define pB second

int n;
bool adj[500][500];
int ct[500][500];
int nextStep[500][500];
bool win[500][500];
int adjCt[500];
int curPos = 0;

int start(int N, bool A[MAX_N][MAX_N])
{
    n = N;
    F0R(i, n) {
        adjCt[i] = 0;
        F0R(j, n) {
            adj[i][j] = A[i][j];
            if (A[i][j]) adjCt[i]++;
            ct[i][j] = 0;
        }
    }

    queue<pair<int, ii>> q;
    F0R(i, n) {
        q.push({0,{i,i}});
        q.push({1,{i,i}});
        win[i][i] = true;
    }
    while (!q.empty()) {
        pair<int, ii> u = q.front(); q.pop();
        if (u.pA == 1) {
            // am robber
            F0R(i, n) {
                if (adj[i][u.pB.pA] || i==u.pB.pA) {
                    if (!win[i][u.pB.pB]) {
                        win[i][u.pB.pB] = true;
                        nextStep[i][u.pB.pB] = u.pB.pA;
                        q.push({0,{i,u.pB.pB}});
                    }
                }
            }
        } else {
            // am cop
            F0R(i, n) {
                if (adj[i][u.pB.pB]) {
                    ct[u.pB.pA][i]++;
                    if (ct[u.pB.pA][i] == adjCt[i]) {
                        q.push({1,{u.pB.pA,i}});
                    }
                }
            }
        }
    }
    F0R(i, n) {
        if (!win[0][i]) return -1;
    }

    return 0;
}

int nextMove(int R)
{
    return curPos = nextStep[curPos][R];
}
