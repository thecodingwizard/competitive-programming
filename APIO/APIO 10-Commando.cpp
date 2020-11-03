/*
 * Convex Hull Trick: https://usaco.guide/plat/cht
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
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)

#define maxn 1000000

int n;
ll a, b, c;
ll A[maxn];
ll ps[maxn];

struct Func {
    ll m, b;

    long double intersectX(Func other) {
        return (long double)(b-other.b)/(other.m-m);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> a >> b >> c;
    F0R(i, n) cin >> A[i];
    ps[0] = A[0];
    FOR(i, 1, n) ps[i] = ps[i-1] + A[i];

    deque<Func> functions;
    functions.pb(Func{b, 0});
    vector<int> ints(n); F0R(i, n) ints[i] = i;
    for (int i = 0; i < n; i++) {
        int idx = *lower_bound(ints.begin(), ints.begin()+functions.size()-1, ps[i], [&functions](int idx, ll x) {
            return functions[idx].intersectX(functions[idx+1]) < x;
        });

        ll val = functions[idx].m*ps[i]+functions[idx].b + a*ps[i]*ps[i] + c;
        if (i == n-1) cout << val << endl;
        else {
            Func f = {-2LL*a*ps[i]+b, val+a*ps[i]*ps[i]-b*ps[i]};
            while (functions.size() >= 2 && f.intersectX(functions[functions.size()-1]) <= functions[functions.size()-1].intersectX(functions[functions.size()-2])) {
                functions.pop_back();
            }
            functions.push_back(f);
        }
    }

    return 0;
}
