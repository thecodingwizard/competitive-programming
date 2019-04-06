/*
ID: nathan.18
TASK: twofive
LANG: C++
*/

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

int grid[5][5];
int memo[6][6][6][6][6];
bool used[26];

int run(int a, int b, int c, int d, int e, int val) {
    if (e == 5) return 1;
    while (val <= 25 && used[val]) val++;
    if (val > 25) return 0;

    if (memo[a][b][c][d][e] != -1) return memo[a][b][c][d][e];

    int ans = 0;
    if (a != 5 && (a == 0 || grid[0][a-1] < val)) ans += run(a+1, b, c, d, e, val+1);
    if (b != 5 && b < a && grid[0][b] < val && (b == 0 || grid[1][b - 1] < val)) ans += run(a, b+1, c, d, e, val+1);
    if (c != 5 && c < b && grid[1][c] < val && (c == 0 || grid[2][c - 1] < val)) ans += run(a, b, c+1, d, e, val+1);
    if (d != 5 && d < c && grid[2][d] < val && (d == 0 || grid[3][d - 1] < val)) ans += run(a, b, c, d+1, e, val+1);
    if (e != 5 && e < d && grid[3][e] < val && (e == 0 || grid[4][e - 1] < val)) ans += run(a, b, c, d, e+1, val+1);
    
    /* cout << a << " " << b << " " << c << " " << d << " " << e << " " << val << " " << ans << endl; */

    return memo[a][b][c][d][e] = ans;
}


int main() {
    setupIO("twofive");
    
    /* SET2D(grid, -1, 5, 5); */
    /* SET(used, false, 26); */
    /* F0R(i, 6) F0R(j, 6) F0R(k, 6) F0R(l, 6) F0R(m, 6) memo[i][j][k][l][m] = -1; */
    /* run(0, 0, 0, 0, 0, 0); */

    /* return 0; */

    char c; cin >> c;
    if (c == 'N') {
        int m; cin >> m;
        SET2D(grid, -1, 5, 5);
        SET(used, false, 26);
        F0R(i, 5) {
            F0R(j, 5) {
                int sum = 0;
                F0R(k, 25) {
                    if (used[k]) continue;
                    if (j > 0 && grid[i][j - 1] >= k) continue;
                    if (i > 0 && grid[i - 1][j] >= k) continue;
                    grid[i][j] = k;
                    used[k] = true;

                    F0R(i, 6) F0R(j, 6) F0R(k, 6) F0R(l, 6) F0R(m, 6) memo[i][j][k][l][m] = -1;

                    int val;
                    if (i == 0) val = run(j+1, 0, 0, 0, 0, 0);
                    if (i == 1) val = run(5, j+1, 0, 0, 0, 0);
                    if (i == 2) val = run(5, 5, j+1, 0, 0, 0);
                    if (i == 3) val = run(5, 5, 5, j+1, 0, 0);
                    if (i == 4) val = run(5, 5, 5, 5, j+1, 0);
                    /* cout << val << endl; */
                    sum += val;
                    if (sum >= m) {
                        sum -= val;
                        m -= sum;
                        break;
                    }
                    used[k] = false;
                }
            }
        }

        string ans = "";
        F0R(i, 5) F0R(j, 5) ans += ('A' + grid[i][j]);
        cout << ans << endl;
    } else {
        char realGrid[5][5];
        F0R(i, 5) F0R(j, 5) cin >> realGrid[i][j];
        SET2D(grid, -1, 5, 5);
        SET(used, false, 26);

        int ans = 0;
        F0R(i, 5) {
            F0R(j, 5) {
                F0R(k, 25) {
                    if (used[k]) continue;
                    if (j > 0 && grid[i][j - 1] >= k) continue;
                    if (i > 0 && grid[i - 1][j] >= k) continue;
                    grid[i][j] = k;
                    used[k] = true;
                    if (k == realGrid[i][j] - 'A') break;

                    F0R(i, 6) F0R(j, 6) F0R(k, 6) F0R(l, 6) F0R(m, 6) memo[i][j][k][l][m] = -1;

                    int val;
                    if (i == 0) val = run(j+1, 0, 0, 0, 0, 0);
                    if (i == 1) val = run(5, j+1, 0, 0, 0, 0);
                    if (i == 2) val = run(5, 5, j+1, 0, 0, 0);
                    if (i == 3) val = run(5, 5, 5, j+1, 0, 0);
                    if (i == 4) val = run(5, 5, 5, 5, j+1, 0);

                    ans += val;

                    used[k] = false;
                }
            }
        }
        
        ans++;
        cout << ans << endl;
    }

    return 0;
}
