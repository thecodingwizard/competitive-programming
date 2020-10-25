/*
 * For the first subtask, we can simulate.
 *
 * For the second subtask, first note that if a party has < 5% of the votes then
 * they can get 0 votes, so there's only 20 parties we need to consider.
 *
 * For each party, binary search on the number of votes they will get. Then,
 * run dp[i][j] = how many votes needed for parties [i...n] to get collectively
 * j seats; this takes O(n*m*m) time.
 */

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define ii pair<int, int>
#define f first
#define s second
#define mp make_pair

bool comp(pair<ii, int> a, pair<ii, int> b) {
    if (a.f.f*b.f.s == a.f.s*b.f.f) {
        return a.s < b.s;
    }
    return a.f.f*b.f.s < a.f.s*b.f.f;
}

vector<int> A;
int v, n, m; 

// returns # of votes needed for party i to get # seats
// assuming tgtIdx party must get at most tgtSeats seats
int cost(int i, ll seats, int tgtIdx, int tgtSeats) {
    if (i == tgtIdx) {
        return seats == 0 ? 0 : 1e9;
    }
    ll needed = (seats*A[tgtIdx]+tgtSeats)/(tgtSeats+1);
    if (needed != 0 && needed*(tgtSeats+1)%A[tgtIdx]==0 && i >= tgtIdx) needed++;
    if (needed != 0) needed = max(needed, (v+19)/20LL);
    //cout << "cost for " << i << " to get " << seats << " seats w/ tgt " << tgtIdx << ", " << tgtSeats << " is: " << needed << endl;
    return max(needed-A[i], 0LL);
}

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);
    cin >> v >> n >> m;

    int leftover = v;
    A.resize(n); for (auto &x : A) {cin >> x; leftover -= x;}
    
    int a1[n];
    for (int i = 0; i < n; i++) {
        //cout << i << endl;
        priority_queue<pair<ii, int>, vector<pair<ii, int>>, decltype(&comp)> pq(comp);
        int votes[n];
        for (int j = 0; j < n; j++) {
            votes[j] = 0;
            int vo = i == j ? A[i]+leftover : A[j];
            if (20*vo >= v) pq.push(mp(mp(vo, 1), -j));
        }
        for (int j = 0; j < m; j++) {
            pair<ii, int> u = pq.top(); pq.pop();
            //cout << u.f.f << "/" << u.f.s << " " << u.s << endl;
            votes[-u.s]++;
            pq.push(mp(mp(-u.s == i ? A[-u.s]+leftover : A[-u.s],votes[-u.s]+1), u.s));
        }
        a1[i] = votes[i];
    }

    int a2[n];
    for (int i = 0; i < n; i++) {
        if (A[i]*20 < v) {
            a2[i] = 0;
            continue;
        }

        int lo = 0, hi = m; a2[i] = m;
        while (lo < hi) {
            int tgt = (lo+hi)/2;
            ll dp[n+1][m+1];
            for (int j = 0; j <= n; j++) for (int k = 0; k <= m; k++) dp[j][k] = j == 0 && k == 0 ? 0 : 1e9;
            for (int j = 0; j < n; j++) {
                for (int k = 0; k <= m-tgt; k++) {
                    for (int l = 0; l + k <= m-tgt; l++) {
                        dp[j+1][k+l] = min(dp[j+1][k+l], dp[j][k] + cost(j, l, i, tgt));
                    }
                }
            }
            if (dp[n][m-tgt] <= leftover) {
                a2[i] = tgt;
                hi = tgt;
            } else {
                lo = tgt + 1;
            }
        }
    }

    for (int i = 0; i < n; i++) cout << a1[i] << " \n"[i==n-1];
    for (int i = 0; i < n; i++) cout << a2[i] << " \n"[i==n-1];

    return 0;
}
