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
    while (t--) {
        int n; cin >> n;
        vector<int> A; F0R(i, n) { int x; cin >> x; A.pb(x); }
        int L[n], R[n];
        stack<int> s;
        F0R(i, n) {
            while (!s.empty() && A[s.top()] > A[i]) {
                R[s.top()] = i;
                s.pop();
            }
            L[i] = s.empty() ? -1 : s.top();
            s.push(i);
        }
        while (!s.empty()) {
            R[s.top()] = n;
            s.pop();
        }

        vector<ii> events;
        F0R(i, n) {
            events.pb(mp(R[i]-L[i], A[i]));
        }
        sort(all(events));

        set<int> unique;
        map<int, int> ct;

        F0R(i, n) {
            unique.insert(A[i]);
            ct[A[i]]++;
        }

        int dupCt = 0;
        for (auto x : ct) if (x.s > 1) dupCt++;

        bool valid[n];

        int idx = 0;
        F0R(i, n) {
            while (idx < (int)events.size() && events[idx].f <= i+1) {
                int toRemove = events[idx].s;
                if (ct[toRemove] == 1) {
                    ct[toRemove] = 0;
                    unique.erase(toRemove);
                } else {
                    ct[toRemove]--;
                    if (ct[toRemove] == 1) {
                        dupCt--;
                    }
                }
                idx++;
            }
            if (dupCt == 0 && unique.size() == n-i && *unique.begin() == 1 && *unique.rbegin() == n-i) valid[i] = true;
            else valid[i] = false;
        }
        F0R(i, n) if (valid[i]) cout << "1"; else cout << "0";
        cout << "\n";
    }

    return 0;
}
