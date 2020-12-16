/*
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

    ll dpN = 0; // value of dp[i][i]: how much it costs to buy all the stocks

    // should be nondecreasing
    priority_queue<int, vector<int>, greater<int>> slopes;

    F0R(i, n) {
        int x; cin >> x;
        dpN -= x;

        slopes.push(x); slopes.push(x);
        slopes.pop();
    }

    while (!slopes.empty()) {
        dpN += slopes.top(); slopes.pop();
    }

    cout << dpN << endl;

    return 0;
}
