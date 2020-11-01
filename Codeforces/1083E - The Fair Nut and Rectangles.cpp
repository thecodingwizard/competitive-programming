/*
 * CHT
 * https://usaco.guide/plat/cht
 */

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define pb push_back

struct Rect {
    ll x, y, a;

    bool operator<(Rect &other) const {
        return x < other.x;
    }
};

struct Func {
    ll m, b;
    ll eval(ll x) {
        return m*x+b;
    }
    long double intersect(Func other) {
        return (long double)(other.b-b)/(m-other.m);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;

    vector<Rect> A;

    for (int i = 0; i < n; i++) {
        ll x, y, a; cin >> x >> y >> a;
        A.pb(Rect{x,y,a});
    }

    sort(A.begin(), A.end());

    ll ans = 0;
    deque<Func> functions;
    for (int i = 0; i < n; i++) {
        ll val = A[i].x*A[i].y-A[i].a;

        if (!functions.empty()) {
            while (functions.size() >= 2) {
                Func last = functions.back();
                Func secondLast = functions[functions.size()-2];
                if (last.eval(A[i].y) < secondLast.eval(A[i].y)) {
                    functions.pop_back();
                } else {
                    break;
                }
            }
            val += max(0LL, functions.back().eval(A[i].y));
        }

        ans = max(ans, val);

        Func cur = {-A[i].x, val};
        while (functions.size() >= 2) {
            Func first = functions[0], second = functions[1];
            if (first.intersect(second) <= first.intersect(cur)) {
                functions.pop_front();
            } else {
                break;
            }
        }
        functions.push_front(cur);
    }

    cout << ans << endl;

    return 0;
}
