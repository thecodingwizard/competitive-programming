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
    freopen("gpsduel.in", "r", stdin);
    freopen("gpsduel.out", "w", stdout);

    int n, m; cin >> n >> m;
    vi adjList[n+10]; vii adjList1[n+10], adjList2[n+10];
    F0R(i, m) {
        int a, b, p, q; cin >> a >> b >> p >> q;
        adjList[a].push_back(b);
        adjList1[b].push_back(mp(p, a));
        adjList2[b].push_back(mp(q, a));
    }
    int dist1[n+10], dist2[n+10], nextNode1[n+10], nextNode2[n+10];
    FOR(i, 1, n+1) dist1[i] = dist2[i] = nextNode1[i] = nextNode2[i] = INF;

    dist1[n] = dist2[n] = 0;
    priority_queue<ii, vii, greater<ii>> pq; pq.push(mp(0, n));
    while (!pq.empty()) {
        ii next = pq.top(); pq.pop();
        if (next.A > dist1[next.B]) continue;
        for (ii child : adjList1[next.B]) {
            if (dist1[child.B] > child.A + dist1[next.B]) {
                dist1[child.B] = child.A + dist1[next.B];
                nextNode1[child.B] = next.B;
                pq.push(mp(dist1[child.B], child.B));
            }
        }
    }

    pq.push(mp(0, n));
    while (!pq.empty()) {
        ii next = pq.top(); pq.pop();
        if (next.A > dist2[next.B]) continue;
        for (ii child : adjList2[next.B]) {
            if (dist2[child.B] > child.A + dist2[next.B]) {
                dist2[child.B] = child.A + dist2[next.B];
                nextNode2[child.B] = next.B;
                pq.push(mp(dist2[child.B], child.B));
            }
        }
    }

    int dist[n+10];
    FOR(i, 1, n+1) dist[i] = INF;
    dist[1] = 0;

    pq.push(mp(0, 1));
    while (!pq.empty()) {
        ii next = pq.top(); pq.pop();
        if (next.A > dist[next.B]) continue;
        for (int child : adjList[next.B]) {
            int cost = 0;
            if (nextNode1[next.B] != child) cost++;
            if (nextNode2[next.B] != child) cost++;
            if (dist[child] > cost + dist[next.B]) {
                dist[child] = cost + dist[next.B];
                pq.push(mp(dist[child], child));
            }
        }
    }

    cout << dist[n] << endl;

    return 0;
}
