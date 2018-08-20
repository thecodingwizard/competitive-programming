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
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int main() {
    freopen("split.in", "r", stdin);
    freopen("split.out", "w", stdout);

    ll n; cin >> n;
    ll minX = INF, minY = INF, maxX = -1, maxY = -1;
    vector<pair<ll, ll>> xVals, yVals;
    F0R(i, n) {
        ll x, y; cin >> x >> y;
        xVals.push_back(mp(x, y));
        yVals.push_back(mp(y, x));
        minX = min(minX, x);
        minY = min(minY, y);
        maxX = max(maxX, x);
        maxY = max(maxY, y);
    }
    ll oneEnclosure = (maxX-minX)*(maxY-minY);
    SORT(xVals);
    SORT(yVals);

    ll ans = 0;

    ll left = 0;
    ll right = oneEnclosure;
    ll sMaxY = -1, sMinY = INF;
    ll mult[n];
    FORd(i, 1, n) {
        sMaxY = max(sMaxY, xVals[i].B);
        sMinY = min(sMinY, xVals[i].B);
        mult[i] = sMaxY - sMinY;
    }
    sMaxY = -1, sMinY = INF;
    FOR(i, 1, n) {
        sMaxY = max(sMaxY, xVals[i-1].B);
        sMinY = min(sMinY, xVals[i-1].B);
        left = (sMaxY - sMinY)*(xVals[i-1].A-minX);
        right = (maxX - xVals[i].A)*mult[i];
        ans = max(ans, oneEnclosure - left - right);
    }

    ll up = 0;
    ll down = oneEnclosure;
    ll sMaxX = -1, sMinX = INF;
    FORd(i, 1, n) {
        sMaxX = max(sMaxX, yVals[i].B);
        sMinX = min(sMinX, yVals[i].B);
        mult[i] = sMaxX - sMinX;
    }
    sMaxX = -1, sMinX = INF;
    FOR(i, 1, n) {
        sMaxX = max(sMaxX, yVals[i-1].B);
        sMinX = min(sMinX, yVals[i-1].B);
        up = (sMaxX - sMinX)*(yVals[i-1].A-minY);
        down = (maxY - yVals[i].A)*mult[i];
        ans = max(ans, oneEnclosure - up - down);
    }

    cout << ans << endl;

    return 0;
}
