#include <iostream>
#include <string>
#include <utility>
#include <sstream>
#include <algorithm>
#include <stack>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <bitset>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <unordered_set>

using namespace std;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define INF 1000000000
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define pb push_back
#define PI acos(-1.0)
#define ll long long
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int main() {
    freopen("cowjog.in", "r", stdin);
    freopen("cowjog.out", "w", stdout);

    int n; ll t; cin >> n >> t;
    pair<ll, ll> cows[n];
    F0R(i, n) {
        ll a, b; cin >> a >> b;
        cows[i].A = a; cows[i].B = b*t+a;
    }
    sort(cows, cows+n);
    reverse(cows, cows+n);

    int ans = 0;
    long long x = -1, y = LL_INF;
    /*
     * Consider two cows (A, B) and (X, Y)
     * Cow 1 goes from A -> B
     * Cow 2 goes from X -> Y
     * If A <= X and B >= Y, then cow (A, B) merges
     * with cow (X, Y) and can be ignored.
     */
    for (pair<ll, ll> cow : cows) {
        if (cow.A <= x && cow.B >= y) {
            continue;
        }
        ans++;
        x = cow.A; y = cow.B;
    }
    cout << ans << endl;

    return 0;
}
