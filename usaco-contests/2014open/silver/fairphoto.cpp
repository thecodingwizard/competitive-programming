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
    freopen("fairphoto.in", "r", stdin);
    freopen("fairphoto.out", "w", stdout);

    int n; cin >> n;
    ii cows[n+10];
    F0R(i, n) {
        int pos; char c; cin >> pos >> c;
        cows[i].A = pos; cows[i].B = c == 'S' ? -1 : 1;
    }
    sort(cows, cows+n);

    int runningSum = 0;
    map<int, int> leftEndpoints; leftEndpoints.insert(mp(0, cows[0].A));
    int best = 0;

    F0R(i, n) {
        runningSum += cows[i].B;
        int toSearch;
        if (runningSum >= 0) {
            toSearch = runningSum % 2;
        } else {
            toSearch = runningSum;
        }
        if (leftEndpoints.count(toSearch) > 0) best = max(best, cows[i].A - leftEndpoints[toSearch]);
        if (leftEndpoints.count(-toSearch) > 0) best = max(best, cows[i].A - leftEndpoints[-toSearch]);
        if (leftEndpoints.count(toSearch) == 0) leftEndpoints.insert(mp(toSearch, i == n - 1 ? INF : cows[i+1].A));
        if (leftEndpoints.count(runningSum) == 0) leftEndpoints.insert(mp(runningSum, i == n - 1 ? INF : cows[i+1].A));
    }

    cout << best << endl;

    return 0;
}
