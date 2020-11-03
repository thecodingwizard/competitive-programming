/*
 * See also: https://codeforces.com/blog/entry/56889?#comment-405308
 *
 * For a given k-fragment, let's identify it by its top left coordinate. Consider one cell:
 * the k-fragments that include it form a k by k square.
 *
 * For every color, the k-fragments that include that color are the union of all the k by k squares.
 * Note that the resulting union can be represented as a lot of disjoint rectangles. We can find
 * these rectangles with a sweepline (when looping on the second direction, use a multiset and binary search
 * for the next value). Then, for each rectangle, we add it to a prefix sum array.
 *
 * Finally, we compute the prefix sum array; ps[i][j] = the value of the k-fragment located at (i, j).
 *
 * Not too sure how the time complexity works, but TL is super lenient at 30 seconds and it passes in time.
 *
 * CF comment says complexity is O(nm log nm).
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
#define inf 1000000000

int m, n, k; 
vector<ii> cells[100000];
int ps[3001][3001];

void solve(int u) {
    if (cells[u].empty()) return;
    //cout << "UPDATING " << u << endl;
    map<int, vector<ii>> events;
    for (auto v : cells[u]) {
        events[v.f-k+1].pb(mp(v.s-k+1, 1));
        events[v.f+1].pb(mp(v.s-k+1, -1));
    }
    multiset<int> stuff;
    int prev2 = -1;
    for (auto e : events) {
        vector<ii> rectangles;
        auto it = stuff.begin();
        while (it != stuff.end()) {
            auto it2 = it;
            while (*(--stuff.upper_bound(*it2+k)) > *it2) it2 = --stuff.upper_bound(*it2+k);
            rectangles.pb(mp(*it, *it2+k-1));
            it = stuff.upper_bound(*it2+k);
        }

        if (e.f-1>=0) {
            //cout << "upd: " << prev2 << " to " << e.f-1 << " (inculsive), with these rectangles: ";
            for (auto r : rectangles) {
                r.f = max(r.f, 0);
                //cout << "(" << r.f << ", " << r.s << "); ";
                ps[prev2][r.f]++; ps[prev2][r.s+1]--;
                ps[e.f][r.f]--; ps[e.f][r.s+1]++;
            }
            //cout << endl;
        }
        prev2 = max(e.f, 0);
        for (auto x : e.s) {
            if (x.s == 1) stuff.insert(x.f);
            else stuff.erase(stuff.find(x.f));
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> m >> n >> k;
    F0R(i, m) {
        F0R(j, n) {
            int x; cin >> x; --x;
            cells[x].pb(mp(i, j));
        }
    }

    F0R(i, 100000) {
        solve(i);
    }

    F0R(i, m) {
        F0R(j, n) {
            ps[i][j] += (i-1>=0?ps[i-1][j]:0) + (j-1>=0?ps[i][j-1]:0) - (i-1>=0&&j-1>=0?ps[i-1][j-1]:0);
        }
    }

    int mx = 0;
    ll tot = 0;
    F0R(i, m-k+1) {
        F0R(j, n-k+1) {
            mx = max(mx, ps[i][j]);
            //cout << "(" << i << "," << j << "): " << ps[i][j] << endl;
            tot += ps[i][j];
        }
    }
    cout << mx << " " << tot << endl;

    return 0;
}
