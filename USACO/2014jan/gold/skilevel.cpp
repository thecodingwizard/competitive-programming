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
#include <math.h>
#include <assert.h>

using namespace std;

#define INF 1000000000
#define LL_INF 0xfffffffffffffffLL
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define PI acos(-1.0)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

// Union-Find Disjoint Sets Library written in OOP manner, using both path compression and union by rank heuristics
class UnionFind {                                              // OOP style
private:
    vi p, rank, setSize;                       // remember: vi is vector<int>
    int numSets;
public:
    UnionFind(int N) {
        setSize.assign(N, 1); numSets = N; rank.assign(N, 0);
        p.assign(N, 0); for (int i = 0; i < N; i++) p[i] = i; }
    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
    void unionSet(int i, int j) {
        if (!isSameSet(i, j)) { numSets--;
            int x = findSet(i), y = findSet(j);
            // rank is used to keep the tree short
            if (rank[x] > rank[y]) { p[y] = x; setSize[x] += setSize[y]; }
            else                   { p[x] = y; setSize[y] += setSize[x];
                if (rank[x] == rank[y]) rank[y]++; } } }
    int numDisjointSets() { return numSets; }
    int sizeOfSet(int i) { return setSize[findSet(i)]; }
};

int m, n, t, elevations[501][501], minD[250001];
vii adjList[501][501];
bool visited[501][501];

struct Edge {
    ii first, second;
    int weight;
    Edge(ii _first, ii _second, int _weight) : first(std::move(_first)), second(std::move(_second)), weight(_weight) {}
};

bool howToSort(Edge a, Edge b) {
    return a.weight < b.weight;
}

int main() {
    freopen("skilevel.in", "r", stdin);
    freopen("skilevel.out", "w", stdout);

    cin >> m >> n >> t;
    for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) cin >> elevations[i][j];
    vector<Edge> edges;
    for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) {
        if (i + 1 < m) {
            edges.emplace_back(mp(i, j), mp(i + 1, j), abs(elevations[i + 1][j] - elevations[i][j]));
            assert(abs(elevations[i + 1][j] - elevations[i][j]) < 2*INF);
        }
        if (j + 1 < n) {
            edges.emplace_back(mp(i, j), mp(i, j + 1), abs(elevations[i][j + 1] - elevations[i][j]));
            assert(abs(elevations[i][j + 1] - elevations[i][j]) < 2*INF);
        }
    }
    sort(edges.begin(), edges.end(), howToSort);
    assert(edges.size() == 2*m*n-m-n);
    UnionFind UF(m*n+1);
    for (int &i : minD) {
        i = INF*2+10;
    }
    memset(visited, false, sizeof visited);
    for (Edge e : edges) {
        int node1 = e.first.A*n+e.first.B, node2 = e.second.A*n+e.second.B;
        if (!UF.isSameSet(node1, node2)) {
            adjList[e.first.A][e.first.B].push_back(e.second);
            adjList[e.second.A][e.second.B].push_back(e.first);
            UF.unionSet(node1, node2);
            if (UF.sizeOfSet(node1) >= t) {
                queue<ii> q; q.push(e.first); q.push(e.second);
                while (!q.empty()) {
                    ii node = q.front(); q.pop();
                    if (visited[node.A][node.B]) continue;
                    visited[node.A][node.B] = true;
                    for (ii child : adjList[node.A][node.B]) q.push(child);
                    minD[node.A*n+node.B] = min(e.weight, minD[node.A*n+node.B]);
                }
            }
        }
    }
    long long total = 0;
    for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) {
        int x; cin >> x;
        if (x == 1) total += minD[i*n+j];
    }
    cout << total << endl;
    return 0;
}