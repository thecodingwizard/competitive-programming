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
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
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

ll n, c, f;
pair<ll, ll> A[70000];

bool can(ll midIdx) {
    multiset<ll> lowCows, hiCows;
    F0R(i, midIdx) lowCows.insert(A[i].pB);
    FOR(i, midIdx, c) hiCows.insert(A[i].pB);
    ll totCost = 0;
    int have = 0;
    int half = n/2;
    for (ll cost : lowCows) {
        totCost += cost;
        have++;
        if (have == half) break;
    }
    for (ll cost : hiCows) {
        totCost += cost;
        have++;
        if (have == n) break;
    }
    return f >= totCost;
}

int main() {
    cin >> n >> c >> f;
    F0R(i, c) cin >> A[i].pA >> A[i].pB;
    sort(A, A+c);

    ll lo = (n/2), hi = c-(n/2), mid, ans = -1;
    while (lo < hi) {
        mid = (lo + hi)/2;
        if (can(mid)) {
            ans = mid;
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }

    if (ans == -1) cout << "-1" << endl;
    else cout << A[ans].pA << endl;

    return 0;
}