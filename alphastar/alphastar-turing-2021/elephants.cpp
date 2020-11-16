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

    int n, l, m; cin >> n >> l >> m;
    set<int> A;
    vector<int> positions;
    F0R(i, n) {
        int x; cin >> x; A.insert(x);
        positions.pb(x);
    }
    F0R(i, m) {
        int a, b; cin >> a >> b;
        A.erase(positions[a]);
        positions[a] = b;
        A.insert(b);

        int ct = 0;
        int cur = -1;
        for (int x : A) {
            if (cur < x) {
                cur = x + l;
                ct++;
            }
        }
        cout << ct << "\n";
    }

    return 0;
}
