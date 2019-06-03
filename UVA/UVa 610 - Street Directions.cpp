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
vi children[1000];
int dfsNum[1000], dfsLow[1000], parent[1000], dfsCounter;
bool keep[1000][1000];

void dfs(int node) {
    dfsNum[node] = dfsLow[node] = dfsCounter++;
    F0R(child, n) {
        if (!keep[node][child]) continue;
        if (dfsNum[child] == INF) {
            parent[child] = node;
            dfs(child);

            if (dfsLow[child] <= dfsNum[node]) {
                keep[child][node] = false;
            }

            dfsLow[node] = min(dfsLow[child], dfsLow[node]);
        } else if (parent[node] != child) {
            dfsLow[node] = min(dfsLow[node], dfsNum[child]);
            keep[child][node] = false;
        }
    }
}

int main() {
    int caseNum = 1;
    while (cin >> n >> m && (n || m)) {
        F0R(i, 1000) children[i].clear();
        SET(dfsNum, INF, 1000);
        SET(dfsLow, INF, 1000);
        SET(parent, INF, 1000);
        SET2D(keep, false, 1000, 1000);
        dfsCounter = 1;
        F0R(i, m) {
            int a, b; cin >> a >> b;
            --a; --b;
            keep[a][b] = keep[b][a] = true;
            children[a].pb(b);
            children[b].pb(a);
        }
        dfs(0);

        cout << caseNum++ << endl << endl;
        F0R(i, n) {
            F0R(j, n) {
                if (keep[i][j]) {
                    cout << i+1 << " " << j+1 << endl;
                }
            }
        }
        cout << "#" << endl;
    }

    return 0;
}