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
string s;
vi children[20][20];
bool visited[20][20];
ll ways[20][20];
vii S;

void topoSort(int row, int col) {
    visited[row][col] = true;

    for (int child : children[row][col]) {
        if (!visited[row+1][child]) topoSort(row+1, child);
    }

    S.pb(mp(row, col));
}

int getVal(char x) {
    if (x == '?') return INF;
    if (x >= 'A') return x - 'A' + 9;
    return x - '1';
}

int main() {
    while (cin >> s) {
        n = s.length();
        S.clear();
        SET2D(visited, false, 20, 20);
        SET2D(ways, 0, 20, 20);

        F0R(i, n) {
            F0R(col, n) {
                children[i][col].clear();
                if (i == n - 1) continue;
                if (s[i + 1] == '?') {
                    F0R(j, n) {
                        int val = j;
                        if (abs(col - val) <= 1) continue;
                        children[i][col].pb(val);
                    }
                } else {
                    int val = getVal(s[i + 1]);
                    if (abs(col - val) <= 1) continue;
                    children[i][col].pb(val);
                }
            }
        }

        if (s[0] == '?') {
            F0R(x, n) {
                ways[0][x] = 1;
                topoSort(0, x);
            }
        } else {
            int val = getVal(s[0]);
            ways[0][val] = 1;
            topoSort(0, val);
        }

        reverse(S.begin(), S.end());

        for (ii x : S) {
            for (int child : children[x.pA][x.pB]) {
                ways[x.pA+1][child] += ways[x.pA][x.pB];
            }
        }

        ll ans = 0;
        F0R(i, n) ans += ways[n-1][i];

        cout << ans << endl;
    }

    return 0;
}
