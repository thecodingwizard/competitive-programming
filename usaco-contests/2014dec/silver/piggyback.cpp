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
    freopen("piggyback.in", "r", stdin);
    freopen("piggyback.out", "w", stdout);

    int b, e, p, n, m; cin >> b >> e >> p >> n >> m;
    vi adjList[n+10];
    F0R(i, m) {
        int x, y; cin >> x >> y;
        adjList[x].push_back(y);
        adjList[y].push_back(x);
    }

    int bessie[n+10], elise[n+10], both[n+10];
    memset(bessie, -1, sizeof bessie);
    memset(elise, -1, sizeof elise);
    memset(both, -1, sizeof both);

    queue<ii> q; q.push(mp(1, 0));
    while (!q.empty()) {
        ii next = q.front(); q.pop();
        if (bessie[next.A] != -1) continue; // visited
        bessie[next.A] = next.B;
        for (int child : adjList[next.A]) {
            q.push(mp(child, next.B + b));
        }
    }
    q.push(mp(2, 0));
    while (!q.empty()) {
        ii next = q.front(); q.pop();
        if (elise[next.A] != -1) continue; // visited
        elise[next.A] = next.B;
        for (int child : adjList[next.A]) {
            q.push(mp(child, next.B + e));
        }
    }
    q.push(mp(n, 0));
    while (!q.empty()) {
        ii next = q.front(); q.pop();
        if (both[next.A] != -1) continue; // visited
        both[next.A] = next.B;
        for (int child : adjList[next.A]) {
            q.push(mp(child, next.B + p));
        }
    }

    int best = INF;

    FOR(i, 1, n+1) {
        best = min(best, bessie[i] + elise[i] + both[i]);
    }

    cout << best << endl;

    return 0;
}
