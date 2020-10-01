/*
 * Recursive DP and binary search to find the next road you're going to turn on.
 *
 * Use a sparse table (https://usaco.guide/gold/tree-euler/#sparse-tables) to do
 * RMQ in O(1).
 */

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define ii pair<int, int>
#define f first
#define s second
#define mp make_pair

int h, w, q; 
int A[50000], B[50000];
int stH[20][50000];
int stW[20][50000];

int rmq(const int st[20][50000], int L, int R) {
    int maxLen = 31 - __builtin_clz(R-L+1);
    return max(st[maxLen][L], st[maxLen][R - (1 << maxLen)+1]);
}

map<pair<int, ii>, ll> memo;
int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};
ll dp(int i, int j, int d) {
    auto memoIdx = mp(i, mp(j, d));
    if (memo.count(memoIdx)) {
        return memo[memoIdx];
    }

    int maxTravel;
    if (d == 0) maxTravel = i;
    else if (d == 1) maxTravel = w-j-1;
    else if (d == 2) maxTravel = h-i-1;
    else if (d == 3) maxTravel = j;

    ll ans = 0;
    int lo = 1, hi = maxTravel+1, mid, k = 0;
    while (lo < hi) {
        mid = (lo + hi)/2;
        int a = i + dx[d]*mid, b = j + dy[d]*mid;
        if (a < 0 || a >= h || b < 0 || b >= w) {
            hi = mid;
            continue;
        }
        if (d == 0 || d == 2) {
            if (rmq(stH, min(i+dx[d], a), max(i+dx[d], a)) > B[j]) {
                k = mid;
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        if (d == 1 || d == 3) {
            if (rmq(stW, min(j+dy[d], b), max(j+dy[d], b)) > A[i]) {
                k = mid;
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
    }

    if (k > 0) {
        ans += k;
        int a = i + dx[d]*k, b = j + dy[d]*k;
        if (d == 0 || d == 2) {
            ans += max(dp(a, b, 1), dp(a, b, 3));
        }
        if (d == 1 || d == 3) {
            ans += max(dp(a, b, 0), dp(a, b, 2));
        }
    } else {
        ans += maxTravel;
    }

    return memo[memoIdx] = ans;
}

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);
    cin >> h >> w >> q;
    for (int i = 0; i < h; i++) cin >> A[i];
    for (int i = 0; i < w; i++) cin >> B[i];

    for (int i = 0; i < h; i++) {
        stH[0][i] = A[i];
    }
    for (int len = 1; len < 20; len++) {
        for (int i = 0; i <= h - (1 << len); i++) {
            stH[len][i] = max(stH[len-1][i], stH[len-1][i + (1<<(len-1))]);
        }
    }
    for (int i = 0; i < w; i++) {
        stW[0][i] = B[i];
    }
    for (int len = 1; len < 20; len++) {
        for (int i = 0; i <= w - (1 << len); i++) {
            stW[len][i] = max(stW[len-1][i], stW[len-1][i + (1<<(len-1))]);
        }
    }

    for (int i = 0; i < q; i++) {
        int s, t; cin >> s >> t; --s; --t;
        ll best = 0;
        for (int j = 0; j < 4; j++) {
            best = max(best, dp(s, t, j));
        }
        cout << best << "\n";
    }

    return 0;
}
