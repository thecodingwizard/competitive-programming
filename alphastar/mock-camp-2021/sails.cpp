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

int bit[100010];

void upd(int k, int v) {
    while (k <= 100000) {
        bit[k] += v;
        k += k&-k;
    }
}

int qry(int k) {
    int s = 0;
    while (k) {
        s += bit[k];
        k -= k&-k;
    }
    return s;
}

int get(int x) {
    return qry(x);
}

// return [a...b] where all the numbers in [a...b] is num
ii getRange(int num) {
    int lo = 1, hi = 100001, lowerbound;
    while (lo < hi) {
        int mid = (lo+hi)/2;
        int val = get(mid);
        if (val == num) {
            lowerbound = mid;
            hi = mid;
        } else {
            if (val > num) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
    }
    lo = 1, hi = 100001;
    int upperbound;
    while (lo < hi) {
        int mid = (lo+hi)/2;
        int val = get(mid);
        if (val == num) {
            upperbound = mid;
            lo = mid + 1;
        } else {
            if (val > num) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
    }
    return mp(lowerbound, upperbound);
}

// add one to the range [a...b] inclusive
void updateRange(int a, int b) {
    upd(a, 1);
    upd(b+1, -1);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
 
    int n; cin >> n;
    vector<ii> A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i].f >> A[i].s;
    }

    sort(all(A), [](const ii &a, const ii &b) {
        return a.f < b.f;
    });

    F0R(i, n) {
        if (A[i].s == 0) continue;
        int val = get(A[i].f-A[i].s+1);
        ii range = getRange(val);
        int todo = A[i].s;
        if (range.s < A[i].f) {
            updateRange(range.s+1, A[i].f);
            todo -= A[i].f - range.s;
        }
        updateRange(range.f, range.f + todo - 1);
    }

    ll ans = 0;
    for (int i = 1; i <= 100000; i++) {
        ll x = get(i);
        ans += x*(x-1)/2;
    }
    cout << ans << endl;

    return 0;
}
