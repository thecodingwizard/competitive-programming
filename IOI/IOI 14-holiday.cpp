/*
 * dp[i] = max amount of attractions you can visit starting from the start location
 *         assuming you can only travel right and you can only take i steps
 *
 * Note that the rightmost location you'll optimally visit is increasing as i increases
 * So we can do a Divide & Conquer DP. We'll need to be able to answer the query
 * "what's the sum of the largest x numbers in the range that we're currently considering
 * in our divide & conquer DP?" the range we consider is [start...rightmostLocation]
 *
 * We can do this with a segtree. Sort all the attractions such that they're nondecreasing.
 * Mark all attractions as "inactive." The segtree returns the sum of the first k "active"
 * numbers.
 * As we do divide & conquer DP, mark relevant locations as "active" so that all the numbers
 * in the range [start...mid] are always activated. Then, calculate the number of
 * actions we have left assuming we travel to a certain rightmost location, and query
 * the segtree to find the number of attractions we can visit.
 *
 * We'll need to compute dp[i] for traveling right without needing to return to the start,
 * traveling right while needing to return to the start, traveling left without needing
 * to return to the start, and traveling left while needing to return to the start.
 *
 * Finally we just brute force all possible arrangements of how many steps we allocate
 * to going left and going right, as well as whether we go left then right or right then left.
 */

#include <bits/stdc++.h>
#include "holiday.h"

using namespace std;
using ll = long long;

#define f first
#define s second
#define ii pair<int, int>
#define pb push_back
#define mp make_pair
#define all(x) x.begin(), x.end()

const int maxn = 100000;
int n, start, d;

int stIndex[maxn];
struct node {
    ll val;
    int initVal;
    int ct;
} st[maxn*4];

void buildST(int attraction[]) {
    vector<ii> attractions;
    for (int i = 0; i < n; i++) {
        attractions.pb(mp(attraction[i], i));
    }
    sort(all(attractions));
    reverse(all(attractions));
    int i = 0;
    for (auto x : attractions) {
        stIndex[x.s] = i;
        i++;
    }
    auto build = [&](int p, int i, int j, const auto &build)->void {
        if (i == j) {
            st[p] = node{0, attractions[i].f, 0};
        } else {
            build(p*2, i, (i+j)/2, build);
            build(p*2+1, (i+j)/2+1, j, build);
            st[p] = node{0,-1,0};
        }
    };
    build(1, 0, n-1, build);
}

void upd(int p, int i, int j, int k, bool isActive) {
    if (i > k || j < k) return;
    if (i == j && i == k) {
        st[p].val = isActive ? st[p].initVal : 0;
        st[p].ct = isActive;
    } else {
        upd(p*2, i, (i+j)/2, k, isActive);
        upd(p*2+1, (i+j)/2+1, j, k, isActive);
        st[p].val = st[p*2].val + st[p*2+1].val;
        st[p].ct = st[p*2].ct + st[p*2+1].ct;
    }
}

ll qry(int p, int i, int j, int k) {
    if (st[p].ct <= k) return st[p].val;
    if (i == j) return k <= 0 ? 0 : st[p].val;
    if (st[p*2].ct >= k) return qry(p*2, i, (i+j)/2, k);
    return st[p*2].val + qry(p*2+1, (i+j)/2+1, j, k - st[p*2].ct);
}

vector<ll> oneWayLeft(3*maxn), oneWayRight(3*maxn);
vector<ll> twoWayLeft(3*maxn), twoWayRight(3*maxn);

void compute(int l, int r, int optl, int optr, vector<ll> &dp, int isTwoWay = 0) {
    if (l > r) return;

    int mid = (l+r)/2;
    ll best = -1; int bestTransition = -1;
    for (int k = optl; k <= optr; k++) {
        upd(1, 0, n-1, stIndex[k], 1);
        int stepsRemaining = mid - (k - start) * (isTwoWay ? 2 : 1);

        ll val = qry(1, 0, n-1, stepsRemaining);
        if (best < val) {
            best = val;
            bestTransition = k;
        }
    }

    dp[mid] = best;

    for (int k = bestTransition+1; k <= optr; k++) {
        upd(1, 0, n-1, stIndex[k], 0);
    }
    compute(mid+1, r, bestTransition, optr, dp, isTwoWay);

    for (int k = optl; k <= bestTransition; k++) {
        upd(1, 0, n-1, stIndex[k], 0);
    }
    compute(l, mid-1, optl, bestTransition, dp, isTwoWay);
}

long long int findMaxAttraction(int N, int Start, int D, int attraction[]) {
    n = N, start = Start, d = D;
    int backup = attraction[start];

    buildST(attraction);
    compute(0, d, start, n-1, oneWayRight);

    attraction[start] = 0;
    reverse(attraction, attraction+N);
    buildST(attraction);
    start = n - start - 1;
    compute(0, d, start, n-1, oneWayLeft);

    reverse(attraction, attraction+N);
    start = n - start - 1;
    attraction[start] = backup;
    buildST(attraction);
    compute(0, d, start, n-1, twoWayRight, 1);

    attraction[start] = 0;
    reverse(attraction, attraction+N);
    start = n - start - 1;
    buildST(attraction);
    compute(0, d, start, n-1, twoWayLeft, 1);

    ll best = 0;
    for (int x = 0; x <= d; x++) {
        best = max(best, max(oneWayRight[x] + twoWayLeft[d-x], twoWayRight[x] + oneWayLeft[d-x]));
    }

    return best;
}

