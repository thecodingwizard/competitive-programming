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
#define F0R1(i, a) for (int i=1; i<=(a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
#define F0Rd1(i, a) for (int i=a; i>0; i--)
#define SORT(vec) sort(vec.begin(), vec.end())

#define INF 1000000010
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define pA first
#define pB second
#define mp make_pair
#define pb push_back
#define PI acos(-1.0)
#define ll long long
#define MOD (int)(2e+9+11)
#define SET(vec, val, size) for (int i = 0; i < size; i++) vec[i] = val;
#define SET2D(arr, val, dim1, dim2) F0R(i, dim1) F0R(j, dim2) arr[i][j] = val;
#define SET3D(arr, val, dim1, dim2, dim3) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) arr[i][j][k] = val;
#define SET4D(arr, val, dim1, dim2, dim3, dim4) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) F0R(l, dim4) arr[i][j][k][l] = val;
#define READGRID(arr, dim) F0R(i, dim) F0R(j, dim) cin >> arr[i][j];
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<ll> vl;

void setupIO(const string &PROB) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream infile(PROB + ".in");
    if (infile.good()) {
        freopen((PROB + ".in").c_str(), "r", stdin);
        freopen((PROB + ".out").c_str(), "w", stdout);
    }
}

/* ============================ */

int n, m;
vi children[10000];
int dfsNum[10000], dfsLow[10000], dfsCtr, root, rootChildren, score[10000];

void dfs(int node, int parent) {
    dfsNum[node] = dfsLow[node] = dfsCtr++;
    for (int child : children[node]) {
        if (dfsNum[child] == INF) {
            dfs(child, node);

            if (node == root) rootChildren++;

            if (dfsLow[child] >= dfsNum[node]) score[node]++;
            dfsLow[node] = min(dfsLow[node], dfsLow[child]);
        } else if (child != parent) {
            dfsLow[node] = min(dfsLow[node], dfsNum[child]);
        }
    }
}

int main() {

    while (cin >> n >> m && (n || m)) {
        int a, b;
        F0R(i, n) children[i].clear();
        SET(dfsNum, INF, 10000);
        SET(dfsLow, INF, 10000);
        dfsCtr = 0;
        rootChildren = 0;
        while (cin >> a >> b && !(a == -1 && b == -1)) {
            children[a].pb(b);
            children[b].pb(a);
        }
        root = 0;
        dfs(0, -1);
        score[0] = rootChildren - 1;

        auto cmp = [](ii a, ii b) {
            if (a.pB == b.pB) return a.pA < b.pA;
            else return a.pB > b.pB;
        };
        set<ii, decltype(cmp)> ans(cmp);
        F0R(i, n) {
            ans.insert(mp(i, score[i]+1));
        }

        int ctr = 0;
        for (ii x : ans) {
            cout << x.pA << " " << x.pB << endl;
            if (++ctr == m) break;
        }
        cout << endl;
    }

    return 0;
}
