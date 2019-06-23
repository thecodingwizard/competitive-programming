/*
 * DP. Note that at every step one person must be at the work location, so you
 * can have your state as n*l*l with O(1) transitions. Just try moving the first person,
 * the second person, or the third person.
 *
 * Watch out for a small detail in the problem statement: If you're servicing station i and
 * there is already someone on station i, you *must* use that person to service station i!
 * You cannot move the second or third person in this case.
 *
 * CSES grader only allows you to solve both subtasks; it won't let you know if you got
 * one subtask correct. Also, if you get Runtime Error, it's probably MLE (64MB limit).
 *
 * To avoid MLE, use sliding window DP. However, you can still store the full n*l*l parent
 * pointers if you use char instead of int since your parent pointer is either 1, 2, or 3.
 *
 * At the very end of the code there is a grader to make sure the path you output is valid.
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

int A[200][200];
int B[1000];

int l, n;

int dp[2][200][200];
char nxt[1000][200][200];

int main() {
    setupIO();

    cin >> l >> n;
    F0R(i, l) {
        F0R(j, l) cin >> A[i][j];
    }
    F0R(i, n) {
        int req; cin >> req;
        B[i] = req - 1;
    }

    F0Rd(i, n) {
        int cur = i % 2, prv = (i + 1) % 2;
        F0R(a, l) {
            F0R(b, l) {
                if (i == n - 1) {
                    dp[cur][a][b] = 0;
                    continue;
                }
                int c = B[i], d = B[i + 1];
                int cheapest = INF;
                int option = -1;
                if (c == d) {
                    cheapest = dp[prv][a][b] + A[c][d];
                    option = 1;
                } else if (a == d) {
                    cheapest = dp[prv][c][b] + A[a][d];
                    option = 2;
                } else if (b == d) {
                    cheapest = dp[prv][c][a] + A[b][d];
                    option = 3;
                } else {
                    // move c
                    int op = dp[prv][a][b];
                    if (op + A[c][d] < cheapest) {
                        cheapest = op + A[c][d];
                        option = 1;
                    }
                    // move a
                    op = dp[prv][c][b];
                    if (op + A[a][d] < cheapest) {
                        cheapest = op + A[a][d];
                        option = 2;
                    }
                    // move b
                    op = dp[prv][c][a];
                    if (op + A[b][d] < cheapest) {
                        cheapest = op + A[b][d];
                        option = 3;
                    }
                }
                nxt[i][a][b] = option;
                dp[cur][a][b] = cheapest;
            }
        }
    }

    int best = INF;
    int option = 0;
    int a, b;
    int realA = 2, realB = 3, realC = 1;
    // go with person 1
    int op = dp[0][1][2];
    op += A[0][B[0]];
    if (op < best) {
        best = op;
        option = 1;
        a = 1, b = 2;
    }
    // person 2
    op = dp[0][0][2];
    op += A[1][B[0]];
    if (op < best) {
        best = op;
        option = 2;
        a = 0, b = 2;
        realA = 1, realB = 3, realC = 2;
    }
    // person 3
    op = dp[0][0][1];
    op += A[2][B[0]];
    if (op < best) {
        best = op;
        option = 3;
        a = 0, b = 1;
        realA = 1, realB = 2, realC = 3;
    }
    cout << best << endl;
    vi ans;
    int cur = option;
    int nCtr = 0;
    if (cur == 1) ans.pb(1);
    else if (cur == 2) ans.pb(2);
    else ans.pb(3);
    while (nCtr != n - 1) {
        cur = nxt[nCtr][a][b];
        if (cur == 1) ans.pb(realC);
        else if (cur == 2) ans.pb(realA);
        else ans.pb(realB);
        if (cur == 1) {
        } else if (cur == 2) {
            a = B[nCtr];
            int tmp = realC;
            realC = realA;
            realA = tmp;
        } else if (cur == 3) {
            b = a;
            a = B[nCtr];
            int tmp = realC, tmp2 = realB, tmp3 = realA;
            realA = tmp, realB = tmp3, realC = tmp2;
        }
        nCtr++;
    }
    cout << ans[0];
    FOR(i, 1, ans.size()) cout << " " << ans[i];
    cout << endl;

    int checker = 0;
    a = 0, b = 1; int c = 2;
    int idx = 0;
    for (int x : ans) {
        int d = B[idx++];
        if (x == 1) {
            checker += A[a][d];
            a = d;
        } else if (x == 2) {
            checker += A[b][d];
            b = d;
        } else {
            checker += A[c][d];
            c = d;
        }
    }
    assert(checker == best);

    return 0;
}