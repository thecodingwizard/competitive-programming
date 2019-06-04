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
#define SET(vec, val, size) for (int i = 0; i < size; i++) vec[i] = val;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int main() {
    freopen("snowboots.in", "r", stdin);
    freopen("snowboots.out", "w", stdout);

    int n, b; cin >> n >> b;
    int next[n+10], prev[n+10];
    ii tiles[n];
    pair<ii, int> boots[b];
    F0R(i, n) {
        cin >> tiles[i].A;
        tiles[i].B = i;
    }
    F0R(i, b) {
        cin >> boots[i].A.A >> boots[i].A.B;
        boots[i].B = i;
    }
    sort(tiles, tiles+n);
    reverse(tiles, tiles+n);
    sort(boots, boots+b);
    reverse(boots, boots+b);
    int ans[b];

    F0R(i, n) {
        next[i] = i+1;
    }
    F0Rd(i, n) {
        prev[i] = i - 1;
    }

    int biggestGap = 1;
    int tilePtr = 0;
    for (pair<ii, int> boot : boots) {
        while (tilePtr < n && tiles[tilePtr].A > boot.A.A) {
            int idx = tiles[tilePtr].B;
            next[prev[idx]] = next[idx];
            prev[next[idx]] = prev[idx];
            biggestGap = max(biggestGap, next[idx] - prev[idx]);
            tilePtr++;
        }
        ans[boot.B] = boot.A.B >= biggestGap;
    }

    F0R(i, b) cout << ans[i] << endl;

    return 0;
}
