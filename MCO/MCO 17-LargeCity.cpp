/*
 * Same solution as editorial. Basically do dp[i][j], but compress
 * the dp state: if we have XOOOOXOOOXOX we can represent as a list
 * of ranges of O's. Then, we can skip over empty rows.
 */

#include <bits/stdc++.h>

using namespace std;

#define ii pair<int, int>
#define s second
#define f first

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n, m; cin >> n >> m;
    map<int, set<int>> blocked;
    blocked[n].insert(n+1);
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        blocked[a].insert(b);
    }
    for (auto &row : blocked) row.s.insert(n+1);
    vector<ii> prev = {{1, 1}};
    vector<ii> nxt;
    int prevRow = 0;
    long long ans = 0;
    for (auto &row : blocked) {
        if (prev.size() == 0) break;
        if (row.f != prevRow + 1) {
            int firstCol = prev[0].f;

            prev = {{firstCol, n}};
            //cout << row.f-prevRow-1 << ", " << firstCol << ": " << n-firstCol+1 << ". added" << endl;
            ans += (long long)(row.f-prevRow-1)*(n-firstCol+1);
        }

        int startLoc = 1;
        int idx = 0;
        nxt.clear();
        for (int block : row.s) {
            //cout << "row " << row.f << ": block = " << block << ", startLoc = " << startLoc << endl;
            if (block == startLoc) {
                startLoc++;
                continue;
            }
            while (idx < (int)prev.size() && prev[idx].s < startLoc) idx++;
            if (idx == (int)prev.size() || prev[idx].f > block-1) {
                startLoc = block + 1;
                continue;
            }
            if (prev[idx].f < startLoc) {
                nxt.push_back({startLoc, block-1});
            } else {
                nxt.push_back({prev[idx].f, block-1});
            }
            startLoc = block + 1;
        }
        //for (auto x : nxt) cout << x.f << "," << x.s << endl;
        //cout << "end" << endl;
        prev = nxt;
        prevRow = row.f;
        for (auto x : prev) ans += x.s-x.f+1;
    }
    cout << ans << endl;

    return 0;
}
