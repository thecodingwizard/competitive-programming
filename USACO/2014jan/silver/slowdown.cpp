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
    freopen("slowdown.in", "r", stdin);
    freopen("slowdown.out", "w", stdout);

    int n; cin >> n;
    vi timeSlowdown, distSlowdown;
    F0R(i, n) {
        char c; int x; cin >> c >> x;
        if (c == 'T') timeSlowdown.push_back(x);
        else distSlowdown.push_back(x);
    }
    sort(timeSlowdown.begin(), timeSlowdown.end());
    sort(distSlowdown.begin(), distSlowdown.end());
    reverse(timeSlowdown.begin(), timeSlowdown.end());
    reverse(distSlowdown.begin(), distSlowdown.end());

    double curTime = 0, curDist = 0;
    int curSpeedDenom = 1;
    while (!(timeSlowdown.empty() && distSlowdown.empty())) {
        double nextTime = INF, nextDist = INF;
        if (!timeSlowdown.empty()) {
            nextTime = timeSlowdown.back();
        }
        if (!distSlowdown.empty()) {
            nextDist = distSlowdown.back();
        }
        nextTime = (nextTime-curTime)*(1.0/curSpeedDenom)+curDist;
        if (nextTime < nextDist) {
            curTime = timeSlowdown.back();
            curDist = nextTime;
            timeSlowdown.pop_back();
        } else {
            curTime += (nextDist-curDist)/(1.0/curSpeedDenom);
            curDist = nextDist;
            distSlowdown.pop_back();
        }
        curSpeedDenom++;
    }
    curTime += (1000.0-curDist)/(1.0/curSpeedDenom);
    cout << (int)round(curTime) << endl;

    return 0;
}
