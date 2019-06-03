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

set<string> visited, nodes;
map<string, vector<string>> words;
map<string, int> dfsNum, dfsLow;
vector<string> S;
set<string> ans;
int dfsCtr;

void tarjanSCC(string node) {
    dfsLow[node] = dfsNum[node] = dfsCtr++;
    visited.insert(node);
    S.pb(node);

    for (string child : words[node]) {
        if (dfsNum.count(child) == 0) tarjanSCC(child);
        if (visited.count(child) > 0) dfsLow[node] = min(dfsLow[node], dfsLow[child]);
    }

    if (dfsLow[node] == dfsNum[node]) {
        vector<string> scc;
        while (true) {
            string v = S.back(); S.pop_back(); visited.erase(v);
            scc.pb(v);
            if (v == node) break;
        }
        if (scc.size() > 1) {
            for (string s : scc) ans.insert(s);
        }
    }
}

set<string> visited2;
void dfs(string s) {
    if (visited2.count(s) > 0) return;
    visited2.insert(s);
    ans.insert(s);
    for (string child : words[s]) {
        dfs(child);
    }
}

int main() {
    int n;
    while (cin >> n && n) {
        S.clear();
        dfsCtr = 0;
        visited.clear();
        visited2.clear();
        nodes.clear();
        words.clear();
        dfsNum.clear();
        dfsLow.clear();
        ans.clear();
        cin.ignore();
        F0R(i, n) {
            string line; getline(cin, line);
            stringstream ss; ss << line;
            string word; ss >> word;
            string def;
            nodes.insert(word);
            while (ss >> def) {
                words[word].pb(def);
            }
        }

        for (string s : nodes) {
            if (dfsNum.count(s) == 0) tarjanSCC(s);
        }

        for (string s : ans) {
            dfs(s);
        }

        cout << ans.size() << endl;
        bool first = true;
        for (string s : ans) {
            if (first) first = false;
            else cout << " ";
            cout << s;
        }
        cout << endl;
    }

    return 0;
}
