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

    int t; cin >> t;
    F0R(asdkfj, t) {
        int n, k; cin >> n >> k;
        vector<ii> A;
        F0R(i, n) {
            int a, b; cin >> a >> b;
            A.pb(mp(a, b));
        }
        bool can = false;

        F0R(i, n) {
            bool good = true;
            F0R(j, n) {
                if (abs(A[j].f-A[i].f)+abs(A[j].s-A[i].s) > k) good = false;
            }
            if (good) can = true;
        }

        cout << (can ? "1" : "-1") << endl;
    }

    return 0;
}
