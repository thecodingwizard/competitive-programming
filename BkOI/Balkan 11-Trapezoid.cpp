/*
 * Sort all the trapezoids by their top left coordinate.
 *
 * To handle the bottom coordinates, use seg tree / BIT / etc. I used an offline
 * compressed Binary Indexed Tree (though my impl was extremely messy).
 *
 * When you reach a trapezoid's top left coordinate, first, add all the trapezoids
 * whose top right coordinate comes before this trapezoid's top left coordinate.
 * Add the trapezoids into the data structure that handles bottom coordinates.
 *
 * Then, compute the DP value for this trapezoid by querying the bottom data structure.
 *
 * Essentially, sorting will handle the top coordinates while a data structure
 * will handle the bottom coordinates.
 *
 * My implementation is extremely messy...
 */

#include <bits/stdc++.h>
 
using namespace std;
 
#define pb push_back
#define ii pair<int, int>
#define f first
#define s second
 
const int mod = 30013;

struct BIToff {
    bool mode = 0; vector<int> v; vector<int> ft;
    int idx(int x) { return upper_bound(v.begin(), v.end(), x) - v.begin(); }
    void init() {
        mode = 1;
        sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end());
        ft.resize((int)v.size()+1);
    }
    void upd(int x, int y) {
        if (!mode) { v.pb(x); return; }
        int k = idx(x);
        for (; k <= (int) v.size(); k += k&-k) ft[k] = (ft[k] + y) % mod;
    }
    int sum(int x) {
        int ans = 0; for (int p = idx(x); p; p -= p&-p) ans += ft[p];
        return ans;
    }
} bits[100001];
 
int main() {
    int n; cin >> n;
    vector<ii> topLeft;
    vector<pair<ii, ii>> A;
    for (int i = 0; i < n; i++) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        A.pb({{a,b},{c,d}});
        topLeft.pb({a,i});
    }
    sort(topLeft.begin(), topLeft.end());
 
    int tlIdx = 0;
    set<ii> q;
    map<int, int> traps;
    int dp[n];

    // 1 = add, 2 = calculate
    vector<pair<int, ii>> events;
    while (tlIdx != n) {
        while (!q.empty() && q.begin()->f < topLeft[tlIdx].f) {
            int x = q.begin()->s;
            q.erase(q.begin());
            auto it = traps.lower_bound(A[x].s.s);
            while (it != traps.end() && it->s < dp[x]) {
                it = traps.erase(it);
            }
            it = traps.lower_bound(A[x].s.s);
            if (!traps.empty()) {
                if (it != traps.begin()) {
                    it--;
                    if (it->s > dp[x]) continue;
                }
            }
            events.push_back({1, {A[x].s.s, x}});
            traps[A[x].s.s] = dp[x];
        }
 
        int u = topLeft[tlIdx].s;
        int best = 1;
        if (!traps.empty()) {
            auto it = traps.lower_bound(A[u].s.f);
            if (it != traps.begin()) {
                it--;
                best = 1 + it->s;
            }
        }
        events.push_back({2, {u,-1}});
        dp[u] = best;
        q.insert({A[u].f.s, u});
 
        tlIdx++;
    }

    ii dp2[n];
    for (auto e : events) {
        if (e.f == 1) {
            bits[dp[e.s.s]].upd(e.s.f, dp2[e.s.s].s);
        }
    }
    bits[0].upd(1,1);
    for (int i = 0; i <= n; i++) bits[i].init();
    bits[0].upd(1,1);
    for (auto e : events) {
        if (e.f == 1) {
            bits[dp[e.s.s]].upd(e.s.f, dp2[e.s.s].s);
        } else {
            dp2[e.s.f] = make_pair(dp[e.s.f], bits[dp[e.s.f]-1].sum(A[e.s.f].s.f));
        }
    }

    int ans = 0;
    int ans2 = 0;
    for (int i = 0; i < n; i++) {
        if (dp2[i].f > ans) {
            ans = dp2[i].f; ans2 = dp2[i].s;
        } else if (dp2[i].f == ans) {
            ans2 = (ans2 + dp2[i].s) % mod;
        }
    }
 
    cout << ans << " " << ans2 << endl;
 
    return 0;
}
