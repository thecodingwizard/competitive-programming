/*
 * https://github.com/tmwilliamlin168/CompetitiveProgramming/blob/master/APIO/15-Bridge.cpp
 * Note that for a given set of (A, B), the optimal location to place the bridge
 * is in the median of the set of A's and B's
 *
 * Further note that for a pair (A, B), it should go to the bridge closer to its midpoint
 *
 * Sort the pairs (A, B) by their midpoint, calculate the cost of each prefix/suffix,
 * then try each median
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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int k, n; cin >> k >> n;
    ll ans = 0;
    vector<ii> A;
    for (int i = 0; i < n; i++) {
        char a, b; int c, d; cin >> a >> c >> b >> d;
        if (a == b) ans += abs(d-c);
        else A.pb(mp(min(c, d), max(c, d)));
    }

    sort(all(A), [](ii l, ii r) { return (l.f+l.s) < (r.f + r.s); });
    priority_queue<int> r1, r2;
    ll r1s = 0, r2s = 0;
    vector<ll> costs;
    for (auto x : A) {
        r1.push(x.f); r2.push(-x.s);
        int mid = r1.top();
        r1s += x.f; r2s += x.s;
        if (mid > -r2.top()) {
            r2.push(-mid);
            r2s += mid;
            r1.push(-r2.top());
            r1s += -r2.top();
            r2s -= -r2.top();
            r2.pop();
            r1s -= r1.top();
            r1.pop();
        }
        costs.pb(r2s-r1s);
    }
    while (!r1.empty()) r1.pop();
    while (!r2.empty()) r2.pop();
    vector<ll> costs2;
    reverse(all(A));
    r1s = r2s = 0;
    for (auto x : A) {
        r1.push(x.f); r2.push(-x.s);
        int mid = r1.top();
        r1s += x.f; r2s += x.s;
        if (mid > -r2.top()) {
            r2.push(-mid);
            r2s += mid;
            r1.push(-r2.top());
            r1s += -r2.top();
            r2s -= -r2.top();
            r2.pop();
            r1s -= r1.top();
            r1.pop();
        }
        costs2.pb(r2s-r1s);
    }
    if (k == 1) {
        ll output = (ll)ans + (costs.empty() ? 0 : (ll)costs.back()) + (ll)costs.size();
        cout << output << endl;
    } else {
        ll best = (ll)ans + (costs.empty() ? 0 : (ll)costs.back()) + (ll)costs.size();
        for (int i = 0; i < (int)A.size()-1; i++) {
            best = min(best, (ll)ans + (ll)costs.size() + costs[i] + costs2[(ll)A.size()-i-2]);
        }
        cout << best << endl;
    }

    return 0;
}
