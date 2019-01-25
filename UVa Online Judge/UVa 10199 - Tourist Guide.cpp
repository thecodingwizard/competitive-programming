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

int n;
set<string> nodes;
map<string, vector<string>> children;
string root;
int rootChildren = 0, dfsCtr;
map<string, int> dfsLow, dfsNum;
set<string> articulationPoints;

void dfs(string node, string parent) {
    dfsLow[node] = dfsNum[node] = dfsCtr++;
    for (string child : children[node]) {
        if (dfsNum.count(child) == 0) {
            dfs(child, node);

            if (root == node) rootChildren++;

            if (dfsLow[child] >= dfsNum[node]) {
                articulationPoints.insert(node);
            }

            dfsLow[node] = min(dfsLow[node], dfsLow[child]);
        } else if (child != parent) {
            dfsLow[node] = min(dfsLow[node], dfsNum[child]);
        }
    }
}

int main() {
    int caseNum = 1;
    bool first = true;
    while (cin >> n && n) {
        nodes.clear();
        dfsLow.clear();
        dfsNum.clear();
        children.clear();
        articulationPoints.clear();
        dfsCtr = 0;
        F0R(i, n) {
            string s; cin >> s;
            nodes.insert(s);
        }
        int m; cin >> m;
        F0R(i, m) {
            string a, b; cin >> a >> b;
            children[a].pb(b);
            children[b].pb(a);
        }
        for (string s : nodes) {
            if (dfsNum.count(s) > 0) continue;
            root = s;
            rootChildren = 0;
            dfs(root, "");
            if (rootChildren > 1) articulationPoints.insert(root);
            else articulationPoints.erase(root);
        }
        if (first) first = false;
        else cout << endl;
        cout << "City map #" << caseNum++ << ": " << articulationPoints.size() << " camera(s) found" << endl;
        for (string s : articulationPoints) {
            cout << s << endl;
        }
    }

    return 0;
}
