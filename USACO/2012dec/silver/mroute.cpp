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

int n, m, x;
struct Pipe {
    int target;
    int l, c;
};
vector<Pipe> adjList[501];

int main() {
    freopen("mroute.in", "r", stdin);
    freopen("mroute.out", "w", stdout);

    cin >> n >> m >> x;
    vector<int> capacities;
    F0R(i, m) {
        int x, y, l, c; cin >> x >> y >> l >> c;
        adjList[x].push_back(Pipe{y, l, c});
        adjList[y].push_back(Pipe{x, l, c});
        capacities.push_back(c);
    }
    int dist[n+10];
    int ans = INF;
    for (int minC : capacities) {
        F0R(i, n+1) dist[i] = INF;
        dist[1] = 0;
        priority_queue<ii, vector<ii>, greater<ii>> pq; pq.push(mp(0, 1));
        while (!pq.empty()) {
            ii next = pq.top(); pq.pop();
            if (next.A > dist[next.B]);
            for (Pipe child : adjList[next.B]) {
                if (child.c < minC) continue;
                if (dist[child.target] > dist[next.B] + child.l) {
                    dist[child.target] = dist[next.B] + child.l;
                    pq.push(mp(dist[child.target], child.target));
                }
            }
        }
        ans = min(ans, dist[n]+(int)(x/minC));
    }
    cout << ans << endl;

    return 0;
}
