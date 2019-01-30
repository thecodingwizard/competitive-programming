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
#define MOD2 1000000007
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

int s[1000];
char grid[1000][1000];
int dist[1000][1000];
int n, m, p;

int main() {
    cin >> n >> m >> p;
    F0R(i, p) cin >> s[i];
    int ans[p];
    SET(ans, 0, p);
    SET2D(dist, 0, 1000, 1000);

    queue<ii> players[p];
    F0R(i, n) {
        F0R(j, m) {
            cin >> grid[i][j];
            if ('1' <= grid[i][j] && grid[i][j] <= '9') {
                players[grid[i][j] - '1'].push(mp(i, j));
                ans[grid[i][j] - '1']++;
            }
        }
    }

    bool change = true;
    int iteration = 1;
    while (change) {
        change = false;
        F0R(i, p) {
            while (!players[i].empty()) {
                ii next = players[i].front();
                if (dist[next.pA][next.pB] >= iteration*s[i]) break;
                players[i].pop();
                int dx[4] = {0, 1, 0, -1};
                int dy[4] = {1, 0, -1, 0};
                F0R(j, 4) {
                    ii x = { next.pA + dx[j], next.pB + dy[j] };
                    if (x.pA < 0 || x.pA >= n || x.pB < 0 || x.pB >= m || grid[x.pA][x.pB] != '.') continue;
                    grid[x.pA][x.pB] = '1' + i;
                    ans[i]++;
                    players[i].push(x);
                    dist[x.pA][x.pB] = dist[next.pA][next.pB] + 1;
                    change = true;
                }
            }
        }
        iteration++;
    }

    cout << ans[0];
    FOR(i, 1, p) cout << " " << ans[i];
    cout << endl;

    return 0;
}
