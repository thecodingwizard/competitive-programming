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
#include <list>

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

int bolts, nuts;
int match[1000];
bool visited[1000];
vi children[1000];

int augment(int u) {
    if (visited[u]) return 0;
    visited[u] = true;
    for (int child : children[u]) {
        if (match[child] == -1 || augment(match[child])) {
            match[child] = u; return 1;
        }
    }
    return 0;
}

int main() {
    int t; cin >> t;
    F0R1(caseNum, t) {
        cin >> bolts >> nuts;
        F0R(i, bolts) {
            children[i].clear();
            F0R(j, nuts) {
                int connected; cin >> connected;
                if (connected) children[i].pb(500+j);
            }
        }

        // MCBM with Greedy pre-processing (Max cardinality bipartite matching)
        int ans = 0;
        set<int> freeNodes;
        F0R(i, bolts) freeNodes.insert(i);
        SET(match, -1, 1000);
        F0R(i, bolts) {
            vi candidates;
            for (int v : children[i]) {  // O(V^2)
                if (match[v] == -1) candidates.pb(v);
            }
            if (candidates.size() > 0) {
                ans++;
                freeNodes.erase(i); // i is matched, no longer a free vertex
                int a = rand() % candidates.size();
                match[candidates[a]] = i;
            }
        }
        for (int i : freeNodes) {
            SET(visited, false, 1000);
            ans += augment(i);
        }

        cout << "Case " << caseNum << ": a maximum of " << ans << " nuts and bolts can be fitted together" << endl;
    }

    return 0;
}
