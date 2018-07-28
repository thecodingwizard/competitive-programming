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
    freopen("cruise.in", "r", stdin);
    freopen("cruise.out", "w", stdout);

    int n, m, k; cin >> n >> m >> k;
    int left[n+1], right[n+1]; F0R(i, n) cin >> left[i+1] >> right[i+1];
    // true = left, false = right
    bool steps[m]; F0R(i, m) { char c; cin >> c; steps[i] = c == 'L'; }

    // port, index
    map<int, int> seen;
    vector<int> portOrder;
    int idx = 0, curPort = 1;
    while (seen.count(curPort) == 0) {
        seen[curPort] = idx++;
        portOrder.push_back(curPort);
        F0R(i, m) {
            if (steps[i]) curPort = left[curPort];
            else curPort = right[curPort];
        }
    }
    int mod = idx - seen[curPort];
    int adjustedIndex = (k - seen[curPort] + mod) % mod;
    cout << portOrder[seen[curPort] + adjustedIndex] << endl;

    return 0;
}
