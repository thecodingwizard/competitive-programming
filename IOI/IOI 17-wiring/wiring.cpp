/*
 * Benq is too good https://oj.uz/submission/56090
 * Also see editorial + tmw's writeup
 */

#include "wiring.h"
#include <bits/stdc++.h>

using namespace std;

#define ii pair<int,int>
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define all(x) x.begin(), x.end()
#define inf 1000000010

// uh...
#define int long long

set<int> wires[2];
int dp[200000];

int getClosest(int x, int t) {
    auto it = wires[t].lower_bound(x);
    int best = inf;
    if (it != wires[t].end()) {
        best = min(best, *it-x);
    }
    if (it != wires[t].begin()) {
        best = min(best, x-*prev(it));
    }
    return best;
}

long long min_total_length(vector<int32_t> r, vector<int32_t> b) {
    for (int x : r) wires[0].insert(x);
    for (int x : b) wires[1].insert(x);

    vector<ii> A;
    for (int x : r) A.pb(mp(x, 0));
    for (int x : b) A.pb(mp(x, 1));

    sort(all(A));

    int prevBlockIdx = -1;
    int prevBlockSum = 0;
    for (int i = 0; i < (int)A.size(); i++) {
        dp[i] = (i==0?0:dp[i-1]) + getClosest(A[i].f, !A[i].s);

        if (i == 0 || A[i].s != A[i-1].s) {
            prevBlockIdx = i-1;
            prevBlockSum = 0;
        }
        if (prevBlockIdx != -1 && A[prevBlockIdx].s != A[i].s) {
            prevBlockSum += A[i].f - A[prevBlockIdx].f;
            prevBlockIdx--;
            dp[i] = min(dp[i], (prevBlockIdx>=0?dp[prevBlockIdx]:0) + prevBlockSum);
        }
    }

    return dp[A.size()-1];
}
