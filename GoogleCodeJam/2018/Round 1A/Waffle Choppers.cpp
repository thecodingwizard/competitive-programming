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

int main() {
    int t; cin >> t;
    F0R1(caseNum, t) {
        int r, c, h, v;
        cin >> r >> c >> h >> v;
        char grid[r + 1][c + 1];
        F0R1(i, r) F0R1(j, c) cin >> grid[i][j];
        int ps[r + 1][c + 1];
        SET2D(ps, 0, r + 1, c + 1);
        F0R1(i, r) {
            F0R1(j, c) {
                ps[i][j] = ps[i - 1][j] + ps[i][j - 1] - ps[i - 1][j - 1] + (grid[i][j] == '@');
            }
        }
        int ct = ps[r][c];
        bool can = true;
        if (ct % (h+1)*(v+1) != 0) can = false;
        int numPerCookie = ct/(h+1)/(v+1);

        vi horizLines;
        int start = 0;
        F0R1(i, r) {
            if ((ps[i][c] - ps[start][c]) == numPerCookie*(v+1)) {
                horizLines.pb(i);
                start = i;
            }
        }
        if (horizLines.size() != h + 1) can = false;
        else {
            bool hasLine[c+1]; SET(hasLine, false, c+1);
            start = 0;
            int ctr = 0;
            F0R1(i, c) {
                if (ps[r][i] - ps[r][start] == numPerCookie*(h+1)) {
                    hasLine[i] = true;
                    start = i;
                    ctr++;
                }
            }
            if (ctr != v + 1) can = false;
            F0R(i, h+1) {
                int top = (i == 0 ? 0 : horizLines[i - 1]), bot = horizLines[i];
                start = 0;
                F0R1(j, c) {
                    if (!hasLine[j]) continue;
                    if ((ps[bot][j] - ps[top][j]) - (ps[bot][start] - ps[top][start]) != numPerCookie) {
                        can = false;
                    }
                    start = j;
                }
            }
        }

        if (ps[r][c] == 0) can = true;

        cout << "Case #" << caseNum << ": ";
        if (can) cout << "POSSIBLE" << endl;
        else cout << "IMPOSSIBLE" << endl;
    }

    return 0;
}
