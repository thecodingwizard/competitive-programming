/*
 * We can keep track of k prefix sums as we sweep from left to right.
 * Each time we encounter a prefix sum we have encountered before, we can
 * use that as an interval. However, we have to check to make sure that none
 * of the intermediate prefix sum values go below the endpoints prefix sum values
 * as that would mean that there was some unbalanced parenthesis, like ")(".
 * We can do this by doing an initial sweep:
 * - For each location i, figure out the first location j s.t. there exists some k where A[k][j] < A[k][i]
 *
 * This is basically the solution described in the official USACO solution: http://usaco.org/current/data/sol_cbs.html
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

int main() {
    setupIO("cbs");

    int k, n;
    cin >> k >> n;
    char A[k][n];
    F0R(i, k) {
        F0R(j, n) {
            cin >> A[i][j];
        }
    }

    // For each location i, figure out the first location j s.t. there exists some k where A[k][j] < A[k][i]
    int minStartLoc[n];
    SET(minStartLoc, -1, n);
    stack<ii> s;
    F0R(j, k) {
        while (!s.empty()) s.pop();
        int ps = 0;
        F0R(i, n) {
            if (A[j][i] == '(') ps++;
            else ps--;
            while (!s.empty() && s.top().pA >= ps) {
                s.pop();
            }
            if (!s.empty()) {
                MAX(minStartLoc[i], s.top().pB);
            }
            s.push(mp(ps, i));
        }
    }

    map<vi, int> psLocations;

    vi init;
    F0R(i, k) init.pb(0);
    psLocations[init] = 0;

    int ps[k];
    SET(ps, 0, k);
    int setCount[n+1];
    SET(setCount, 0, n);
    ll ans = 0;
    F0R(i, n) {
        vi nums;
        F0R(j, k) {
            if (A[j][i] == '(') ps[j]++;
            else ps[j]--;
            nums.pb(ps[j]);
        }
        if (psLocations.count(nums)) {
            // can match with psLocations[nums]
            // check to make sure psLocations[nums]...i prefix sums don't go below nums
            int startLoc = psLocations[nums];
            if (startLoc > minStartLoc[i]) {
                ans += setCount[startLoc] + 1;
                setCount[i + 1] = setCount[startLoc] + 1;
            }
        }
        psLocations[nums] = i + 1;
    }
    cout << ans << endl;

    return 0;
}
