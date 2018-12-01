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

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    freopen("art.in", "r", stdin);
    freopen("art.out", "w", stdout);

    int n; cin >> n;
    set<int> magic;
    int A[n][n]; F0R(i, n) F0R(j, n) cin >> A[i][j];
    F0R(i, n) F0R(j, n) if (A[i][j] != 0) magic.insert(A[i][j]);
    int colorCt = magic.size();
    int colors = n*n;
    int minX[colors+10], maxX[colors + 10], minY[colors+10], maxY[colors+10];
    SET(minX, INF, colors+10);
    SET(maxX, 0, colors+10);
    SET(minY, INF, colors+10);
    SET(maxY, 0, colors+10);

    F0R(i, n) {
        F0R(j, n) {
            int color = A[i][j];
            minX[color] = min(minX[color], i);
            maxX[color] = max(maxX[color], i);
            minY[color] = min(minY[color], j);
            maxY[color] = max(maxY[color], j);
        }
    }

    int count[n][n];
    int delta[n+20];
    set<int> toConsider;
    vi delta2[n+20];
    SET2D(count, 0, n, n);
    FOR(i, 1, n*n+1) {
        if (magic.count(i) > 0) {
            delta2[minX[i]].pb(i);
            delta2[maxX[i]+1].pb(i);
        }
    }
    F0R(i, n) {
        for (int x : delta2[i]) {
            if (toConsider.count(x) > 0) toConsider.erase(x);
            else toConsider.insert(x);
        }

        SET(delta, 0, n+10);

        for (int k : toConsider) {
            if (i >= minX[k] && i <= maxX[k]) {
                delta[minY[k]]++;
                delta[maxY[k] + 1]--;
            }
        }

        int ctr = 0;
        F0R(j, n) {
            ctr += delta[j];
            count[i][j] = ctr;
        }
    }

    bool first[colors + 10];
    SET(first, true, colors+10);

    F0R(i, n) {
        F0R(j, n) {
            if (count[i][j] > 1) {
                first[A[i][j]] = false;
            }
        }
    }

    int ans = 0;
    FOR(i, 1, n*n+1) {
        if (first[i]) ans++;
    }
    if (ans == n*n && colorCt == 1) {
        // that one color most cover up the other colors
        ans -= 1;
    }
    cout << ans << endl;

    return 0;
}