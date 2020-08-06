/*
 * dp[i][j] = min cost if k = i and e = j.
 * dp[i][j] = min(dp(i-1, j+1) + single(i), dp(i-2, j) + double(i), dp(i - i/2, j-1) + half(i))
 *
 * Note that dp(i) depends on i-1, i-2, and i/2. We have limited memory, so let's not store the values we don't need.
 *
 * In particular, for a given i, we will store dp(i) and dp(i-1).
 * We will start from dp(1) and calculate dp(2), dp(3), etc.
 *
 * We want to be able to "increment" a dp value: dp(1) ==> dp(2), etc.
 * To get dp(i+1), we need dp(i) and dp(i-1) (which we have). We also need dp(i+1 - (i+1)/2); we'll store this too.
 *
 * If i = 12 for example, we want to store:
 * dp(12), dp(6), dp(3), dp(2), dp(1)
 *
 * Now let's try to increment dp(12) to dp(13).
 * dp(13) relies on dp(12) and dp(11), which is stored in dp(12).
 *
 * It also relies on dp(7), which we don't have. Therefore, we increment dp(6) to become dp(7).
 *
 * Solve recursively: dp(7) needs dp(6) and dp(5), which we have from dp(6).
 * It also needs dp(4), so we need to increment dp(3).
 *
 * dp(3) needs dp(2) and dp(1), which is stored in dp(3).
 *
 * It also needs dp(2), which we already have, so we don't increment anything.
 */


#include <bits/stdc++.h>

using namespace std;

#include "ckuclib.h"

#define ll long long
#define ii pair<ll, ll>
#define f first
#define s second

int cur[30][25];
ii storage[30][25];

void solve(int idx, int nrg, int tgt) {
    if (cur[idx][nrg] == tgt) return;
    assert(cur[idx][nrg] == tgt-1);
    if (!(cur[idx][min(nrg+1, 22)] == tgt-1 || cur[idx][min(nrg+1, 22)] == tgt)) {
        solve(idx, min(nrg+1, 22), tgt-1);
    }

    if (tgt == 1) {
        storage[idx][nrg] = make_pair(jedno(1), 0);
        cur[idx][nrg] = 1;
        return;
    }
    ll newVal = min(storage[idx][nrg].s + dwa(tgt), (cur[idx][min(nrg+1, 22)] == tgt-1 ? storage[idx][min(nrg+1, 22)].f : storage[idx][min(nrg+1, 22)].s) + jedno(tgt));
    ll nextVal = tgt - tgt/2;
    if (nrg > 0) {
        solve(idx+1, nrg-1, nextVal);
        newVal = min(newVal, storage[idx+1][nrg-1].f + polowa(tgt));
    }
    storage[idx][nrg].s = storage[idx][nrg].f;
    storage[idx][nrg].f = newVal;

    cur[idx][nrg] = tgt;
}

int main() {
    int n = dajn(), e = min(daje(), 22);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= 22; j++) {
            solve(0, j, i);
            if (i == dajn() && j == e) {
                odpowiedz(storage[0][j].f);
            }
        }
    }

    return 0;
}
