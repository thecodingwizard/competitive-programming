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

class UnionFind {
private:
    vi p, rank, setSize;
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
            if (rank[x] > rank[y]) { p[y] = x; setSize[x] += setSize[y]; }
            else                   { p[x] = y; setSize[y] += setSize[x];
                if (rank[x] == rank[y]) rank[y]++; } } }
    int numDisjointSets() { return numSets; }
    int sizeOfSet(int i) { return setSize[findSet(i)]; }
};

int main() {
    freopen("mootube.in", "r", stdin);
    freopen("mootube.out", "w", stdout);

    int n, q; cin >> n >> q;
    vector<pair<int, ii>> edges;
    F0R(i, n-1) {
        int pi, qi, ri; cin >> pi >> qi >> ri;
        edges.push_back(mp(ri, mp(pi, qi)));
    }
    vector<pair<ii, int>> queries;
    int ans[q];
    F0R(i, q) {
        int a, b; cin >> a >> b;
        queries.push_back(mp(mp(a, b), i));
    }
    SORT(edges);
    reverse(edges.begin(), edges.end());
    SORT(queries);
    reverse(queries.begin(), queries.end());

    UnionFind UF(n+10);
    int idx = 0;
    for (pair<ii, int> q : queries) {
        while (idx < n-1 && edges[idx].A >= q.A.A) {
            UF.unionSet(edges[idx].B.A, edges[idx].B.B);
            idx++;
        }
        ans[q.B] = UF.sizeOfSet(q.A.B) - 1;
    }

    F0R(i, q) cout << ans[i] << endl;

    return 0;
}
