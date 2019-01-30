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

int p, t;
bool adjMatrix[1000][1000];
map<string, int> nameMap;
int sccCt = 0, dfsNum[1000], dfsLow[1000], dfsCtr;
bool visited[1000];
vi s;

void tarjanSCC(int node) {
    dfsNum[node] = dfsLow[node] = dfsCtr++;
    visited[node] = true;
    s.pb(node);

    F0R(i, p) {
        if (!adjMatrix[node][i]) continue;

        if (dfsNum[i] == INF) tarjanSCC(i);
        if (visited[i]) dfsLow[node] = min(dfsLow[node], dfsLow[i]);
    }

    if (dfsLow[node] == dfsNum[node]) {
        sccCt++;
        while (true) {
            int next = s.back(); s.pop_back(); visited[next] = false;
            if (next == node) break;
        }
    }
}

int main() {
    while (cin >> p >> t && (p || t)) {
        sccCt = 0;
        nameMap.clear();
        SET2D(adjMatrix, false, 1000, 1000);
        dfsCtr = 0;
        SET(dfsNum, INF, 1000);
        SET(dfsLow, INF, 1000);
        SET(visited, false, 1000);
        s.clear();

        F0R(i, p) {
            string a, b; cin >> a >> b;
            string name = a + b;
            nameMap.insert(mp(name, i));
        }

        F0R(i, t) {
            string a, b, c, d; cin >> a >> b >> c >> d;
            string name1 = a + b, name2 = c + d;
            adjMatrix[nameMap[name1]][nameMap[name2]] = true;
        }

        F0R(i, p) {
            if (dfsNum[i] == INF) tarjanSCC(i);
        }

        cout << sccCt << endl;
    }

    return 0;
}
