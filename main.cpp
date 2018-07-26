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
    freopen("cardgame.in", "r", stdin);
    freopen("cardgame.out", "w", stdout);

    int n; cin >> n;
    bool taken[2*n+1]; memset(taken, false, sizeof taken);
    int elsie[n]; F0R(i, n) { cin >> elsie[i]; taken[elsie[i]] = true; }
    vi bessie; FOR(i, 1, 2*n+1) if (!taken[i]) bessie.push_back(i);
    sort(bessie.begin(), bessie.end()); reverse(bessie.begin(), bessie.end());

    int best = 0;
    for (int i = 0; i < n; i++) {
        int ans = 0;
        set<int> high, low;
        for (int x = 0; x < i; x++) high.insert(bessie[x]);
        for (int x = i; x < n; x++) low.insert(bessie[x]);
        for (int j = 0; j < n; j++) {
            int card = elsie[j];
            if (j >= i) {
                // low card wins
                auto it = low.lower_bound(card);
                if (it == low.begin()) continue;
                it--;
                low.erase(it);
                ans++;
            } else {
                // high card wins
                auto it = high.upper_bound(card);
                if (it == high.end()) continue;
                high.erase(it);
                ans++;
            }
        }
        best = max(best, ans);
    }
    cout << best << endl;

    return 0;
}
