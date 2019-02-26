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
#include <ctime>

using namespace std;

template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define F0R1(i, a) for (int i=1; i<=(a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
#define F0Rd1(i, a) for (int i=a; i>0; i--)
#define SORT(vec) sort(vec.begin(), vec.end())
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

bool isValid(ll x) {
    if (x % 9 == 0) return false;
    while (x > 0) {
        if (x % 10 == 9) return false;
        x /= 10;
    }
    return true;
}

ll dp[30][9][2];

ll tenPow(ll x) {
    ll toReturn = 1;
    F0R(i, x) toReturn *= 10;
    return toReturn;
}

ll leadingDigit(ll x) {
    while (x >= 10) x /= 10;
    return x;
}

ll numDigits(ll x) {
    int ans = 0;
    while (x > 0) {
        x /= 10;
        ans++;
    }
    return ans;
}

ll getBadNumsWithNine(ll x) {
    if (x == 0) return 0;
    ll badNums = 0;
    F0R(mod, 9) {
        badNums += (leadingDigit(x))*dp[numDigits(x)-1][mod][true];
    }
    if (leadingDigit(x) == 9) badNums += x-leadingDigit(x)*tenPow(numDigits(x)-1) + 1;
    else badNums += getBadNumsWithNine(x-leadingDigit(x)*tenPow(numDigits(x)-1));
    return badNums;
}

ll getBadNumsMod(ll x, int mod) {
    if (x == 9) return 0;
    if (x == 0 || x < (9-mod)%9) return 0;
    else if (x < 10) return 1;
    ll badNums = 0;
    F0R(firstDigit, leadingDigit(x)) {
        int magicMod = (9 - firstDigit - mod);
        while (magicMod < 0) magicMod += 9;
        badNums += dp[numDigits(x)-1][magicMod%9][false];
    }
    if (leadingDigit(x) != 9) badNums += getBadNumsMod(x-leadingDigit(x)*tenPow(numDigits(x)-1), (mod+leadingDigit(x))%9);
    return badNums;
}

ll solve(ll x) {
    ll badNums = 0;
    badNums += getBadNumsMod(x, 0);
    badNums += getBadNumsWithNine(x);
    return x - badNums;
}

int main() {
    SET3D(dp, 0, 30, 9, 2);
    dp[0][0][0] = 1;
    F0R(numDigits, 20) {
        F0R(mod, 9) {
            F0R(hasNine, 2) {
                F0R(toAdd, 10) {
                    dp[numDigits+1][(mod + toAdd)%9][hasNine || toAdd == 9] += dp[numDigits][mod][hasNine];
                }
            }
        }
    }

    int t; cin >> t;
    F0R1(caseNum, t) {
        ll f, l;
        cin >> f >> l;
//        f = rand() % 5000;
//        l = rand() % 300000 + 5000;
//        ll ans = 0;
//        FOR(i, f, l+1) {
//            if (isValid(i)) ans++;
//        }
//        ll ans2 = solve(l) - solve(f) + 1;
//        if (isValid(f) && isValid(l) && f < l) {
//            if (ans != ans2) {
//                cout << "Error!!! " << f << " " << l << " should be " << ans << " but got " << ans2 << endl;
//                return 0;
//            } else {
//                cout << f << " " << l << ": All good." << endl;
//            }
//        } else {
//            cout << f << " " << l << ": Bad Input" << endl;
//        }
        cout << "Case #" << caseNum << ": " << solve(l) - solve(f) + 1 << endl;
    }

    return 0;
}