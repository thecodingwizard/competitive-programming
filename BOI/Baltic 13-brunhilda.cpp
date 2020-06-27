/*
 * Note that it's optimal to always reduce as many people as possible.
 *
 * Define dp[i] = min number of steps to eliminate i children.
 *
 * dp[0] = 0. Then, take the biggest prime number p.
 * dp[1] = dp[2] = ... = dp[p-1] = 1.
 *
 * Then, we want to pick the prime number p that will allow us to expand our
 * dp array the most. In other words, we want to pick the prime number p such
 * that dp[x] is reachable, x % p = 0, and x + p is maximum.
 *
 * We can do this by keeping track of which prime numbers we encounter
 * as we populate the DP array (in my code, it's what the transitions set does).
 */

#include <bits/stdc++.h>

using namespace std;

#define ii pair<int, int>
#define f first
#define s second

int A[100000]; 
int dp[10000001]; 
set<ii> transitions;

int main() {
    int m, q; cin >> m >> q;
    for (int i = 0; i < m; i++) cin >> A[i];
    for (int i = 0; i < 10000001; i++) dp[i] = -1;
    dp[0] = 0;

    int nxtStart = 0, nxtVal = 0;
    for (int i = 0; i < m; i++) {
        nxtVal = max(nxtVal, A[i]);

        transitions.insert({A[i],A[i]});
    }

    while (nxtStart != -1) {
        int begin = nxtStart, end = begin + nxtVal;
        nxtStart = -1;
        nxtVal = 0;

        end = min(end, 10000001);

        while (!transitions.empty() && transitions.begin()->f < end) {
            int x = transitions.begin()->s;
            transitions.erase(transitions.begin());
            int i = (end-1)/x*x;
            if (nxtStart+nxtVal < i + x) {
                nxtStart = i;
                nxtVal = x;
            }
            int nxt = (end-1)/x*x+x;
            if (nxt <= 10000000) transitions.insert({nxt,x});
        }

        for (int i = begin + 1; i < end; i++) {
            if (dp[i] == -1) dp[i] = dp[begin]+1;
        }
    }

    for (int i = 0; i < q; i++) {
        int x; cin >> x;
        if (dp[x] == -1) cout << "oo" << "\n";
        else cout << dp[x] << "\n";
    }

    return 0;
}
