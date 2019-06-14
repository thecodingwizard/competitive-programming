/*
 * Pattern Finding
 *
 * You can write a brute-force script for small n, and hence you can find many patterns
 *
 * First consider if there was just one knight. Obvious pattern exists to see whether or not
 * Alice will win.
 *
 * If there are multiple knights, the optimal strategy for each player is:
 * - If you are going to lose with that knight, lose as fast as possible
 * - If you are going to win with that knight, win as slowly as possible
 *
 * Hence you can use DP to calculate how many moves before a knight will have
 * no more possible moves assuming each player plays optimally. A pattern exists for this as well!
 *
 * Finally you can solve the problem after figuring out all the patterns.
 * In O(1) time, you can identify whether or not a knight is a winning knight,
 * and how many moves before the knight will run out of moves.
 *
 * If the most # of moves of any losing knight for Alice is >=
 * the most # of moves of any winning knight for Alice, then No. Otherwise, Yes.
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

int k, n;
ii A[200000];

int calcMoves(ii loc) {
    int x = loc.pA, y = loc.pB;
    int numMoves = loc.pA/2 + loc.pB/2;
    if (x/2 % 2 == 1 && y/2 % 2 == 1) {
        if (x % 2 == 0 && y % 2 == 0) numMoves -= 1;
        else numMoves += 1;
    }
    return numMoves;
}

bool willWin(ii loc) {
    bool ans = calcMoves(loc) % 2 == 1;
    if (n % 4 == 0) {
        if (loc.pA == n-1 && loc.pB == n-1) ans = false;
    } else if (n % 4 == 1) {
        if (loc.pA == n-1 || loc.pB == n-1) {
            if (loc.pA == n-2 || loc.pB == n-2) ans = true;
            else ans = false;
        }
    }
    return ans;
}

int main() {
    setupIO();

    cin >> k >> n;
    F0R(i, k) {
        cin >> A[i].pA >> A[i].pB;
        --A[i].pA; --A[i].pB;
    }

    int lengthLoss = -1, lengthWin = -1;
    F0R(i, k) {
        int numMoves = calcMoves(A[i]);
        if (willWin(A[i])) {
            MAX(lengthWin, numMoves);
        } else {
            MAX(lengthLoss, numMoves);
        }
    }
    int dx[4] = { -2, -2, -1, 1 };
    int dy[4] = { 1, -1, -2, -2 };
    if (lengthLoss >= lengthWin) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        F0R(i, k) {
            int best = willWin(A[i]) ? -INF : INF;
            int bestAns = -1;
            F0R(x, 4) {
                int a = A[i].pA + dx[x], b = A[i].pB + dy[x];
                if (a < 0 || a >= n || b < 0 || b >= n) continue;
                if (willWin(A[i])) {
                    // Maximize
                    if (!willWin(mp(a, b)) && best < calcMoves(mp(a, b))) {
                        best = calcMoves(mp(a, b));
                        bestAns = x;
                    }
                } else {
                    // Minimize
                    if (best > calcMoves(mp(a, b))) {
                        best = calcMoves(mp(a, b));
                        bestAns = x;
                    }
                }
            }
            assert(bestAns != -1);
            int a = A[i].pA + dx[bestAns], b = A[i].pB + dy[bestAns];
            cout << a+1 << " " << b+1 << endl;
        }
    }

    return 0;
}