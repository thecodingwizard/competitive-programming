/*
 * slope trick!
 *
 * https://usaco.guide/adv/slope
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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;

    ll dp0 = 0; // y-intercept

    // slope increases by one at each of these points
    priority_queue<ll> slopeChanges;

    ll initialSlope = 0;

    ll totA = 0, totB = 0;
    ll diff;
    F0R(i, n) {
        int a, b; cin >> a >> b; totA += a; totB += b;

        diff = totA - totB;

        dp0 += abs(diff);
        initialSlope--;

        // at x = diff, the function slope changes by two
        slopeChanges.push(diff);
        slopeChanges.push(diff);

        // remove the final slope change that will cause the slope to become positive
        slopeChanges.pop();
    }

    // Want to calculate dp value where x = diff (the final difference)
    vector<ll> changes;
    while (!slopeChanges.empty()) { changes.pb(slopeChanges.top()); slopeChanges.pop(); }
    reverse(all(changes));
    ll curX = 0, slope = initialSlope;
    for (ll x : changes) {
        ll dist = x - curX;
        if (x >= diff) {
            dp0 += slope*dist;
            break;
        }
        if (x >= 0) {
            dp0 += slope*dist;
            curX = x;
        }
        slope++;
    }

    cout << dp0 << endl;

    return 0;
}
