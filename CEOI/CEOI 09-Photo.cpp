/*
 * Same solution as editorial
 *
 * You just have to observe that two rectangles will never be partially intersecting,
 * if two rectangles overlap then 
 * the taller one will be entirely contained horizontally by the shorter one.
 *
 * Then we can just do dp[i][j][k] = # of rectangles for the subset of points
 * bounded on the left by point i, on the right by point j, and below by point k
 */

#include <bits/stdc++.h>

using namespace std;

#define ii pair<int, int>
#define f first
#define s second

int n, a; 
int memo[100][100][101];
bool vis[100][100][101];
int top[100][100];
int mx[100][100];
ii A[101];

int dp(int i, int j, int k) {
    int oi = i;
    if (memo[i][j][k] != -1) return memo[i][j][k];
    while (i < n && A[i].s <= A[k].s) i++;
    if (j < i) return memo[oi][j][k] = 0;
    if (i == j) return memo[oi][j][k] = 1;

    int maxY = mx[i][j];
    if (A[maxY].s*(A[j].f-A[i].f) <= a) return memo[oi][j][k] = 1;


    int best = 1e9;
    for (int x = i; x <= j; x++) {
        if (A[x].s <= A[k].s) continue;
        if (top[i][x] == -1) break;

        best = min(best, dp(i, x, top[i][x]) + dp(x+1, j, k) + 1);
    }

    return memo[oi][j][k] = best;
}

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);
    cin >> n >> a;

    for (int i = 0; i < n; i++) cin >> A[i].f >> A[i].s;
    sort(A, A+n);
    A[100].s = -1;

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int t = i; mx[i][j] = i;
            if (A[i].s*(A[j].f-A[i].f) > a) t = -1;
            for (int k = i; k <= j; k++) {
                if (t != -1 && A[k].s > A[t].s && A[k].s*(A[j].f-A[i].f) <= a) t = k;
                if (A[mx[i][j]].s < A[k].s) mx[i][j] = k;
            }
            top[i][j] = t;
        }
    }

    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) for (int k = 0; k <= 100; k++) memo[i][j][k] = -1;

    cout << dp(0, n-1, 100) << "\n";

    return 0;
}
