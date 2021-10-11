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

    string s; cin >> s;

    int ans = 0;
    int previousBearIndex = -1;
    for (int i = 0; i < (int)s.size() - 3; i++) {
        if (s.substr(i, 4) == "bear") {
            ans += (i - previousBearIndex)*(s.size() - 3 - i);
            previousBearIndex = i;
        }
    }

    cout << ans << endl;

    return 0;
}

// Alt: two nested for loops and only check rightmost