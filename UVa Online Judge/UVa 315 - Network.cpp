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
vi children[100];
int dfsLow[100], dfsNum[100], dfsParent[100], dfsNumberCounter, rootChildren, dfsRoot;
bool articulationPoint[100];

void dfs(int node) {
    dfsLow[node] = dfsNum[node] = dfsNumberCounter++;
    for (int child : children[node]) {
        if (dfsNum[child] == INF) {
            dfsParent[child] = node;
            if (node == dfsRoot) rootChildren++;
            dfs(child);

            if (dfsLow[child] >= dfsNum[node]) {
                articulationPoint[node] = true;
            }
            dfsLow[node] = min(dfsLow[node], dfsLow[child]);
        } else if (dfsParent[node] != child) {
            dfsLow[node] = min(dfsLow[node], dfsNum[child]);
        }
    }
}

int main() {
    while (cin >> n && n) {
        F0R(i, n) children[i].clear();
        SET(dfsLow, INF, 100);
        SET(dfsNum, INF, 100);
        SET(dfsParent, -1, 100);
        dfsNumberCounter = 0;
        rootChildren = 0;
        SET(articulationPoint, false, 100);

        int node;
        while (cin >> node && node) {
            --node;
            string s; getline(cin, s);
            stringstream ss; ss << s;
            int child;
            while (ss >> child) {
                --child;
                children[node].pb(child);
                children[child].pb(node);
            }
        }

        F0R(i, n) {
            if (dfsNum[i] == INF) {
                dfsRoot = i; rootChildren = 0;
                dfs(i);
                articulationPoint[i] = (rootChildren > 1);
            }
        }

        int ans = 0;
        F0R(i, n) ans += articulationPoint[i];
        cout << ans << endl;
    }

    return 0;
}