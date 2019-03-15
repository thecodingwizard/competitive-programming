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


vi children[25];
int dist[25], n, m;

int run(int node) {
    SET(dist, INF, 25);
    dist[node] = 0;
    queue<int> q;
    q.push(node);
    int endNode = node;
    vi newChildren[25];
    while (!q.empty()) {
        int front = q.front(); q.pop();
        for (int child : children[front]) {
            if (dist[child] == INF) {
                dist[child] = dist[front] + 1;
                q.push(child);
                newChildren[child].pb(front);
                newChildren[front].pb(child);
                endNode = child;
            }
        }
    }
    q.push(endNode);
    SET(dist, INF, 25);
    dist[endNode] = 0;
    int ans = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int child : newChildren[u]) {
            if (dist[child] == INF) {
                dist[child] = dist[u] + 1;
                ans = dist[child];
                q.push(child);
            }
        }
    }
    cout << node << " " << endNode << " " << ans << endl;
    return ans;
}

int main() {
    int N; cin >> N;
    F0R1(caseNum, N) {
        cin >> n;
        cin >> m;
        F0R(i, n) children[i].clear();
        F0R(i, m) {
            int a, b; cin >> a >> b;
            children[a].pb(b);
            children[b].pb(a);
        }
        int best = INF;
        F0R(i, n) {
            MIN(best, run(i));
        }
        cout << "Case #" << caseNum << ":" << endl;
        cout << best << endl << endl;
    }

    return 0;
}
