/*
ID: nathan.18
TASK: fact4
LANG: C++11
*/

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
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

/* Cheap solution, actual solution: count number of twos and fives */
int main() {
    freopen("fact4.in", "r", stdin);
    freopen("fact4.out", "w", stdout);

    int n; cin >> n;
    ll ans = 1;
    ll inf = LL_INF/5000;
    FOR(i, 1, n+1) {
        ans *= i;
        while (ans % 10 == 0) ans /= 10;
        while (ans > inf) ans -= inf;
    }
    cout << ans % 10 << endl;

    return 0;
}
