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

using namespace std;

#define INF 1000000000
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define PI acos(-1.0)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int main() {
    freopen("taxi.in", "r", stdin);
    freopen("taxi.out", "w", stdout);
    int n, m; cin >> n >> m;
    long long ans = 0;
    vi startingPositions, endingPositions;
    startingPositions.push_back(0); endingPositions.push_back(m);
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        startingPositions.push_back(b);
        endingPositions.push_back(a);
        ans += abs(b - a);
    }
    sort(startingPositions.begin(), startingPositions.end());
    sort(endingPositions.begin(), endingPositions.end());
    for (int i = 0; i <= n; i++) {
        ans += abs(startingPositions[i] - endingPositions[i]);
    }
    cout << ans << endl;
    return 0;
}
