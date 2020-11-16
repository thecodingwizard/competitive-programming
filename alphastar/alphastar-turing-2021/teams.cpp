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

    int n; cin >> n;
    vector<int> A;
    F0R(i, n) {
        int x; cin >> x; A.pb(x);
    }
    sort(all(A));

    n -= A.back();

    int teams = 1;
    F0R(i, n) {
        int ct = 1;
        int need = A[i];
        while (ct < need && i+1 < n) {
            ct++; i++;
            need = A[i];
        }
        if (ct >= need) teams++;
    }
    cout << teams << endl;

    return 0;
}
