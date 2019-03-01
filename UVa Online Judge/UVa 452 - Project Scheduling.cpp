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
#include <ctime>

using namespace std;

template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define F0R1(i, a) for (int i=1; i<=(a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
#define F0Rd1(i, a) for (int i=a; i>0; i--)
#define SORT(vec) sort(vec.begin(), vec.end())
#define MIN(a, b) a = min(a, b)
#define MAX(a, b) a = max(a, b)

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
#define all(x) (x).begin(), (x).end()

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
int A[1000];
int dist[1000];
bool visited[1000];

vi topoOrder;

void topoSort(int node) {
    visited[node] = true;
    for (int child : children[node]) {
        if (!visited[child]) topoSort(child);
    }
    topoOrder.pb(node);
}

int main() {
    int t; cin >> t; cin.ignore(); cin.ignore();
    F0R1(caseNum, t) {
        F0R(i, 1000) children[i].clear();
        SET(visited, false, 1000);
        SET(dist, 0, 1000);
        topoOrder.clear();

        vector<char> startNodes;
        vector<char> nodes;
        string line;
        while (getline(cin, line) && !line.empty()) {
            stringstream ss; ss << line;
            char x; ss >> x;
            nodes.pb(x);
            int t; ss >> t;
            char y;
            A[x] = t;
            bool start = true;
            while (ss >> y) {
                children[y].pb(x);
                start = false;
            }
            if (start) startNodes.pb(x);
        }

        for (char x : startNodes) {
            topoSort(x);
        }
        reverse(topoOrder.begin(), topoOrder.end());

        int ans = 0;
        for (int node : topoOrder) {
            dist[node] += A[node];
            for (int child : children[node]) {
                MAX(dist[child], dist[node]);
            }
            MAX(ans, dist[node]);
        }

        if (caseNum != 1) cout << endl;
        cout << ans << endl;
    }

    return 0;
}