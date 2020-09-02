/*
 * Note that the numbers that appear are periodic.
 *
 * We can calculate its period as (A/__gcd((B+1)%A, A))*B.
 *
 * Once we have the period, we just need to count how much of the period is covered
 * by the given ranges, which we can do pretty easily with a map and sweep.
 */

#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define f first
#define s second

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);

    int n; ll A, B; cin >> n >> A >> B;

    ll tmp = (B+1)%A;
    ll period = (A/__gcd(tmp,A))*B;
    if (tmp == 0) period = B;
    assert(period > 0);
    cerr << "Period is " << period << endl;

    map<ll, int> ct;
    ct[period] = 0;
    for (int i = 0; i < n; i++) {
        ll L, R; cin >> L >> R;
        ll Lm = L%period, Rm = R%period;
        ll Ld = L/period, Rd = R/period;

        if (Rd > Ld) {
            if (Rd == Ld + 1 && Rm < Lm) {
                ct[0]++;
                ct[Rm+1]--;
                ct[Lm]++;
            } else {
                cout << period << endl;
                return 0;
            }
        } else {
            assert(Lm<=Rm);
            ct[Lm]++;
            ct[Rm+1]--;
        }
    }

    ll ans = 0;
    int sum = 0;
    ll prv = 0;
    for (pair<ll, int> x : ct) {
        assert(sum >= 0);
        if (sum > 0) ans += x.f-prv;
        sum += x.s;
        prv = x.f;
        if (x.f >= period) {
            break;
        }
    }
    cout << ans << endl;

    return 0;
}
