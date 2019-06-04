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
#define SORT(vec) sort(vec.begin(), vec.end())

#define INF 1000000010
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define pb push_back
#define PI acos(-1.0)
#define ll long long
#define MOD (int)(2e+9+11)
#define SET(vec, val, size) for (int i = 0; i < size; i++) vec[i] = val;
#define SET2D(arr, val, dim1, dim2) F0R(i, dim1) F0R(j, dim2) arr[i][j] = val;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vl;

int main() {
    freopen("fencedin.in", "r", stdin);
    freopen("fencedin.out", "w", stdout);

    int a, b, n, m; cin >> a >> b >> n >> m;
    int VA[n+1], HA[m+1];
    VA[0] = HA[0] = 0;
    FOR(i, 1, n+1) cin >> VA[i];
    FOR(i, 1, m+1) cin >> HA[i];
    sort(VA, VA+n+1);
    sort(HA, HA+m+1);

    F0R(i, n) VA[i] = VA[i + 1] - VA[i];
    F0R(i, m) HA[i] = HA[i + 1] - HA[i];
    VA[n] = b - VA[n];
    HA[m] = a - HA[m];
    sort(VA, VA+n+1);
    sort(HA, HA+m+1);

    ll ans = (ll)(m)*VA[0] + (ll)(n)*HA[0];
    int vIdx = 1, hIdx = 1;
    while (vIdx <= n && hIdx <= m) {
        if (VA[vIdx] < HA[hIdx]) {
            ans += (ll)VA[vIdx++]*(m-hIdx+1);
        } else {
            ans += (ll)HA[hIdx++]*(n-vIdx+1);
        }
    }
    cout << ans << endl;

    return 0;
}
