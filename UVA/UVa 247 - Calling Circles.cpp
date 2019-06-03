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
set<string> nodes, visited;
map<string, vector<string>> children;
map<string, int> dfsLow, dfsNum;
int dfsCtr;
vector<string> s;
vector<vector<string>> ans;

void tarjanSCC(string node) {
    dfsLow[node] = dfsNum[node] = dfsCtr++;
    visited.insert(node);
    s.pb(node);

    for (string child : children[node]) {
        if (dfsNum.count(child) == 0) tarjanSCC(child);
        if (visited.count(child)) {
            dfsLow[node] = min(dfsLow[node], dfsLow[child]);
        }
    }

    if (dfsLow[node] == dfsNum[node]) {
        vector<string> scc;
        while (true) {
            string v = s.back(); s.pop_back(); visited.erase(v);
            scc.pb(v);
            if (node == v) break;
        }
        ans.pb(scc);
    }
}

int main() {
    int caseNum = 1;
    while (cin >> n >> m && (n || m)) {
        nodes.clear();
        children.clear();
        dfsCtr = 0;
        dfsLow.clear();
        dfsNum.clear();
        visited.clear();
        s.clear();
        ans.clear();
        F0R(i, m) {
            string a, b; cin >> a >> b;
            nodes.insert(a);
            nodes.insert(b);
            children[a].pb(b);
        }

        for (string s : nodes) {
            if (dfsNum.count(s) == 0) tarjanSCC(s);
        }

        if (caseNum != 1) cout << endl;
        cout << "Calling circles for data set " << caseNum++ << ":" << endl;
        for (vector<string> scc : ans) {
            bool first = true;
            for (string s : scc) {
                if (first) first = false;
                else cout << ", ";
                cout << s;
            }
            cout << endl;
        }
    }

    return 0;
}
