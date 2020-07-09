/*
 * Calculate the prefix sum array. We want to use exactly n^2 queries while maximizing
 * the size of each query. If we process the prefix sum array in reverse (starting from n,n and ending
 * at 1,1) then it turns out we can calculate the prefix sum array in n^2 queries
 * where each query is at least n/2 by n/2.
 */

#include <bits/stdc++.h>
#include "treasure.h"
using namespace std;

void findTreasure (int n) {
    int ps[n+1][n+1];
    int m = (n+1)/2;
    for (int i = 0; i <= n; i++) for (int j = 0; j <= n; j++) ps[i][j] = 0;
    for (int i = n; i >= 1; i--) {
        for (int j = n; j >= 1; j--) {
            if (i>=m&&j>=m) {
                ps[i][j] = countTreasure(1, 1, i, j);
            } else if (i >= m) {
                ps[i][j] = ps[i][n] - countTreasure(1, j+1, i, n);
            } else if (j >= m) {
                ps[i][j] = ps[n][j] - countTreasure(i+1, 1, n, j);
            } else {
                ps[i][j] = ps[i][n] + ps[n][j] + countTreasure(i+1, j+1, n, n) - ps[n][n];
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (ps[i][j] - ps[i-1][j] - ps[i][j-1] + ps[i-1][j-1] == 1) Report(i, j);
        }
    }
}
