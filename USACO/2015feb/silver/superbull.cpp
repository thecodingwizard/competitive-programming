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
    freopen("superbull.in", "r", stdin);
    freopen("superbull.out", "w", stdout);

    int n; cin >> n;
    int teams[n];
    F0R(i, n) cin >> teams[i];
    bool taken[n]; F0R(i, n) taken[i] = false;
    int dist[n]; F0R(i, n) dist[i] = 0;
    long long ans = 0;

    F0R(i, n) {
        int best = -1;
        F0R(j, n) {
            if (taken[j]) continue;
            if (best == -1 || dist[best] < dist[j]) {
                best = j;
            }
        }

        if (best == -1) continue;

        ans += dist[best];
        taken[best] = true;

        F0R(j, n) {
            dist[j] = max(dist[j], teams[best] ^ teams[j]);
        }
    }

    cout << ans << endl;

    return 0;
}
