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


int main() {
    int m; cin >> m;

    while (m--) {
        int n; cin >> n;
        vi children[n];
        F0R(i, n) {
            int x; cin >> x;
            F0R(j, x) {
                int enemy; cin >> enemy;
                --enemy;
                if (enemy >= n) continue;
                children[enemy].pb(i);
                children[i].pb(enemy);
            }
        }

        bool visited[n]; SET(visited, false, n);
        int ans = 0;

        F0R(i, n) {
            if (visited[i]) continue;

            queue<int> q;
            q.push(i);
            int color[n];
            SET(color, INF, n);
            color[i] = 0;

            bool isBipartite = true;
            while (!q.empty() && isBipartite) {
                int next = q.front(); q.pop();
                visited[next] = true;
                for (int child : children[next]) {
                    if (color[child] == INF) {
                        color[child] = 1 - color[next];
                        q.push(child);
                    } else if (color[child] == color[next]) {
                        isBipartite = false;
                    }
                }
            }

            if (isBipartite) {
                int ct[2];
                SET(ct, 0, 2);
                F0R(x, n) {
                    if (color[x] == INF) continue;
                    ct[color[x]]++;
                }
                ans += max(ct[0], ct[1]);
            }
        }
        cout << ans << endl;
    }

    return 0;
}