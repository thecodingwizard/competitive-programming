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

int A[100000];
string sum(int j, int k) {
    string ans = "";
    int carry = 0;
    F0R(digit, max(j, k-j)) {
        int left = digit < j ? A[j - digit - 1] : 0;
        int right = digit < k-j ? A[k - digit - 1] : 0;
        int together = left + right + carry;
        carry = 0;
        if (together >= 10) {
            carry = 1;
            together -= 10;
        }
        ans = to_string(together) + ans;
    }
    if (carry == 1) ans = "1" + ans;
    return ans;
}

int main() {
    setupIO();

    int n; cin >> n;
    F0R(i, n) {
        char c; cin >> c;
        A[i] = c - '0';
    }
    FOR(numLen, n/2, n) {
        // numLen...n
        string cur = "-1";
        if (A[numLen] != 0) {
            string ans = sum(numLen, n);
            cur = ans;
        }
        if (A[n - numLen] != 0) {
            string ans = sum(n - numLen, n);
            if (cur == "-1") cur = ans;
            else cur = min(cur, ans);
        }
        if (cur != "-1") {
            cout << cur << endl;
            return 0;
        }
    }

    return 0;
}