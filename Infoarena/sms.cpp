/*
 * Define ct[i] = expected number of keystrokes needed to type the i'th character.
 * ct[0] = 0.
 *
 * ct[i] = 1*p_correct + (2 + ct[i])*p_incorrect + (1 + ct[i-1] + ct[i])*p_backspace
 *
 * The first term, 1*p_correct: need to press one key if we press the right one.
 *
 * The second term: If we press an incorrect key, we immediately press backspace.
 * This costs two keystrokes. Now, we try again to press the right key, which takes
 * ct[i] keystrokes.
 *
 * The third term: If we press backspace, that's one key. Then, we have to re-type
 * the previous key, which takes ct[i-1] keystrokes. Then, we have to type this key,
 * which takes ct[i] keystrokes.
 *
 * We do some math to get an equation for ct[i] in terms of ct[i-1]. Then,
 * we just iterate through all n keys, calculating ct[i] for each, and then we
 * sum up ct[1] through ct[n].
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
#define ld long double

int main() {
    cin.tie(0)->sync_with_stdio(0);

    freopen("sms.in", "r", stdin);
    freopen("sms.out", "w", stdout);

    int n, k; cin >> n >> k;
    string s; cin >> s;
    ld C[k], I[k], B[k];
    F0R(x, k) {
        cin >> C[x] >> I[x] >> B[x];
    }
    ld p = 0;
    ld ans = 0;
    F0R(x, n) {
        ld c = C[s[x]-'a'], i = I[s[x]-'a'], b = B[s[x]-'a'];
        p = (c + 2*i + (1+p)*b)/(1-i-b);
        ans += p;
    }
    cout << fixed << setprecision(10);
    cout << ans << endl;

    return 0;
}
