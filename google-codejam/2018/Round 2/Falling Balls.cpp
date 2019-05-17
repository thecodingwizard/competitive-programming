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
        int c; cin >> c;
        int A[c]; F0R(i, c) cin >> A[i];
        bool taken[c]; SET(taken, false, c);
        char ans[c][c]; SET2D(ans, '.', c, c);
        bool good = true;
        int maxDist = 0;
        if (A[0] == 0 || A[c-1] == 0) good = false;
        F0R(i, c) {
            if (A[i] != 0) {
                int ct = 0;
                int end = i;
                F0R(j, i + 1) {
                    if (taken[j]) continue;
                    ct++;
                    taken[j] = true;
                    if (end == i) end = j;
                    if (ct == A[i]) break;
                }
                F0R(x, i - end) {
                    ans[x][end + x] = '\\';
                }
                MAX(maxDist, i - end);
                FOR(j, i, c) {
                    if (ct == A[i]) break;
                    if (taken[j]) continue;
                    ct++;
                    taken[j] = true;
                    end = j;
                }
                F0R(x, end - i) {
                    ans[x][end - x] = '/';
                }
                MAX(maxDist, end - i);
            }
        }
        maxDist++;
        if (!good) {
            cout << "Case #" << caseNum << ": IMPOSSIBLE" << endl;
        } else {
            cout << "Case #" << caseNum << ": " << maxDist << endl;
            F0R(i, maxDist) {
                F0R(j, c) {
                    cout << ans[i][j];
                }
                cout << endl;
            }
        }
    }


    return 0;
}
