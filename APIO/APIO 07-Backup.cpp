/*
 * https://github.com/dolphingarlic/CompetitiveProgramming/blob/master/APIO/APIO%2007-backup.cpp
 */
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
    int n, k; cin >> n >> k;
    vector<int> A(n); F0R(i, n) cin >> A[i];
    vector<ll> dist(n-1);
    vector<int> L(n), R(n);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    F0R(i, n-1) {
        dist[i] = A[i+1]-A[i];
        pq.push(mp(dist[i], i));
        L[i] = i-1; R[i] = i+1;
    }
    vector<bool> alive(n, 1);
    ll best = 0;
    int ct = 0;
    while (!pq.empty()) {
        pair<ll, int> u = pq.top(); pq.pop();
        if (!alive[u.s]) continue;
        best += u.f;
        ct++;
        if (ct == k) break;
        if (L[u.s] >= 0 && R[u.s] < n-1) {
            int l = L[u.s], r = R[u.s];
            L[u.s] = L[l], R[u.s] = R[r];
            if (L[u.s] >= 0) R[L[u.s]] = u.s;
            if (R[u.s] < n-1) L[R[u.s]] = u.s;
            if (alive[l] && alive[r]) {
                dist[u.s] = dist[r] + dist[l] - dist[u.s];
                pq.push(mp(dist[u.s], u.s));
            } else {
                alive[u.s] = 0;
            }
            alive[l] = alive[r] = 0;
        } else {
            if (L[u.s] >= 0) alive[L[u.s]] = 0;
            if (R[u.s] < n-1) alive[R[u.s]] = 0;
            alive[u.s] = 0;
        }
    }
    cout << best << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
