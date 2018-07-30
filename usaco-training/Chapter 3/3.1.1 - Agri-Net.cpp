/*
ID: nathan.18
TASK: agrinet
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

int n;
vii adjList[110];
bool visited[110];
priority_queue<ii> pq;

void process(int node) {
    visited[node] = true;
    for (ii child : adjList[node]) {
        if (!visited[child.B]) pq.push(child);
    }
}

int main() {
    freopen("agrinet.in", "r", stdin);
    freopen("agrinet.out", "w", stdout);

    cin >> n;
    F0R(i, n) F0R(j, n) {
            int cost; cin >> cost;
            adjList[i].push_back(mp(cost != 0 ? -cost : INF, j));
        }
    memset(visited, false, sizeof visited);
    int ans = 0;
    process(0);
    while (!pq.empty()) {
        ii front = pq.top(); pq.pop();
        if (!visited[front.B]) {
            ans += -front.A;
            process(front.B);
        }
    }
    cout << ans << endl;

    return 0;
}
