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
    for (int tc = 1; tc <= t; tc++) {
        cout << "Case #" << tc << ": ";

        int n, m; cin >> n >> m;
        map<int, int> unswappedModels;
        map<int, int> swappedModels;
        F0R(i, m) {
            int s; cin >> s;
            unswappedModels[s]++;
        }
        ll ans = 0;
        F0R(i, n) {
            map<int, int> reqs;
            F0R(j, m) {
                int x; cin >> x;
                reqs[x]++;
            }
            ans += m;

            map<int, int> leftoverReqs;
            map<int, int> newUnswapped, newSwapped;
            for (ii y : reqs) {
                ii x = y;
                if (swappedModels[x.f] > 0) {
                    x.s -= swappedModels[x.f];
                }
                if (x.s > 0) {
                    if (unswappedModels[x.f] > 0) {
                        int ct = min(unswappedModels[x.f], x.s);
                        unswappedModels[x.f] -= ct;
                        newUnswapped[x.f] += ct;
                        x.s -= ct;
                    }
                }
                ans -= y.s - max(x.s, 0);
            }
            for (ii x : unswappedModels) {
                ans -= x.s;
            }
            for (ii x : reqs) {
                int ct = x.s - newUnswapped[x.f];
                assert(ct >= 0);
                newSwapped[x.f] = ct;
            }
            swap(unswappedModels, newUnswapped);
            swap(swappedModels, newSwapped);
        }
        cout << ans << endl;
    }

    return 0;
}
