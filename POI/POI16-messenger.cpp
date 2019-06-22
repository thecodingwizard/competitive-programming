/*
 * DP ways(i, j, k) = number of ways to go from i to j using k moves, ignoring condition of visiting start/end only once
 *
 * To go from this to the number of good ways, see the last code block in the editorial:
 * https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/POI/official/2016/editorial/pos.pdf
 */

#include <bits/stdc++.h>

using namespace std;

template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define F0R1(i, a) for (int i=1; i<=(a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
#define F0Rd1(i, a) for (int i=a; i>0; i--)
#define SORT(vec) sort(vec.begin(), vec.end())
#define RSORT(vec) sort(vec.rbegin(), vec.rend())
#define MIN(a, b) a = min(a, b)
#define MAX(a, b) a = max(a, b)

#define INF 1000000010
#define LL_INF 4500000000000000000LL
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

void setupIO(const string &PROB = "") {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if (PROB.length() != 0) {
        ifstream infile(PROB + ".in");
        if (infile.good()) {
            freopen((PROB + ".in").c_str(), "r", stdin);
            freopen((PROB + ".out").c_str(), "w", stdout);
        }
    }
}

/* ============================ */

int n, m, z;
vector<int> children[100];

int memo[100][100][51];

ll dp(int curLoc, int v, int d) {
    if (d < 0) return 0;
    if (memo[curLoc][v][d] != -1) return memo[curLoc][v][d];
    if (d == 0) return curLoc == v;
    int ans = 0;
    for (int uu : children[curLoc]) {
        ans = (ans + dp(uu, v, d - 1)) % z;
    }
    return memo[curLoc][v][d] = ans;
}

int ans[100][100][51];

int main() {
    setupIO();

    cin >> n >> m >> z;
    F0R(i, m) {
        int a, b;
        cin >> a >> b;
        children[--a].pb(--b);
    }
    int q;
    cin >> q;
    SET3D(memo, -1, 100, 100, 51);

    int validWays[2][2][51];
    F0R(u, n) {
        F0R(v, n) {
            int xx[2] = {u, v};
            F0R1(i, 50) {
                F0R(j, 2) {
                    F0R(k, 2) {
                        validWays[j][k][i] = dp(xx[j], xx[k], i);
                        F0R(l, 2) {
                            F0R1(m, i - 1) {
                                validWays[j][k][i] -= (dp(xx[j], xx[l], m) * validWays[l][k][i - m]) % z;
                                validWays[j][k][i] = (validWays[j][k][i] + z) % z;
                            }
                        }
                    }
                }
                ans[u][v][i] = validWays[0][1][i];
            }
        }
    }


    F0R(i, q) {
        int u, v, d;
        cin >> u >> v >> d;
        cout << ans[u - 1][v - 1][d] << "\n";
    }

    return 0;
}