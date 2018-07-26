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

struct Move {
    int steps; bool goingRight;
};

int main() {
    freopen("paint.in", "r", stdin);
    freopen("paint.out", "w", stdout);

    int n, k; cin >> n >> k;
    Move moves[n];
    vector<int> positions;
    int curPos = 0;
    F0R(i, n) {
        int a; char c; cin >> a >> c;
        moves[i].steps = a; moves[i].goingRight = c == 'R';
        if (moves[i].goingRight) curPos += a;
        else curPos -= a;
        positions.push_back(curPos);
    }
    positions.push_back(0);
    sort(positions.begin(), positions.end());
    map<int, int> compression, reverseCompression; int ctr = 0;
    for (int pos : positions) {
        if (compression.count(pos)) continue;
        compression[pos] = ctr;
        reverseCompression[ctr] = pos;
        ctr++;
    }
    int delta[ctr]; memset(delta, 0, sizeof delta);
    curPos = 0;
    for (Move move : moves) {
        if (move.goingRight) {
            delta[compression[curPos]]++;
            curPos += move.steps;
            delta[compression[curPos]]--;
        } else {
            delta[compression[curPos]]--;
            curPos -= move.steps;
            delta[compression[curPos]]++;
        }
    }
    int ans = 0;
    int curDelta = 0;
    for (int i = 0; i < ctr; i++) {
        curDelta += delta[i];
        if (curDelta >= k && i+1 < ctr) {
            ans += reverseCompression[i+1] - reverseCompression[i];
        }
    }
    cout << ans << endl;

    return 0;
}
