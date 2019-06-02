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

int n;
ii A[20000];
int dp[2][2002][2];
int main() {
    cin >> n;
    F0R(i, n) {
        cin >> A[i].pA >> A[i].pB;
    }

    SET3D(dp, INF, 1, 2002, 2);
    dp[0][1000][0] = abs(A[0].pA);
    dp[0][1000][1] = abs(A[0].pB);
    F0R(i, n - 1) {
        int curIdx = i % 2;
        int nxtIdx = (i + 1) % 2;
        F0R(j, 2002) F0R(k, 2) dp[nxtIdx][j][k] = INF;
        F0R(j, 2002) {
            F0R(k, 2) {
                if (dp[curIdx][j][k] == INF) continue;
                int cDist = dp[curIdx][j][k];
                int xCoord, yCoord;
                if (k == 0) {
                    xCoord = A[i].pA;
                    yCoord = j - 1000;
                } else {
                    xCoord = j - 1000;
                    yCoord = A[i].pB;
                }
                int dX = abs(xCoord - A[i + 1].pA) + cDist;
                int dY = abs(yCoord - A[i + 1].pB) + cDist;
                MIN(dp[nxtIdx][yCoord + 1000][0], dX);
                MIN(dp[nxtIdx][xCoord + 1000][1], dY);
            }
        }
    }
    int ans = INF;
    F0R(j, 2002) {
        F0R(k, 2) {
            MIN(ans, dp[(n - 1) % 2][j][k]);
        }
    }
    cout << ans << endl;

    return 0;
}