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

void solve() {
    int n, c; cin >> n >> c; c -= n-1;
    if (c < 0) {
        cout << "IMPOSSIBLE" << endl;
        return;
    }
    vector<int> A(n); A[n-1] = n;
    for (int i = n-2; ~i; i--) {
        int len = min(c, n-i-1);
        for (int diff = 0; diff <= len/2; diff++) {
            swap(A[i+diff], A[i+len-diff]);
        }

        A[i+len] = i+1;

        c -= len;
    }
    if (c != 0) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        for (auto x : A) cout << x << " ";
        cout << endl;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        cout << "Case #" << tc << ": ";
        solve();
    }

    return 0;
}
