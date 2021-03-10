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
    vector<ii> A(n);
    F0R(i, n) {
        cin >> A[i].f >> A[i].s;
    }
    sort(all(A));
    int q; cin >> q;
    F0R(i, q) {
        int m; cin >> m;

        bool g = 1;

        multiset<int> endpoints;
        int idx = 0;

        vector<int> stuff;
        F0R(i, m) {
            int k; cin >> k;
            stuff.pb(k);
        }
        sort(all(stuff));

        F0R(i, m) {
            int k = stuff[i];
            while (idx < n && A[idx].f <= k) {
                endpoints.insert(A[idx].s);
                idx++;
            }
            for (int i = 0; i < k; i++) {
                auto it = endpoints.lower_bound(k);
                if (it == endpoints.end()) g = 0;
                else endpoints.erase(it);
            }
        }
        cout << g << endl;
    }

    return 0;
}
