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
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int main() {
    freopen("hayfeast.in", "r", stdin);
    freopen("hayfeast.out", "w", stdout);

    ll n, m; cin >> n >> m;
    pair<ll, ll> haybales[n]; F0R(i, n) cin >> haybales[i].A >> haybales[i].B;

    multiset<ll> spices;
    ll curFlavor = 0;
    int i = 0, j = 0;
    ll ans = LL_INF;
    while (j <= n) {
        if (curFlavor < m) {
            spices.insert(haybales[j].B);
            curFlavor += haybales[j++].A;
            continue;
        }
        ans = min(ans, *spices.rbegin());
        spices.erase(spices.find(haybales[i].B));
        curFlavor -= haybales[i++].A;
    }
    cout << ans << endl;

    return 0;
}
