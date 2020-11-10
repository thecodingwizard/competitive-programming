/*
 * Basically the same solution as https://github.com/farmerboy95/CompetitiveProgramming/blob/master/POI/POI%2008-Permutation.cpp
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
#define inf 1000000010

#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <class T> using Tree = tree<T, null_type, less<T>, 
	rb_tree_tag, tree_order_statistics_node_update>; 
#define ook order_of_key
#define fbo find_by_order

map<int, int> primeCt;

ll binPow(ll b, ll p, ll m) {
    ll ans = 1;
    while (p>0) {
        if (p % 2 == 1) ans = ans*b%m;
        b = b*b%m;
        p /= 2;
    }
    return ans;
}

// https://usaco.guide/adv/extend-euclid
array<ll,3> extendEuclid(ll a, ll b) {
    array<ll,3> x = {1,0,a}, y = {0,1,b};
    // we know that 1*a+0*b=a and 0*a+1*b=b
    for (;y[2];swap(x,y)) { // run extended Euclidean algo
        ll k = x[2]/y[2];
        F0R(i,3) x[i] -= k*y[i];
        // keep subtracting multiple of one equation from the other
    }
    return x; // x[0]*a+x[1]*b=x[2], x[2]=gcd(a,b)
}

ll modInv(int a, int m) {
    array<ll, 3> x = extendEuclid(a, m);
    assert(x[2] == 1);
    return x[0] + (x[0]<0)*m;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n, m; cin >> n >> m;
    vector<int> factors;
    if (m%2 == 0) factors.pb(2);
    ll m2 = m;
    while (m2%2==0) m2 /= 2;
    for (int i = 3; i*i <= m2; i+=2) {
        if (m2%i == 0) {
            while (m2 % i == 0) m2 /= i;
            factors.pb(i);
        }
    }
    if (m2 != 1) factors.pb(m2);
    vector<int> A;
    F0R(i, n) {
        int x; cin >> x; A.pb(x);
    }
    Tree<ii> numbersSmaller;
    ll ans = 1;
    ll mult = 1;
    map<int, int> ct;
    for (int i = n-1; ~i; --i) {
        ll numSmaller = numbersSmaller.ook(mp(A[i], i));
        numbersSmaller.insert(mp(A[i], i));

        ct[A[i]]++;
        int inverse = ct[A[i]];
        for (int f : factors) {
            while (inverse > 0 && inverse % f == 0) {
                inverse /= f;
                primeCt[f]--;
                if (primeCt[f] == -1) {
                    numSmaller/=f;
                }
            }
        }
        mult = (mult*modInv(inverse, m))%m;

        ll mult2 = 1;
        for (int f : factors) {
            mult2 = (mult2*binPow(f, primeCt[f], m))%m;
        }

        ans = (ans+numSmaller*mult%m*mult2)%m;
        int num = n-i;
        for (int f : factors) {
            while (num % f == 0) {
                num /= f;
                primeCt[f]++;
            }
        }
        mult = (mult*num)%m;
        //cout << ans << endl;
    }

    cout << ans << endl;

    return 0;
}
