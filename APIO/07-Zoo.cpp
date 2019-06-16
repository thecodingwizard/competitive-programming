// Editorial: https://github.com/mostafa-saad/MyCompetitiveProgramming/tree/master/Olympiad/APIO/official/2007/2007.pdf
// dp[k][i][j] = maximum number of children whose vision end at or before k
// assuming first 4 enclosures are i
// and last 5 enclosures are j
// sliding window on k

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

struct child {
    vi like, fear;
};

int main() {
    setupIO();

    int n, c; cin >> n >> c;
    int dp[2][(1 << 4)][(1 << 5)];

    SET3D(dp, 0, 2, (1 << 4), (1 << 5));

    vector<child> A[n];
    F0R(i, c) {
        int e, f, l; cin >> e >> f >> l;
        child ch;
        F0R(j, f) {
            int x; cin >> x;
            ch.fear.pb(x-1);
        }
        F0R(j, l) { int x; cin >> x; ch.like.pb(x-1); }
        A[(e-1+4)%n].pb(ch);
    }

    FOR(i, 4, n) {
        int cur = (i % 2);
        int prv = (i - 1) % 2;
        F0R(startMask, (1 << 4)) {
            F0R(curMask, (1 << 5)) {
                bool illegal = false;
                FOR(j, i - 4, 4) {
                    int startPos = j;
                    int curPos = j - (i - 4);
                    bool startOn = (startMask & (1 << startPos)) > 0;
                    bool curOn = (curMask & (1 << curPos)) > 0;
                    if (startOn != curOn) {
                        illegal = true;
                    }
                }
                if (illegal) {
                    dp[cur][startMask][curMask] = -INF;
                    continue;
                }

                int newCt = 0;
                for (child ch : A[i]) {
                    bool good = false;
                    for (int like : ch.like) {
                        int curPos = like - (i - 4);
                        if (curMask & (1 << curPos)) {
                            good = true;
                        }
                    }
                    for (int fear : ch.fear) {
                        int curPos = fear - (i - 4);
                        if (!(curMask & (1 << curPos))) {
                            good = true;
                        }
                    }
                    if (good) newCt++;
                }

                int oldCt = -INF;
                int prevMask = curMask & ~(1 << 4);
                prevMask <<= 1;
                oldCt = max(oldCt, dp[prv][startMask][prevMask]);
                oldCt = max(oldCt, dp[prv][startMask][prevMask | 1]);

                dp[cur][startMask][curMask] = oldCt + newCt;
            }
        }
    }

    int ans = 0;
    F0R(startMask, (1 << 4)) {
        F0R(curMask, (1 << 5)) {
            int extraChildren = 0;
            F0R(endLoc, 4) {
                for (child ch : A[endLoc]) {
                    bool good = false;
                    for (int like : ch.like) {
                        if (like < 4) {
                            if (startMask & (1 << like)) good = true;
                        } else {
                            int maskPos = like - (n - 5);
                            assert(maskPos >= 0 && maskPos < 5);
                            if (curMask & (1 << maskPos)) good = true;
                        }
                    }
                    for (int fear : ch.fear) {
                        if (fear < 4) {
                            if (!(startMask & (1 << fear))) good = true;
                        } else {
                            int maskPos = fear - (n - 5);
                            assert(maskPos >= 0 && maskPos < 5);
                            if (!(curMask & (1 << maskPos))) good = true;
                        }
                    }
                    if (good) extraChildren++;
                }
            }
            ans = max(ans, dp[(n-1)%2][startMask][curMask] + extraChildren);
        }
    }
    assert(ans <= c);
    cout << ans << endl;

    return 0;
}