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

int r, c;
int A[300][300];
int B[300][300];

int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, -1, 0, 1 };

void solve() {
    cin >> r >> c;
    F0R(i, r) F0R(j, c) cin >> A[i][j];
    F0R(i, r) F0R(j, c) B[i][j] = A[i][j];

    priority_queue<pair<int, ii>> pq;
    F0R(i, r) F0R(j, c) pq.push(mp(A[i][j], mp(i, j)));

    while (!pq.empty()) {
        pair<int, ii> u = pq.top(); pq.pop();
        if (u.f < A[u.s.f][u.s.s]) continue;

        F0R(i, 4) {
            ii v = mp(u.s.f+dx[i], u.s.s+dy[i]);
            if (v.f < 0 || v.f >= r || v.s < 0 || v.s >= c) continue;
            if (A[v.f][v.s] < u.f-1) {
                A[v.f][v.s] = u.f-1;
                pq.push(mp(u.f-1, v));
            }
        }
    }

    ll ans = 0;
    F0R(i, r) F0R(j, c) ans += A[i][j] - B[i][j];
    cout << ans << endl;
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
