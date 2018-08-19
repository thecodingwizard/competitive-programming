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

int n, k;
vi rooms;
ll memo[100][7];

ll solve(int pos, int doorsUsed) {
    if (doorsUsed > k) return INF;
    if (pos == n) return 0;
    if (doorsUsed == k) {
        ll sum = 0;
        FOR(i, pos, n) sum += (i-pos)*rooms[i];
        return sum;
    }
    if (memo[pos][doorsUsed] != -1) return memo[pos][doorsUsed];
    ll best = INF;
    ll cost = 0;
    FOR(i, pos + 1, n + 1) {
        cost += (i-pos-1)*rooms[i-1];
        best = min(best, solve(i, doorsUsed+1) + cost);
    }
    return memo[pos][doorsUsed] = best;
}

int main() {
    freopen("cbarn2.in", "r", stdin);
    freopen("cbarn2.out", "w", stdout);

    cin >> n >> k;
    F0R(i, n) {
        int x; cin >> x;
        rooms.push_back(x);
    }

    ll best = LL_INF;
    F0R(i, n) {
        rotate(rooms.begin(), rooms.begin()+1, rooms.end());
        F0R(j, 100) F0R(k, 7) memo[j][k] = -1;
        best = min(best, solve(0, 1));
    }
    cout << best << endl;

    return 0;
}
