/*
 * Same solution as editorial
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

ll solve(vector<int> need, int depth) {
    if (depth > 12) return -1;

    if (need.size() == 1) {
        ll ans = 0;
        bool needzero = false;
        F0R(i, 10) {
            int j = i;
            if (need[0] & (1 << j)) {
                if (j == 0) {
                    needzero = 1;
                } else {
                    ans = ans*10+j;
                    if (needzero) {
                        ans = ans*10;
                        needzero = 0;
                    }
                }
            }
        }
        if (ans == 0 && needzero) return 10;
        return ans;
    }

    ll ans = -1;
    F0R(lastDigit, 10) {
        vector<int> next;
        int curDigit = lastDigit;
        int curMask = 0;

        for (auto x : need) {
            curMask |= x & ~(1 << curDigit);

            curDigit++;
            if (curDigit == 10) {
                next.pb(curMask);
                curDigit = 0;
                curMask = 0;
            }
        }
        if (curDigit != 0) next.pb(curMask);

        ll ans2 = solve(next, depth + 1);
        if (ans2 == -1) continue;
        ll nxt = ans2*10+lastDigit;
        if (lastDigit == 0 && ans2 == 0 && need[0] != 0) nxt = 10;
        if (ans == -1 || nxt < ans) {
            ans = nxt;
        }
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int k; cin >> k;
    vector<int> A;
    F0R(i, k) {
        int x; cin >> x;
        A.pb(1 << x);
    }

    cout << solve(A, 1) << endl;

    return 0;
}
