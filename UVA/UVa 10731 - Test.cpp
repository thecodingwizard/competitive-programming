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

vi children[1000];
bool visited[1000];
int dfsNum[1000], dfsLow[1000], dfsCtr;
vector<vi> ans;
vector<int> S;

void tarjanSCC(int node) {
    dfsNum[node] = dfsLow[node] = dfsCtr++;
    visited[node] = true;
    S.pb(node);

    for (int child : children[node]) {
        if (dfsNum[child] == INF) tarjanSCC(child);
        if (visited[child]) dfsLow[node] = min(dfsLow[node], dfsLow[child]);
    }

    if (dfsNum[node] == dfsLow[node]) {
        vi toPush;
        while (true) {
            int next = S.back(); S.pop_back(); visited[next] = false;
            toPush.pb(next);
            if (next == node) break;
        }
        SORT(toPush);
        ans.pb(toPush);
    }
}

int main() {
    int n;
    bool firstCase = true;
    while (cin >> n && n) {
        dfsCtr = 0;
        SET(visited, false, 1000);
        SET(dfsNum, INF, 1000);
        SET(dfsLow, INF, 1000);
        F0R(i, 1000) children[i].clear();
        ans.clear();
        S.clear();

        F0R(i, n) {
            vector<int> line;
            F0R(j, 5) {
                char c; cin >> c;
                line.pb(c);
            }
            char ans; cin >> ans;
            for (int x : line) {
                if (x == ans) continue;
                children[ans].pb(x);
            }
        }

        FOR(i, 'A', 'Z'+1) {
            if (children[i].size() == 0) continue;
            if (dfsNum[i] == INF) tarjanSCC(i);
        }


        if (firstCase) firstCase = false;
        else cout << endl;

        SORT(ans);
        for (vi x : ans) {
            bool first = true;
            for (int y : x) {
                if (first) first = false;
                else cout << " ";
                cout << char(y);
            }
            cout << endl;
        }
    }

    return 0;
}
