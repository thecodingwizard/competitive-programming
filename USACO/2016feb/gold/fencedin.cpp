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

class UnionFind {
private:
    vi p, rank, setSize;
public:
    UnionFind(int N) {
        setSize.assign(N, 1); rank.assign(N, 0);
        p.assign(N, 0); for (int i = 0; i < N; i++) p[i] = i; }
    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
    void unionSet(int i, int j) {
        if (!isSameSet(i, j)) {
            int x = findSet(i), y = findSet(j);
            // rank is used to keep the tree short
            if (rank[x] > rank[y]) { p[y] = x; setSize[x] += setSize[y]; }
            else                   { p[x] = y; setSize[y] += setSize[x];
                if (rank[x] == rank[y]) rank[y]++; } } }
};

int main() {
    freopen("fencedin.in", "r", stdin);
    freopen("fencedin.out", "w", stdout);

    int a, b, n, m; cin >> a >> b >> n >> m;
    int VA[n], HA[m];
    F0R(i, n) cin >> VA[i]; F0R(i, m) cin >> HA[i];
    sort(VA, VA+n); sort(HA, HA+m);
    vector<pair<int, pair<bool, int>>> lines;
    F0R(i, n) {
        lines.push_back(mp(VA[i] - (i-1>=0?VA[i-1]:0), mp(true, i)));
    }
    lines.push_back(mp(b-VA[n-1], mp(true, n)));
    F0R(i, m) {
        lines.push_back(mp(HA[i] - (i-1>=0?HA[i-1]:0), mp(false, i)));
    }
    lines.push_back(mp(a-HA[m-1], mp(false, m)));
    SORT(lines);

    UnionFind UF((n+1)*(m+1));
    long long cost = 0;
    for (pair<int, pair<bool, int>> line : lines) {
        if (line.B.A) {
            // vertical
            F0R(i, m) {
                int node1 = line.B.B*(m+1)+i;
                int node2 = node1 + 1;
                if (!UF.isSameSet(node1, node2)) {
                    UF.unionSet(node1, node2);
                    cost += line.A;
                }
            }
        } else {
            // horizontal
            F0R(i, n) {
                int node1 = i*(m+1)+line.B.B;
                int node2 = node1 + (m+1);
                if (!UF.isSameSet(node1, node2)) {
                    UF.unionSet(node1, node2);
                    cost += line.A;
                }
            }
        }
    }
    cout << cost << endl;

    return 0;
}
