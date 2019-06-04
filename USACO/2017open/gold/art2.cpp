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
    freopen("art2.in", "r", stdin);
    freopen("art2.out", "w", stdout);

    int n; cin >> n;
    int colors[n];
    int start[n+10], end[n+10];
    memset(start, -1, sizeof start);
    set<int> allColors;
    F0R(i, n) {
        cin >> colors[i];
        if (colors[i] == 0) continue;
        allColors.insert(colors[i]);
        if (start[colors[i]] == -1) start[colors[i]] = i;
        end[colors[i]] = i;
    }
    vector<pair<int, pair<bool, int>>> events;
    for (int x : allColors) events.push_back(mp(start[x], mp(false, x)));
    for (int x : allColors) events.push_back(mp(end[x], mp(true, x)));
    SORT(events);
    int ans = 0;
    int depth = 0;
    stack<int> s;
    for (pair<int, pair<bool, int>> ev : events) {
        if (ev.B.A) {
            depth--;
            if (s.top() != ev.B.B) {
                cout << "-1" << endl;
                return 0;
            }
            s.pop();
        } else {
            depth++;
            s.push(ev.B.B);
        }
        ans = max(ans, depth);
    }
    cout << ans << endl;

    return 0;
}
