/*
 * https://github.com/Szawinis/CompetitiveProgramming/blob/master/Olympiad/Baltic/Baltic09-candy.cpp
 *
 * Sort by y[i]-x[i] increasing, then partition the sorted array into subsequences where x[i]+y[i] is nondecreasing 
 * You can do this greedily
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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vector<ii> A(n);
    F0R(i, n) {
        cin >> A[i].f >> A[i].s;
    }

    sort(all(A), [](ii a, ii b) {
        if (a.s-a.f == b.s-b.f) return a.f+a.s < b.f+b.s;
        return a.s-a.f < b.s-b.f;
    });

    int ctr = 0;
    set<ii> wagons;
    int ans[n];

    for (int i = 0; i < n; i++) {
        ii x = A[i];
        int search = x.f+x.s;
        auto it = wagons.upper_bound(mp(search, inf));
        if (it == wagons.begin()) {
            wagons.insert(mp(search, ++ctr));
            ans[i] = ctr;
        } else {
            ans[i] = (--it)->s;
            wagons.erase(it);
            wagons.insert(mp(search, ans[i]));
        }
    }

    cout << ctr << "\n";
    F0R(i, n) {
        cout << A[i].f << " " << A[i].s << " " << ans[i] << "\n";
    }

    return 0;
}
