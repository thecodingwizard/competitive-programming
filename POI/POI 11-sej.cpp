/*
 * https://github.com/tmwilliamlin168/CompetitiveProgramming/blob/master/POI/18T-Strongbox.cpp
 *
 * We want to find the smallest number x such that gcd(A[i], x) % x != 0 for all 0 <= i < k-1, and gcd(A[k-1], n) % x == 0.
 *
 * To do this, first make a list of all the primes of n. Then, for all A[i] where 0 <= i < k-1, we want to make a set
 * of all the "illegal" numbers that are divisors of A[i]. To do this:
 * - Add A[i] to the set
 * - For every prime factor p of n, if A[i] % p == 0 and A[i]/p is not yet in the set, recurse to A[i]/p.
 *
 * See implementation for more details
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

vector<ll> primes;
ll ans = 1e18;
set<ll> illegalNumbers;

void handleNumber(ll n, bool updAns) {
    illegalNumbers.insert(n);
    if (updAns) ans = min(ans, n);
    for (ll p : primes) {
        if (n % p == 0 && illegalNumbers.count(n/p) == 0) {
            handleNumber(n/p, updAns);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n; int k; cin >> n >> k;
    ll origN = n;
    if (k == 1) {
        cout << n << endl;
        return 0;
    }

    for (ll i = 2; i*i <= n; i++) {
        if (n%i == 0) {
            primes.pb(i);
            while (n%i == 0) n /= i;
        }
    }
    if (n>1) primes.pb(n);

    F0R(i, k) {
        ll x; cin >> x;
        handleNumber(__gcd(origN, x), i==k-1);
    }

    cout << origN/ans << endl;

    return 0;
}
