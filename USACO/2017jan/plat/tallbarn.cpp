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
#define READGRID(arr, dim) F0R(i, dim) F0R(j, dim) cin >> arr[i][j];
typedef pair<int, int> ii;
typedef pair<ii, int> iii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vl;

ll n, k;
double A[100000];

pair<double, ll> calc(int i, double goal) {
    ll numNeeded = ceil((-1+sqrt(1+4*A[i]/goal))/2);
    return mp(A[i]/numNeeded, numNeeded);
}

bool can(double goal) {
    ll cows = 0;
    F0R(i, n) {
        cows += calc(i, goal).pB;
    }
    return cows <= k;
}

int main() {
    freopen("tallbarn.in", "r", stdin);
    freopen("tallbarn.out", "w", stdout);

    cin >> n >> k;
    F0R(i, n) cin >> A[i];

    double lo = 0, hi = 1000000000001, ans = 0, mid;
    while (lo + 0.000000000001 < hi) {
        mid = (lo + hi)/2;
        if (can(mid)) {
            hi = mid;
            ans = mid;
        } else {
            lo = mid;
        }
    }

    double finalAns = 0;
    F0R(i, n) {
        finalAns += calc(i, ans).pA;
    }
    cout << (ll)round(finalAns) << endl;

    return 0;
}