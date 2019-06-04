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
    setupIO("balance");

    int n; cin >> n;
    ll A[2*n]; F0R(i, 2*n) cin >> A[i];

    ll numOnes = 0;
    ll numLeft = 0, numRight = 0;
    ll ct[2*n];
    ll psZeroes[2*n];
    ll psOnes[n];
    vi leftZeroes, rightZeroes;
    psZeroes[n - 1] = !A[n - 1];
    F0Rd(i, n - 1) {
        psZeroes[i] = psZeroes[i + 1] + !A[i];
    }
    F0R(i, n) {
        psOnes[i] = numOnes;
        if (A[i] == 0) {
            numLeft += numOnes;
            ct[i] = numOnes;
            leftZeroes.pb(i);
        } else {
            numOnes++;
            ct[i] = psZeroes[i];
        }
    }
    reverse(all(leftZeroes));
    numOnes = 0;
    psZeroes[2*n - 1] = !A[2*n - 1];
    F0Rd(i, 2*n - 1) {
        psZeroes[i] = psZeroes[i + 1] + !A[i];
    }
    FOR(i, n, 2*n) {
        if (A[i] == 0) {
            numRight += numOnes;
            ct[i] = numOnes;
            rightZeroes.pb(i);
        } else {
            numOnes++;
            ct[i] = psZeroes[i];
        }
    }

    ll ans = abs(numLeft - numRight);

    ll left = numLeft, right = numRight;
    // Case 1: Move ones from right to left
    int zeroIdx = 0;
    ll numSwaps = 0;
    FOR(i, n, 2*n) {
        if (zeroIdx == leftZeroes.size()) break;
        if (A[i] == 1) {
            int zeroLoc = leftZeroes[zeroIdx++];
            left -= ct[zeroLoc];
            right -= ct[i];
            numSwaps += (i - zeroLoc);
            MIN(ans, abs(left - right) + numSwaps);
        }
    }

    // Case 2: Move ones from left to right
    zeroIdx = 0;
    left = numLeft, right = numRight;
    numSwaps = 0;
    ll numMoved = 0;
    F0Rd(i, n) {
        if (zeroIdx == rightZeroes.size()) break;
        if (A[i] == 1) {
            int zeroLoc = rightZeroes[zeroIdx++];
            left -= ct[i] + numMoved;
            left += psOnes[i];
            right -= ct[zeroLoc] + numMoved;
            right += psZeroes[zeroLoc] - 1;
            numSwaps += (zeroLoc - i);
            MIN(ans, abs(left - right) + numSwaps);
            numMoved++;
        }
    }
    cout << ans << endl;

    return 0;
}
