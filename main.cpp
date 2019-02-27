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

int n, k;
ll dp[200][(1 << 15)];
iii requirements[100];

string solve(int mask, ll p, int start) {
    if (start == n) return "";
    if (p >= dp[start+1][(mask & ~(1 << 15)) << 1]) {
        return "1" + solve(((mask & ~(1 << 15)) << 1) + 1, p-dp[start+1][(mask & ~(1 << 15)) << 1], start+1);
    } else {
        return "0" + solve((mask & ~(1 << 15)) << 1, p, start+1);
    }
}

int main() {
    int t; cin >> t;
    F0R1(caseNum, t) {
        ll p;
        cin >> n >> k >> p;
        F0R(i, k) {
            int a, b, c; cin >> a >> b >> c;
            requirements[i] = { c, { --a, --b } };
        }
        SET2D(dp, 0, 200, (1 << 15));

        F0R(j, (1 << 15)) {
            bool bad = false;
            F0R(l, k) {
                if (requirements[l].pB.pB < n && requirements[l].pB.pA >= n-15) {
                    int ct = 0;
                    FOR(m, n-requirements[l].pB.pB-1, n-requirements[l].pB.pA) {
                        if (j & (1 << m)) ct++;
                    }
                    if (ct != requirements[l].pA) bad = true;
                }
            }
            if (bad) dp[n][j] = 0;
            else dp[n][j] = 1;
        }

        F0Rd(i, n) {
            F0R(j, (1 << 15)) {
                bool bad = false;
                F0R(l, k) {
                    if (requirements[l].pB.pB < i && requirements[l].pB.pA >= i-15) {
                        int ct = 0;
                        FOR(m, i-requirements[l].pB.pB-1, i-requirements[l].pB.pA) {
                            if (j & (1 << m)) ct++;
                        }
                        if (ct != requirements[l].pA) bad = true;
                    }
                }
                F0R(l, 16) {
                    if ((j & (1 << l)) && l>=i) bad = true;
                }
                if (bad) dp[i][j] = 0;
                else dp[i][j] = dp[i+1][(j & ~(1 << 15)) << 1] + dp[i+1][((j & ~(1 << 15)) << 1) + 1];
            }
        }

        cout << "Case #" << caseNum << ": " << solve(0, p-1, 0) << endl;
    }

    return 0;
}