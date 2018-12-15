/*
ID: nathan.18
TASK: buylow
LANG: C++
*/
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

using namespace std;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define F0R1(i, a) for (int i=1; i<=(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define F0Rd1(i, a) for (int i=a; i>0; i--)
#define SORT(vec) sort(vec.begin(), vec.end())

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
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<ll> vl;

void fastscan(int&n) {bool negative=false;register int c;n=0;c=getchar();if(c=='-') {negative=true;c=getchar();}
    for(;(c>47&&c<58);c=getchar()){n=n*10+c-48;}
    if(negative){n*=-1;}}

void setupIO(string PROB) {
    ifstream infile(PROB + ".in");
    if (infile.good()) {
        freopen((PROB + ".in").c_str(), "r", stdin);
        freopen((PROB + ".out").c_str(), "w", stdout);
    }
}

/* ============================ */

struct BigInteger {
    vi digits;
    BigInteger() {
        digits.pb(0);
    }
    BigInteger(int init) {
        digits.pb(init);
    }

    void add(BigInteger x) {
        for (int i = 0; i < x.digits.size(); i++) {
            if (digits.size() <= i) digits.pb(0);
            digits[i] += x.digits[i];
        }
        int i = 0;
        while (true) {
            int carry = digits[i]/10;
            digits[i] %= 10;
            if (carry == 0 && digits.size() == i+1) break;
            if (digits.size() == i+1) {
                digits.pb(carry);
            } else {
                digits[i+1] += carry;
            }
            i++;
        }
    }

    string toString() {
        string s;
        for (int digit : digits) s = to_string(digit) + s;
        return s;
    }

    bool operator <(const BigInteger& rhs) const {
        if (digits.size() != rhs.digits.size()) return digits.size() < rhs.digits.size();
        F0Rd(i, digits.size()) {
            if (digits[i] != rhs.digits[i]) return digits[i] < rhs.digits[i];
        }
        return false;
    }
};

int n;
int A[5000];
pair<int, BigInteger> dp[5000];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    setupIO("buylow");

    cin >> n;
    F0R(i, n) cin >> A[i];

    F0R(i, n) {
        int best = 1;
        map<int, BigInteger> tmp;
        F0R(j, i) {
            if (A[j] > A[i]) {
                if (best == dp[j].pA + 1) {
                    tmp[A[j]] = max(tmp[A[j]], dp[j].pB);
                } else if (best < dp[j].pA + 1) {
                    best = dp[j].pA + 1;
                    tmp.clear();
                    tmp[A[j]] = dp[j].pB;
                }
            }
        }
        dp[i].pA = best;
        if (best == 1) {
            dp[i].pB = BigInteger(1);
        } else {
            BigInteger bestCt = 0;
            for (auto const &x : tmp) {
                bestCt.add(x.pB);
            }
            dp[i].pB = bestCt;
        }
    }

    int best = 0;
    map<int, BigInteger> bestCt;
    F0R(i, n) {
        if (best == dp[i].pA) {
            bestCt[A[i]] = max(bestCt[A[i]], dp[i].pB);
        } else if (best < dp[i].pA) {
            best = dp[i].pA;
            bestCt.clear();
            bestCt[A[i]] = dp[i].pB;
        }
    }
    BigInteger finalCt = 0;
    for (auto const &x : bestCt) finalCt.add(x.pB);
    cout << best << " " << finalCt.toString() << endl;

    return 0;
}