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

struct Event {
    int pos, startY, endY, id; bool isEnd;
    bool operator<(const Event &other) const {
        return pos < other.pos;
    }
};

int main() {
    freopen("painting.in", "r", stdin);
    freopen("painting.out", "w", stdout);

    int n; cin >> n;
    vector<Event> sweep;
    F0R(i, n) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        sweep.push_back(Event{a, b, d, i, false});
        sweep.push_back(Event{c, b, d, i, true});
    }
    set<pair<int, bool>> horizontalLines;
    bool toPaint[n+10]; memset(toPaint, false, sizeof toPaint);
    sort(sweep.begin(), sweep.end());

    int ans = 0;
    for (Event e : sweep) {
        if (e.isEnd) {
            if (toPaint[e.id]) {
                horizontalLines.erase(mp(e.startY, false));
                horizontalLines.erase(mp(e.endY, true));
            }
        } else {
            auto it = horizontalLines.lower_bound(mp(e.endY, true));
            if (it == horizontalLines.end() || !it->B) {
                horizontalLines.insert(mp(e.startY, false));
                horizontalLines.insert(mp(e.endY, true));
                toPaint[e.id] = true;
                ans++;
            }
        }
    }
    cout << ans << endl;

    return 0;
}
