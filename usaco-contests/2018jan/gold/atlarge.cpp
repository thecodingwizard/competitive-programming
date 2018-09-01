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
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int n, k;
int distBes[100001], distFarmer[100001];
vi adjList[100001];
int ans = 0;

void dfsBes(int node, int parent, int dist) {
    distBes[node] = dist;
    for (int child : adjList[node]) {
        if (child == parent) continue;
        dfsBes(child, node, dist+1);
    }
}

void dfsAns(int node, int parent) {
    if (distBes[node] >= distFarmer[node] && distBes[parent] < distFarmer[parent]) {
        ans++;
    }
    for (int child : adjList[node]) {
        if (child != parent) dfsAns(child, node);
    }
}

int main() {
    freopen("atlarge.in", "r", stdin);
    freopen("atlarge.out", "w", stdout);

    cin >> n >> k;
    F0R(i, n-1) {
        int x, y; cin >> x >> y;
        adjList[x].push_back(y);
        adjList[y].push_back(x);
    }
    dfsBes(k, -1, 0);
    queue<int> q;
    FOR(i, 1, n+1) {
        if (adjList[i].size() == 1) {
            q.push(i);
            distFarmer[i] = 0;
        } else {
            distFarmer[i] = INF;
        }
    }

    while (!q.empty()) {
        int next = q.front(); q.pop();
        for (int child : adjList[next]) {
            if (distFarmer[child] == INF) {
                distFarmer[child] = distFarmer[next] + 1;
                q.push(child);
            }
        }
    }

    dfsAns(k, -1);
    cout << ans << endl;

    return 0;
}
