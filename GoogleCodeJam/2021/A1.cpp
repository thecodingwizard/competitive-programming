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
    int n; cin >> n;
    vector<int> A(n);
    F0R(i, n) cin >> A[i];

    int cost = 0;
    for (int i = 0; i < n-1; i++) {
        int best = i;
        for (int j = i+1; j < n; j++) {
            if (A[best] > A[j]) {
                best = j;
            }
        }
        cost += best-i+1;
        for (int j = i; j < i+(best+1-i)/2; j++) {
            swap(A[j], A[best-j+i]);
        }
    }
    cout << cost << endl;
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
