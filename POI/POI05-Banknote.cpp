/*
 * A n*k*k dp solution is fairly obvious (n*k states, then from each location just try using 1...C_i notes of that denomination).
 *
 * However using a deque it's possible to update all the transitions in O(k) time bringing the complexity
 * down to O(n*k). Editorial: https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/POI/official/2005/editrial/ban.pdf
 * Look on page 92 for the pseudocode.
 *
 * Basically, when processing a note i with value A and number B, consider every offset from 0...A-1.
 * Let's call the offset we're currently processing X.
 *
 * We are going to update all the DP values X, X+A, X+A+A, X+A+A+A, ... all the way until we reach k.
 *
 * For every DP value that we update, we basically have to decide how many of note i we want to take
 * in O(1) time. Obviously to update X we take 0 notes.
 * To update X+A, we can either take 0 notes or 1 note.
 * To update X+A+A we take 0, 1, or 2 notes.
 * Let's say we're trying to update X + a*A. For every y <= a,
 * DP[X + a*A] = min(DP[X + a*A], DP[X + y*A] + (a - y))
 * where (a-y) is the number of notes of value A that we take. We also have to make sure that (a - y) <= numberOfNotes[i]
 * We can maintain a deque as we update X, then X+A, then X+A+A...
 * The deque contains a list of monotonically increasing values of y.
 * The front of the deque is ideal; e.g. DP[X + y*A] + (a - y) is minimized.
 * However, we have to make sure to pop off the front of the deque if (a - y) is greater than numberOfNotes[i].
 *
 * Look at the pseudocode in the editorial or look at the code below for additional clarity.
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

int n;
int A[200], B[200];
iii dp[20001][201];

int main() {
    setupIO();

    cin >> n; F0R(i, n) cin >> A[i]; F0R(i, n) cin >> B[i];
    int k; cin >> k;

    F0R(i, k+1) F0R(j, n+1) dp[i][j] = { INF, { INF, INF } };

    dp[0][0].pA = 0;
    F0R(j, n) {
        F0R(i, A[j]) {
            deque<int> dq;
            int numTimes = 0;
            int val = A[j];
            while (i + numTimes*val <= k) {
                int dest = i + val*numTimes;
                while (!dq.empty() && (dp[i + val*dq.back()][j].pA + (numTimes - dq.back()) >= dp[i + val*numTimes][j].pA)) dq.pop_back();
                dq.push_back(numTimes);

                if (dp[dest][j+1].pA > dp[i + val*dq.front()][j].pA + (numTimes - dq.front())) {
                    dp[dest][j+1] = { dp[i + val*dq.front()][j].pA + (numTimes - dq.front()), { i + val*dq.front(), j } };
                }

                if (numTimes - dq.front() == B[j]) dq.pop_front();
                numTimes++;
            }
        }
    }

    cout << dp[k][n].pA << endl;
    assert(dp[k][n].pA != INF);
    int ans[n]; SET(ans, 0, n);
    ii cur = { k, n };
    while (cur.pA != 0) {
        ii xx = dp[cur.pA][cur.pB].pB;
        int val = A[xx.pB]; int diff = cur.pA - xx.pA;
        int ct = diff / val;
        ans[xx.pB] += ct;
        cur = xx;
    }
    cout << ans[0];
    FOR(i, 1, n) cout << " " << ans[i];
    cout << endl;

    return 0;
}