/*
 * Square root decomposition
 * define ct[x][y] = number of containers spaced x apart starting from index i where i % x = y.
 * Update ct[x][y] as we sweep from left to right.
 *
 * If we encounter a block that's spaced more than sqrt(n) apart, instead of adding it to ct[x][y], we
 * can directly loop through the indexes that it will update, since at most it will update sqrt(n) indexes.
 *
 * At each index, we loop through x = 1...sqrt(n) and add ct[x][index % x] to the number of blocks we have at this index.
 * 
 * Time complexity is O(n sqrt n)
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
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define inf 1000000010

#define sqrtn 316
#define maxn 100000
int blocks[maxn];
int toAdd[sqrtn][sqrtn];

vector<pair<ii, int>> events[2*maxn];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k; cin >> n >> k;
    for (int i = 0; i < k; i++) {
        int a, l, d; cin >> a >> l >> d; --a;
        if (d >= sqrtn) {
            assert(l <= sqrtn);
            for (int j = a; j <= a+(l-1)*d; j += d) blocks[j]++;
        } else {
            events[a].pb(mp(mp(a, d), 1));
            events[a+l*d].pb(mp(mp(a, d), -1));
        }
    }

    for (int i = 0; i < n; i++) {
        for (auto e : events[i]) {
            toAdd[e.f.s][e.f.f%e.f.s] += e.s;
        }
        for (int j = 1; j < sqrtn; j++) {
            blocks[i] += toAdd[j][i%j];
        }
    }

    for (int i = 0; i < n; i++) cout << blocks[i] << " \n"[i==n-1];

    return 0;
}
