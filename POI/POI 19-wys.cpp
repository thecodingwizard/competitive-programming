/*
 * Sort all the initial points. Note that no query will change the relative ordering of these points.
 * Further note that to answer a Z query, we simply have to find the number of numbers x such that
 * x >= max(A[i] + (n-i) - n) across all i.
 *
 * We can update the i that yields the maximum A[i]+(n-i)-n after each update:
 * - note that the optimal i will either stay the same or increase after each update
 * - just once at the start of the program, make a list of indexes such that A[i]+(n-i)-n forms a decreasing sequence
 * - if the optimal i changes, it will become the next i that isn't affected by the update in the list of indexes
 * 
 * We can handle updates with a binary indexed tree + binary search,
 * and we can answer Z queries by binary searching.
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

ll bit[300010];

void upd(int k, ll v) {
    while (k <= 300009) {
        bit[k] += v;
        k += k&-k;
    }
}
ll qry(int k) {
    ll s = 0;
    while (k) {
        s += bit[k];
        k -= k&-k;
    }
    return s;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q; cin >> n >> q;
    vector<ll> A;
    F0R(i, n) {
        ll x; cin >> x; A.pb(x);
    }
    sort(all(A));

    vector<pair<ll, int>> cutoff;
    F0R(i, n) {
        ll val = A[i] + (n-i) - n;
        while (!cutoff.empty() && cutoff.back().f <= val) {
            cutoff.pop_back();
        }
        cutoff.pb(mp(val, i));
    }
    int cutoffIdx = 0;

    ll totSubtract = 0;
    ll deltaX = 0;

    F0R(i, q) {
        char c; cin >> c;

        int maxIdx, changeValue;
        if (c == 'Z') {
            int lo = 0, hi = n, ans = n;

            ll cutoffVal = cutoff[cutoffIdx].f - totSubtract + qry(cutoff[cutoffIdx].s+1);

            while (lo < hi) {
                int mid = (lo+hi)/2;
                ll midVal = A[mid] - totSubtract + qry(mid+1);
                if (midVal >= cutoffVal) {
                    ans = mid;
                    hi = mid;
                } else {
                    lo = mid + 1;
                }
            }

            cout << n - ans << "\n";
            continue;
        } else if (c == 'B') {
            ll x, y; cin >> x >> y; x -= deltaX;

            int lo = 0, hi = n, ans = -1;

            while (lo < hi) {
                int mid = (lo+hi)/2;
                ll midVal = A[mid] - totSubtract + qry(mid+1);
                if (midVal >= x) {
                    hi = mid;
                } else {
                    ans = mid;
                    lo = mid + 1;
                }
            }

            maxIdx = ans;
            deltaX += y;
            changeValue = y;
        } else {
            ll x, y; cin >> x >> y; x -= deltaX;

            int lo = 0, hi = n, ans = -1;

            while (lo < hi) {
                int mid = (lo+hi)/2;
                ll midVal = A[mid] - totSubtract + qry(mid+1);
                if (midVal > x) {
                    hi = mid;
                } else {
                    ans = mid;
                    lo = mid + 1;
                }
            }

            maxIdx = ans;
            changeValue = y;
        }

        totSubtract += changeValue;
        upd(maxIdx+2, changeValue);

        int lo = 0, hi = cutoff.size(), unaffectedIdx = -1;
        while (lo < hi) {
            int mid = (lo+hi)/2;
            if (cutoff[mid].s > maxIdx) {
                unaffectedIdx = mid;
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }

        if (unaffectedIdx != -1) {
            ll curVal = cutoff[cutoffIdx].f - totSubtract + qry(cutoff[cutoffIdx].s+1);
            ll unaffectedVal = cutoff[unaffectedIdx].f - totSubtract + qry(cutoff[unaffectedIdx].s+1);
            if (curVal < unaffectedVal) {
                cutoffIdx = unaffectedIdx;
            }
        }
    }

    return 0;
}
