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

int n;
bool canReachStart[100][100], canReachEnd[100][100];
int grid[100][100];
bool visited[100][100];
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

void floodfill1(int a, int b) {
    canReachStart[a][b] = true;
    visited[a][b] = true;
    F0R(i, 4) {
        int a1 = a + dx[i], a2 = b + dy[i];
        if (a1 < 0 || a1 >= n || a2 < 0 || a2 >= n) continue;
        if (visited[a1][a2] || grid[a1][a2]) continue;
        floodfill1(a1, a2);
    }
}

void floodfill2(int a, int b) {
    canReachEnd[a][b] = true;
    visited[a][b] = true;
    F0R(i, 4) {
        int a1 = a + dx[i], a2 = b + dy[i];
        if (a1 < 0 || a1 >= n || a2 < 0 || a2 >= n) continue;
        if (visited[a1][a2] || grid[a1][a2]) continue;
        floodfill2(a1, a2);
    }
}

int cost(int i, int j, int k, int l) {
    return (k-i)*(k-i)+(l-j)*(l-j);
}

int main() {
    cin >> n;
    ii start, end;
    cin >> start.pA >> start.pB >> end.pA >> end.pB;

    F0R(i, n) {
        F0R(j, n) {
            char c; cin >> c;
            grid[i][j] = c == '1';
        }
    }

    SET2D(canReachStart, false, 100, 100);
    SET2D(canReachEnd, false, 100, 100);
    SET2D(visited, false, 100, 100);
    floodfill1(start.pA-1, start.pB-1);
    SET2D(visited, false, 100, 100);
    floodfill2(end.pA-1, end.pB-1);

    int ans = INF;
    F0R(i, n) {
        F0R(j, n) {
            F0R(k, n) {
                F0R(l, n) {
                    if (canReachStart[i][j] && canReachEnd[k][l]) MIN(ans, cost(i, j, k, l));
                }
            }
        }
    }
    cout << ans << endl;

    return 0;
}