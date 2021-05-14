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

    int n, s; cin >> n >> s;
    vector<int> A(n);
    priority_queue<ii> pq;
    map<int, int> ct;
    map<int, vector<int>> reverseIdx;
    F0R(i, n) {
        cin >> A[i];
        A[i]++;
        A[i] %= s;
        ct[A[i]]++;
        reverseIdx[A[i]].pb(i+1);
    }

    for (auto x : ct) {
        if (x.f != 0) {
            pq.push(mp(x.s, x.f));
        }
    }

    int cur = 0;
    int ctr = 0;
    vector<int> ans;
    while (!pq.empty()) {
        ii u = pq.top(); pq.pop();

        if (u.s + cur == s-1 && !pq.empty()) {
            ii newU = pq.top(); pq.pop();
            pq.push(u);
            ans.pb(newU.s);
            if (newU.f-1 > 0) pq.push(mp(newU.f-1, newU.s));
            cur += newU.s;
            cur %= s;
        } else {
            if (u.f-1 > 0) pq.push(mp(u.f-1, u.s));
            cur += u.s;
            cur %= s;
            if (cur == s-1) {
                if (!pq.empty()) ctr++;
                cur = 0;
            }
            ans.pb(u.s);
        }
    }

    cout << ctr << endl;
    for (auto x : reverseIdx[0]) cout << x << " ";
    for (auto x : ans) {
        cout << reverseIdx[x].back() << " ";
        reverseIdx[x].pop_back();
    }
    cout << endl;

    return 0;
}
