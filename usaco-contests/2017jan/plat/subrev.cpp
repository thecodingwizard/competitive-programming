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
typedef pair<ii, int> iii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vl;

int n, A[51];
int dp[51][51][51][51];

int run(int start, int end, int lo, int hi) {
    if (start >= end) {
        return A[start] >= lo && A[end] <= hi && start == end ? 1 : 0;
    }
    if (dp[start][end][lo][hi] != -1) return dp[start][end][lo][hi];
    int optimal = -1;
    // take left
    if (A[start] >= lo && A[start] <= hi) {
        optimal = max(optimal, run(start + 1, end, A[start], hi) + 1);
    }

    // take right
    if (A[end] <= hi && A[end] >= lo) {
        optimal = max(optimal, run(start, end - 1, lo, A[end]) + 1);
    }

    // don't take left
    optimal = max(optimal, run(start + 1, end, lo, hi));

    // don't take right
    optimal = max(optimal, run(start, end - 1, lo, hi));

    // swap
    // take both
    if (A[end] >= lo && A[start] <= hi && A[end] <= hi && A[start] >= lo) {
        optimal = max(optimal, run(start + 1, end - 1, A[end], A[start]) + 2);
    }
    // take left
    if (A[end] >= lo && A[end] <= hi) {
        optimal = max(optimal, run(start + 1, end - 1, A[end], hi) + 1);
    }
    // take right
    if (A[start] >= lo && A[start] <= hi) {
        optimal = max(optimal, run(start + 1, end - 1, lo, A[start]) + 1);
    }

    return dp[start][end][lo][hi] = optimal;
}

int main() {
    freopen("subrev.in", "r", stdin);
    freopen("subrev.out", "w", stdout);

    cin >> n;
    F0R(i, n) cin >> A[i];
    SET4D(dp, -1, 51, 51, 51, 51);

    cout << run(0, n-1, 0, 50) << endl;

    return 0;
}