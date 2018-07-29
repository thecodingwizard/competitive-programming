/*
ID: nathan.18
TASK: comehome
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
    freopen("comehome.in", "r", stdin);
    freopen("comehome.out", "w", stdout);

    int p; cin >> p;
    vii adjList[100];
    F0R(i, p) {
        char a, b; int d;
        cin >> a >> b >> d;
        adjList[a - 'A'].emplace_back(b - 'A', d);
        adjList[b - 'A'].emplace_back(a - 'A', d);
    }
    int dist[100];
    int minDist = INF; char minDistPasture;

    F0R(i, 100) dist[i] = INF;
    dist['Z' - 'A'] = 0;
    priority_queue<ii, vii, greater<ii>> pq; pq.push(mp(0, 'Z' - 'A'));
    while (!pq.empty()) {
        ii front = pq.top(); pq.pop();
        if (front.A > dist[front.B]) continue;
        for (ii child : adjList[front.B]) {
            if (dist[child.A] > front.A + child.B) {
                dist[child.A] = front.A + child.B;
                pq.push(mp(dist[child.A], child.A));
            }
        }
    }

    for (int c = 0; c < 'Z' - 'A'; c++) {
        if (dist[c] != INF && dist[c] < minDist) {
            minDist = dist[c];
            minDistPasture = (char) c + 'A';
        }
    }

    cout << minDistPasture << " " << minDist << endl;

    return 0;
}
