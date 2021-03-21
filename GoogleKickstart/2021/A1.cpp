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

    int t; cin >> t;
    int x = 1;
    while (t--) {
        int n, m; cin >> n >> m;
        string s; cin >> s;

        for (int i = 0; i < n/2; i++) {
            if (s[i] != s[n-i-1]) {
                m--;
            }
        }
        cout << "Case #" << x << ": " << abs(m) << endl;
        x++;
    }

    return 0;
}
