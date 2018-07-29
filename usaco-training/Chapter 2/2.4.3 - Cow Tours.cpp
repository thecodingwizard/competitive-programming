/*
ID: nathan.18
TASK: cowtour
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
bool adjMatrix[150][150], visited[150];
ii pastures[150];
int groupId[150];
double maxDiameter[150];
double groupMaxDiameter[150];
int groups = 0;

void assignGroupId(int node, int id) {
    if (visited[node]) return; visited[node] = true;
    groupId[node] = id;
    F0R(i, n) if (adjMatrix[node][i]) assignGroupId(i, id);
}

double calcDist(int a, int b) {
    ii i = pastures[a], j = pastures[b];
    return sqrt((j.A-i.A)*(j.A-i.A)+(j.B-i.B)*(j.B-i.B));
}

double calcMaxDiameter(int node) {
    double dist[150]; F0R(i, 150) dist[i] = INF;
    dist[node] = 0;
    double maxD = 0;
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    pq.push(mp(0, node));
    while (!pq.empty()) {
        pair<double, int> front = pq.top(); pq.pop();
        if (front.A > dist[front.B]) continue;
        maxD = max(maxD, front.A);
        F0R(i, n) {
            if (i == front.B || !adjMatrix[front.B][i]) continue;
            if (dist[front.B] + calcDist(i, front.B) < dist[i]) {
                dist[i] = dist[front.B] + calcDist(i, front.B);
                pq.push(mp(dist[i], i));
            }
        }
    }
    return maxD;
}

int main() {
    freopen("cowtour.in", "r", stdin);
    freopen("cowtour.out", "w", stdout);

    cin >> n;
    F0R(i, n) cin >> pastures[i].A >> pastures[i].B;
    F0R(i, n) F0R(j, n) { char c; cin >> c; adjMatrix[i][j] = c == '1'; }
    memset(visited, false, sizeof visited);
    F0R(i, n) {
        if (!visited[i]) assignGroupId(i, groups++);
    }
    memset(groupMaxDiameter, 0, sizeof groupMaxDiameter);
    F0R(i, n) {
        double diameter = calcMaxDiameter(i);
        maxDiameter[i] = diameter;
        groupMaxDiameter[groupId[i]] = max(groupMaxDiameter[groupId[i]], diameter);
    }

    double ans = INF;
    F0R(i, n) F0R(j, n) {
        if (groupId[i] == groupId[j]) continue;
        ans = min(ans, max(max(groupMaxDiameter[groupId[i]], groupMaxDiameter[groupId[j]]), maxDiameter[i] + calcDist(i, j) + maxDiameter[j]));
    }
    printf("%0.6f\n", ans);

    return 0;
}
