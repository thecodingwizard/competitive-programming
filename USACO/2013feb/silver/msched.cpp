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

int n, m;
int cows[10001];
vi children[10001];
int result[100001];

int calcTime(int cow) {
    if (result[cow] != -1) return result[cow];
    result[cow] = cows[cow];
    for (int child : children[cow]) {
        result[cow] = max(result[cow], cows[cow] + calcTime(child));
    }
    return result[cow];
}

int main() {
    freopen("msched.in", "r", stdin);
    freopen("msched.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> cows[i];
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        children[a].push_back(b);
    }
    int ans = 0;
    memset(result, -1, sizeof result);
    for (int i = 1; i <= n; i++) {
        ans = max(ans, calcTime(i));
    }
    cout << ans << endl;
    return 0;
}
