/*
 * N^3 DP[prevStart][prevEnd] is obvious
 *
 * The key is to process the DP in decreasing order of prevEnd; for a given prevEnd we process
 * all prevStart in decreasing order.
 *
 * When processing a given prevEnd, we consider all DP values that start at prevEnd+1.
 * There are two cases to consider:
 * - The next DP state is longer than our current DP state. In this case, our transition value
 *   will be (nextDPValue + nextDPStateLength) - currentDPStateLength
 * - The next DP state is shorter than our current DP state. In this case, our transition value
 *   will be (nextDPValue - nextDPStateLength) + currentDPStateLength
 * We can maintain a multiset (actually it needs to be O(1) but a multiset is easier to think about)
 * of (dpVal + dpStateLen) for all the DP states longer than our current DP state, and another
 * multiset of (dpVal - dpStateLen) for all the DP states shorter than our current DP state.
 * Then we can do the transition in O(log n) time. As prevStart decreases, we will have to move
 * some transitions from the longer multiset to the shorter multiset.
 *
 * Finally, we can optimize out a log factor (the multiset) by using a stack / keeping the minimum.
 */

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define ii pair<int, int>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define inf 1000000010

int len[2000];
int get(int a, int b) {
    return len[b]-(a==0?0:len[a-1]) + (b-a);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int m, n; cin >> m >> n;
    vector<int> A(n);
    F0R(i, n) cin >> A[i];
    len[0] = A[0];
    FOR(i, 1, n) len[i] = len[i-1] + A[i];

    // pair stores <len, dpValue>
    vector<vector<pair<int, int>>> startingAt(n+1);

    for (int end = n-1; ~end; end--) {
        int idx = startingAt[end+1].size()-1;
        // bigger stores dp + dist. ans is bigger - len
        // smaller stores dp - dist. ans is smaller + len
        int bestSmaller = 2*inf;
        stack<int> bestBigger;

        for (auto x : startingAt[end+1]) {
            if (bestBigger.empty() || bestBigger.top() >= x.s+x.f) bestBigger.push(x.s + x.f);
        }

        for (int start = end; ~start; start--) {
            int len = get(start, end);
            if (len > m) break;

            while (idx >= 0 && startingAt[end+1][idx].f <= len) {
                if (bestBigger.top() == startingAt[end+1][idx].f + startingAt[end+1][idx].s)
                    bestBigger.pop();
                if (bestSmaller > startingAt[end+1][idx].s - startingAt[end+1][idx].f)
                    bestSmaller = startingAt[end+1][idx].s - startingAt[end+1][idx].f;
                idx--;
            }

            int opt = 2*inf;
            if (end == n-1) opt = 0;
            if (!bestBigger.empty()) {
                opt = min(opt, bestBigger.top() - len);
            }
            if (bestSmaller != 2*inf) opt = min(opt, bestSmaller + len);

            startingAt[start].pb(mp(len, opt));
        }
    }

    int best = 2*inf;
    for (auto x : startingAt[0]) {
        best = min(best, x.s);
    }

    cout << best << "\n";

    return 0;
}
