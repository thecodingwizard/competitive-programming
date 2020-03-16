/*
 * Submask DP
 */

#include <bits/stdc++.h>

#define pb push_back
#define ll long long
#define vi vector<ll>
#define INF 4500000000000000000LL

using namespace std;

int m, n, t, k;
vector<vi> students;
vector<vi> guests;
ll val[15][(1 << 15)]; // val[i][j] = group i of students goes to tables in mask j, how much do they make?
ll dp[16][(1 << 15)]; // dp[i][j] = groups [0...i) have gone, mask j tables available, max value so far

void solve() {
    cin >> m >> n >> t;
    students.clear();
    for (int i = 0; i < m; i++) {
        vi s;
        for (int j = 0; j < n; j++) {
            int x; cin >> x;
            s.push_back(x);
        }
        students.push_back(s);
    }
    guests.clear();
    for (int i = 0; i < t; i++) {
        int x; cin >> x;
        vi g;
        for (int j = 0; j < x; j++) {
            int y; cin >> y;
            g.pb(y);
        }
        guests.pb(g);
    }
    cin >> k;

    for (int i = 0; i < m; i++) {
        vi stuff2;
        for (int j = 0; j < n; j++) {
            for (int a = 0; a < k; a++) {
                stuff2.pb(students[i][j]);
            }
        }
        sort(stuff2.begin(), stuff2.end());
        for (int j = 0; j < (1 << t); j++) {
            vi stuff;
            for (int a = 0; a < t; a++) {
                if ((1 << a) & j) {
                    for (int g : guests[a]) stuff.pb(g);
                }
            }
            sort(stuff.begin(), stuff.end());
            if (stuff2.size() < stuff.size()) {
                val[i][j] = -INF;
            } else {
                val[i][j] = 0;
                for (int a = 0; a < stuff.size(); a++) {
                    val[i][j] += stuff[stuff.size()-1-a]*stuff2[stuff2.size()-1-a];
                }
            }
        }
    }

    for (int j = 0; j <= m; j++) {
        for (int i = 0; i < (1 << t); i++) {
            dp[j][i] = -INF;
        }
    }

    dp[0][(1 << t) - 1] = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < (1 << t); j++) {
            if (dp[i][j] == -INF) continue;
            for (int s = j; s; s = (s-1)&j) {
                dp[i+1][j^s] = max(dp[i+1][j^s], dp[i][j] + val[i][s]);
            }
            dp[i+1][j] = max(dp[i+1][j], dp[i][j]);
        }
    }

    ll best = -1;
    if (best < dp[m][0]) best = dp[m][0];

    cout << best << endl;
}

int main() {

    int t; cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }

    return 0;
}