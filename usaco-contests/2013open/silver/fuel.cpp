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
    freopen("fuel.in", "r", stdin);
    freopen("fuel.out", "w", stdout);

    int n, g, b, d; cin >> n >> g >> b >> d;
    pair<ll, ll> stations[n+1]; F0R(i, n) cin >> stations[i].B >> stations[i].A;
    sort(stations, stations+n, [](pair<ll, ll> a, pair<ll, ll> b) { return a.B < b.B; });
    stations[n] = mp(-LL_INF, d);

    ll ans = 0;
    ll curPos = 0;
    ll curTank = b;
    ll maxPos = b;
    ll curCost = 0;

    set<pair<ll, ll>> reachable;
    for (pair<ll, ll> station : stations) {
        while (station.B > maxPos) {
            if (reachable.size() == 0) {
                cout << "-1" << endl;
                return 0;
            }
            auto it = reachable.begin();
            pair<ll, ll> cheapest;
            while (curPos != 0 && it->B <= curPos) {
                reachable.erase(it);
                if (reachable.size() == 0) {
                    cout << "-1" << endl;
                    return 0;
                }
                it = reachable.begin();
            }
            cheapest = *it;
            if (curPos == 0) {
                curTank -= (cheapest.B - curPos);
            } else {
                ans += (g-curTank)*curCost;
                curTank = g-(cheapest.B - curPos);
            }
            curPos = cheapest.B;
            maxPos = cheapest.B + g;
            curCost = cheapest.A;
            reachable.erase(reachable.begin());
        }
        reachable.insert(station);
        if (station.A == -INF) {
            ans += (station.B - curPos - curTank)*curCost;
        } else {
            if (station.A <= curCost) {
                ans += max(0LL, (station.B - curPos - curTank))*curCost;
                curTank = max(0LL, curTank - (station.B - curPos));
                curPos = station.B;
                maxPos = station.B + g;
                curCost = station.A;
            }
        }
    }

    cout << ans << endl;

    return 0;
}
