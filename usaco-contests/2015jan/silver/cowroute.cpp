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

int a, b, n;
int cost[1010][1010], flightCt[1010][1010];
long long dist[1010], minFlights[1010];

int main() {
    freopen("cowroute.in", "r", stdin);
    freopen("cowroute.out", "w", stdout);

    F0R(i, 1010) F0R(j, 1010) cost[i][j] = flightCt[i][j] = INF;

    cin >> a >> b >> n;
    F0R(i, n) {
        int c, cities; cin >> c >> cities;
        vi toUpdate;
        F0R(j, cities) {
            int city; cin >> city;
            cost[city][city] = 0;
            flightCt[city][city] = 0;
            F0R(k, toUpdate.size()) {
                int x = toUpdate[k];
                if (c < cost[x][city]) {
                    cost[x][city] = c;
                    flightCt[x][city] = j - k;
                } else if (c == cost[x][city] && flightCt[x][city] > j - k) {
                    flightCt[x][city] = j - k;
                }
            }
            toUpdate.push_back(city);
        }
    }

    priority_queue<pair<pair<ll, ll>, int>, vector<pair<pair<ll, ll>, int>>, greater<pair<pair<ll, ll>, int>>> pq;
    pq.push(mp(mp(0, 0), a));

    F0R(i, 1010) { dist[i] = LL_INF; minFlights[i] = LL_INF; }
    dist[a] = 0; minFlights[a] = 0;

    while (!pq.empty()) {
        pair<pair<ll, ll>, int> next = pq.top(); pq.pop();
        if (next.A.A > dist[next.B]) continue;
        if (next.B == b) {
            cout << next.A.A << " " << next.A.B << endl;
            return 0;
        }
        F0R(i, 1001) {
            if (cost[next.B][i] == INF) continue;
            if (cost[next.B][i] + next.A.A < dist[i]) {
                dist[i] = cost[next.B][i] + next.A.A;
                minFlights[i] = minFlights[next.B] + flightCt[next.B][i];
                pq.push(mp(mp(dist[i], minFlights[i]), i));
            } else if (cost[next.B][i] + next.A.A == dist[i] && minFlights[next.B] + flightCt[next.B][i] < minFlights[i]) {
                minFlights[i] = minFlights[next.B] + flightCt[next.B][i];
                pq.push(mp(mp(dist[i], minFlights[i]), i));
            }
        }
    }

    cout << "-1 -1" << endl;

    return 0;
}
