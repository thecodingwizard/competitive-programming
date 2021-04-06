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
    int n; cin >> n;
    int A[n]; F0R(i, n) cin >> A[i];

    bool g = 1;
    vector<int> newSeq;
    F0R(i, n) if (A[i] <= n) newSeq.pb(A[i]);
    int lastCar = -1;
    for (int i = 0; i < sz(newSeq); i++) {
        if (lastCar != -1 && lastCar <= newSeq[i]) g = 0;
        if (i == sz(newSeq)-1) continue;
        if (newSeq[i] >= newSeq[i+1]) {
            if (lastCar != -1) g = 0;
            else {
                lastCar = newSeq[i];
            }
        }
    }
    cout << g << endl;

    return 0;
}
