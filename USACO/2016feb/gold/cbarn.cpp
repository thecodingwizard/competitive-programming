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
    freopen("cbarn.in", "r", stdin);
    freopen("cbarn.out", "w", stdout);

    int n; cin >> n;
    int cows[n];
    F0R(i, n) cin >> cows[i];
    int maxPt = 0;
    F0R(i, n) {
        maxPt = max(maxPt - 1 + cows[i], 0);
    }
    F0R(i, n) {
        if (maxPt == 0) {
            rotate(cows, cows + i, cows + n);
            break;
        }
        maxPt = max(maxPt - 1 + cows[i], 0);
    }

    long long ans = 0;
    queue<int> q;
    F0R(i, n) {
        F0R(j, cows[i]) q.push(i);
        int target = q.front(); q.pop();
        ans += (i - target)*(i - target);
    }

    cout << ans << endl;

    return 0;
}
