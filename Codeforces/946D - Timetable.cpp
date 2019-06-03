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
typedef vector<iii> viii;
typedef vector<ll> vl;

int n, m, k;
vi A[500];

int dp[500][501];
int transition[500][501];

int run(int x, int k) {
    if (x >= n) return 0;
    if (dp[x][k] != -1) return dp[x][k];
    int best = INF;
    F0R(i, k+1) {
        best = min(best, transition[x][i] + run(x + 1, k - i));
    }
    return dp[x][k] = best;
}

int calcTransition(int x) {
    int tmp[501];
    SET(tmp, INF, 501);
    int a = A[x].size();
    F0R(i, a) {
        FOR(j, i, a) {
            tmp[a-(j-i+1)] = min(tmp[a-(j-i+1)], A[x][j]-A[x][i]+1);
        }
    }
    F0R(i, 501) {
        transition[x][i] = min(tmp[i], (i == 0 ? INF : transition[x][i-1]));
        if (i >= a) transition[x][i] = 0;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> k;
    F0R(i, n) {
        F0R(j, m) {
            char c; cin >> c;
            if (c == '1') A[i].pb(j);
        }
    }
    SET2D(dp, -1, 500, 501);
    F0R(i, n) calcTransition(i);
    cout << run(0, k) << endl;

    return 0;
}