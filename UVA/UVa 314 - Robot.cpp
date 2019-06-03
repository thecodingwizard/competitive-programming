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

int main() {
    int m, n;
    while (cin >> m >> n && (n || m)) {
        int grid[m][n]; F0R(i, m) F0R(j, n) cin >> grid[i][j];
        ii start, end;
        int startDir;
        cin >> start.pA >> start.pB >> end.pA >> end.pB;
        string dir; cin >> dir;
        int dx[4] = { -1, 0, 1, 0 };
        int dy[4] = { 0, 1, 0, -1 };
        if (dir == "north") startDir = 0;
        else if (dir == "east") startDir = 1;
        else if (dir == "south") startDir = 2;
        else if (dir == "west") startDir = 3;

        queue<pair<ii, int>> q; q.push(mp(start, startDir));
        set<pair<ii, int>> visited;
        int dist[50][50][4]; SET3D(dist, INF, 50, 50, 4);
        dist[start.pA][start.pB][startDir] = 0;
        int ans = -1;
        while (!q.empty()) {
            pair<ii, int> next = q.front(); q.pop();
            if (visited.count(next) == 0) visited.insert(next);
            else continue;

            if (next.pA == end) {
                ans = dist[next.pA.pA][next.pA.pB][next.pB];
                break;
            }

            // turn left
            MIN(dist[next.pA.pA][next.pA.pB][(next.pB+3)%4], dist[next.pA.pA][next.pA.pB][next.pB] + 1);
            q.push(mp(next.pA, (next.pB+3)%4));
            // turn right
            MIN(dist[next.pA.pA][next.pA.pB][(next.pB+1)%4], dist[next.pA.pA][next.pA.pB][next.pB] + 1);
            q.push(mp(next.pA, (next.pB+1)%4));
            // move forward 1 - 3 spaces
            FOR(i, 1, 4) {
                ii pos = { next.pA.pA + dx[next.pB]*i, next.pA.pB + dy[next.pB]*i };
                if (pos.pA <= 0 || pos.pA >= m || pos.pB <= 0 || pos.pB >= n) break;
                if (grid[pos.pA][pos.pB] == 1 || grid[pos.pA - 1][pos.pB] == 1 || grid[pos.pA][pos.pB - 1] == 1 || grid[pos.pA - 1][pos.pB - 1] == 1) break;
                MIN(dist[pos.pA][pos.pB][next.pB], dist[next.pA.pA][next.pA.pB][next.pB] + 1);
                q.push(mp(pos, next.pB));
            }
        }
        cout << ans << endl;
    }

    return 0;
}
