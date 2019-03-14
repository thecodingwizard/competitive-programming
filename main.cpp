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

struct state {
    int x, y, dist, targ;
};

int n;
char A[10][10];
int ways[10][10][2600][26];
bool visited[10][10][26];
int main() {
    int caseNum = 1;
	while (cin >> n && n) {
        SET4D(ways, 0, 10, 10, 2600, 26);
        SET3D(visited, false, 10, 10, 26);
        ii start;
        int biggest = -1;
		F0R(i, n) {
            F0R(j, n) {
                cin >> A[i][j];
                if (A[i][j] == 'A') start = { i, j };
                if (A[i][j] != '.' && A[i][j] != '#') {
                    A[i][j] -= 'A';
                    MAX(biggest, (int)A[i][j]);
                }
            }
        }
        
        cout << "Case " << caseNum++ << ": ";
        ii ans = { INF, INF };


        queue<state> q;
        q.push(state{start.pA, start.pB, 0, 0});
        ways[start.pA][start.pB][0][0] = 1;
        while (!q.empty()) {
            state next = q.front(); q.pop();
            if (visited[next.x][next.y][next.targ]) continue;
            visited[next.x][next.y][next.targ] = true;
            if (next.targ == biggest && A[next.x][next.y] == next.targ) {
                ans = { next.dist, ways[next.x][next.y][next.dist][next.targ] };
                break;
            }
            int newTarg = next.targ;
            if (next.targ == A[next.x][next.y]) newTarg++;
            int dx[4] = { -1, 0, 1, 0 };
            int dy[4] = { 0, 1, 0, -1 };
            F0R(i, 4) {
                state nxt = { next.x + dx[i], next.y + dy[i], next.dist + 1, newTarg };
                if (nxt.x < 0 || nxt.x >= n || nxt.y < 0 || nxt.y >= n || A[nxt.x][nxt.y] == '#') continue;
                if (A[nxt.x][nxt.y] != '.' && A[nxt.x][nxt.y] != nxt.targ) continue;
                ways[nxt.x][nxt.y][nxt.dist][newTarg] += ways[next.x][next.y][next.dist][next.targ];
                q.push(nxt);
            }
        }


        if (ans.pA == INF) {
            cout << "Impossible";
        } else {
            cout << ans.pA << " " << ans.pB;
        }
        cout << endl;
	}

    return 0;
}
