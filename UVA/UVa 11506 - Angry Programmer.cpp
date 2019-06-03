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

int m, w, s, t, f;
int res[3000][3000], p[3000];
bool visited[3000];

void augment(int node, int minEdge) {
    if (node == s) {
        f = minEdge;
    } else if (p[node] != -1) {
        augment(p[node], min(minEdge, res[p[node]][node]));
        res[p[node]][node] -= f;
        res[node][p[node]] += f;
    }
}

int main() {
    while (cin >> m >> w && (m || w)) {
        s = 2, t = m*2;
        SET2D(res, 0, 3000, 3000);
        F0R(i, m - 2) {
            int n, c; cin >> n >> c;
            res[n*2][n*2+1] = c;
        }
        F0R(i, w) {
            int a, b, w;
            cin >> a >> b >> w;
            res[a * 2 + 1][b * 2] += w;
            res[b * 2 + 1][a * 2] += w;
        }
        res[s][s+1] = INF;
        res[t][t+1] = INF;

        int mf = 0;
        while (true) {
            f = 0;
            SET(p, -1, 3000);
            SET(visited, false, 3000);

            queue<int> q;
            q.push(s);
            visited[s] = true;
            while (!q.empty()) {
                int next = q.front(); q.pop();
                if (next == t+1) break;
                F0R(child, 2800) {
                    if (!visited[child] && res[next][child] > 0) {
                        p[child] = next;
                        visited[child] = true;
                        q.push(child);
                    }
                }
            }

            augment(t, INF);

            if (f == 0) break;
            mf += f;
        }

        cout << mf << endl;
    }

    return 0;
}