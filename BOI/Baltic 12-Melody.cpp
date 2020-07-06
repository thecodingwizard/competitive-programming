/*
 * compute distance between every pair of notes.
 *
 * define dp[i] = min cost to finish playing piece assuming the note at index i
 * was played properly.
 *
 * to transition, we need to determine what's the next note we want to play (O(n)).
 *
 * we keep track of the indexes of every note, and we find the smallest index of the
 * target note that we can transition to (can do this with binary search or just
 * dumb brute force).
 *
 * go from i = n-1 to i = 0.
 */

#include <bits/stdc++.h>

using namespace std;

#define vi vector<int>
#define pb push_back
#define ii pair<int, int>
#define f first
#define s second
#define ll long long

int dist(string &s1, string &s2) {
    int c = 0;
    for (int i = 0; i < s1.size(); i++) {
        if (s1[i] != s2[i]) c++;
    }
    return c;
}

int main() {
    cin.tie(0); ios_base::sync_with_stdio(0);

    int n, s, g; cin >> n >> s >> g;
    string A[n]; for (int i = 0; i < n; i++) cin >> A[i];
    vi adj[n];
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (dist(A[i], A[j]) <= g) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }
    int d[n][n], dnxt[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) d[i][j] = -1;
        d[i][i] = 0;
        queue<int> q; q.push(i);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (d[i][v] == -1) {
                    d[i][v] = d[i][u] + 1;
                    if (d[i][v] == 1) dnxt[i][v] = v;
                    else dnxt[i][v] = dnxt[i][u];
                    q.push(v);
                }
            }
        }
    }

    int l; cin >> l;
    int B[l]; for (int i = 0; i < l; i++) { cin >> B[i]; B[i]--; }
    int dp[l];
    int dpnxt[l];
    vector<int> indexes[n];
    for (int i = l-1; i>=0; i--) {
        if (i == l-1) {
            dp[i] = 0; dpnxt[i] = -1;
        } else {
            dp[i] = l-i-1;
            dpnxt[i] = -1;
            for (int x = 0; x < n; x++) {
                int di = d[B[i]][x];
                if (di == -1) continue;
                for (int k = indexes[x].size()-1; k >= 0; k--) {
                    int j = indexes[x][k];
                    if (di <= j-i && dp[i] > dp[j] + j-i-1) {
                        dp[i] = dp[j] + j-i-1;
                        dpnxt[i] = j;
                    }
                    if (di <= j-i) break;
                }
            }
        }
        indexes[B[i]].push_back(i);
    }

    int bestStart = 0;
    for (int i = 1; i < l; i++) if (dp[i] + i < dp[bestStart] + bestStart) bestStart = i;

    cout << dp[bestStart] + bestStart << "\n";
    int note = bestStart;
    int printed = bestStart;
    for (int i = 0; i < printed; i++) cout << B[bestStart]+1 << " ";
    while (note != -1) {
        if (dpnxt[note] == -1) {
            for (; printed < l; printed++) {
                cout << B[note]+1 << " ";
            }
            cout << endl;
            return 0;
        }
        int start = B[note], end = dpnxt[note] == -1 ? -1 : B[dpnxt[note]];

        while (start != end) {
            cout << start+1 << " ";
            printed++;
            start = dnxt[start][end];
        }
        for (; printed < dpnxt[note]; printed++) cout << start+1 << " ";

        note = dpnxt[note];
    }

    return 0;
}
