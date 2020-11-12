/*
 * http://blog.brucemerry.org.za/2013/07
 *
 * For two rows { X, Y }, we will calculate the 2d array cost[i][j] = cost to
 * go from the i'th column of the X'th row to the j'th column of the Y'th row.
 *
 * We can calculate cost for { X, X+1 } in O(c^2) time.
 *
 * Now, note that if we have cost[i][j] for { X, Y } and { Y, Z }, then it's
 * possible to calculate cost[i][j] for { X, Z } in O(c^2) time.
 *
 * Naively, cost2[i][j] = min(costXY[i][k] + costYZ[k][j]) which takes O(c^3).
 *
 * However, note that the optimal paths should never interesect:
 * if p[i][j] = the optimal k for cost2[i][j], note that:
 * p[i][j-1] <= p[i][j] <= p[i+1][j].
 *
 * This property allows us to use Knuth's optimization, where we process dp values
 * in increasing order of j-i, and we keep track of p[i][j].
 *
 * This allows us to solve the static problem in O(nc^2), but we need to handle updates.
 * To do this, we can use a segment tree, where each node in the segment tree
 * covers a certain range, and the node stores cost[i][j] = cost to go from i'th column
 * of the first row in the range to the j'th column of the last row in the range
 * (depending on implementation, it might be the last+1 row).
 *
 * We can merge two nodes in O(c^2) using the above method.
 *
 * However, we don't have quite enough memory to fit the entire seg tree. Therefore,
 * as a final optimization, we set the minimum range of a segment tree to be 10,
 * which greatly decreases the number of nodes we have to store. We just
 * brute force calculate each "minimum range" in O(10 * c^2).
 */

#include <bits/stdc++.h>
#include "wombats.h"

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

int n, c;
int BLOCK = 10;
int H[5000][200], V[5000][200];
int psH[5001][200];

int st[(1 << 11)][200][200];

// Merges A with B, storing the result in C
void merge(int A[200][200], int B[200][200], int C[200][200]) {
    int p[200][200];
    F0R(i, c) F0R(j, c) C[i][j] = inf;
    for (int len = -c; len <= c; len++) {
        F0R(i, c) {
            int j = i + len;
            if (j >= 0 && j < c) {
                int lowerBound = j-1>=0?p[i][j-1]:0, upperBound = i+1<c?p[i+1][j]:c-1;
                for (int tgt = lowerBound; tgt <= upperBound; tgt++) {
                    if (C[i][j] >= A[i][tgt] + B[tgt][j]) {
                        C[i][j] = A[i][tgt] + B[tgt][j];
                        p[i][j] = tgt;
                    }
                }
            }
        }
    }
}

void build(int p, int i, int j) {
    if (j - i + 1 <= BLOCK) {
        FOR(rowIdx, i, j+1) {
            int x[200][200], y[200][200], z[200][200];
            F0R(idx, c) {
                F0R(idx2, c) {
                    x[idx][idx2] = abs(psH[rowIdx][idx2]-psH[rowIdx][idx])+V[rowIdx][idx2];
                    y[idx][idx2] = abs(psH[rowIdx+1][idx2]-psH[rowIdx+1][idx]);
                }
            }
            merge(x, y, z);
            int tmp[200][200];
            if (rowIdx == i) {
                F0R(a, c) F0R(b, c) tmp[a][b] = z[a][b];
            } else {
                merge(st[p], z, tmp);
            }
            F0R(a, c) F0R(b, c) st[p][a][b] = tmp[a][b];
        }
        return;
    }
    build(p*2, i, (i+j)/2);
    build(p*2+1, (i+j)/2+1, j);
    merge(st[p*2], st[p*2+1], st[p]);
}

void upd(int p, int i, int j, int k) {
    if (k > j+1 || k < i) return;
    if (j - i + 1 <= BLOCK && i <= k && k <= j+1) {
        build(p, i, j);
        return;
    }
    upd(p*2, i, (i+j)/2, k);
    upd(p*2+1, (i+j)/2+1, j, k);
    merge(st[p*2], st[p*2+1], st[p]);
}

void init(int R, int C, int _H[5000][200], int _V[5000][200]) {
    n = R; c = C; F0R(i, R) F0R(j, C) { H[i][j] = _H[i][j]; V[i][j] = _V[i][j]; }
    F0R(i, n) F0R(j, c) psH[i][j] = j == 0 ? 0 : psH[i][j-1] + H[i][j-1];
    build(1, 0, n-2);
}

void changeH(int P, int Q, int W) {
    H[P][Q] = W;
    F0R(j, c) psH[P][j] = j == 0 ? 0 : psH[P][j-1] + H[P][j-1];
    upd(1, 0, n-2, P);
}

void changeV(int P, int Q, int W) {
    V[P][Q] = W;
    upd(1, 0, n-2, P);
}

int escape(int V1, int V2) {
    return st[1][V1][V2];
}
