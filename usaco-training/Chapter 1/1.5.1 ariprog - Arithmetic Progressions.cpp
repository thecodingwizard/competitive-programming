/*
ID: nathan.18
TASK: ariprog
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
typedef pair<ii, int> iii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<ll> vl;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    freopen("ariprog.in", "r", stdin);
    freopen("ariprog.out", "w", stdout);

    int n, m; cin >> n >> m;
    bool can[m*m*2+10];
    SET(can, false, m*m*2+10);

    F0R(i, m+1) {
        F0R(j, m+1) {
            can[i*i+j*j] = true;
        }
    }

    vii ans;
    F0R(j, m*m) {
        if (!can[j]) continue;
        FOR(k, 1, (m*m*2+5-j)/(n-1)) {
            bool good = true;
            F0R(i, n) {
                if (j+k*i > m*m*2+5) {
                    throw "Error";
                }
                if (!can[j+k*i]) {
                    good = false;
                    break;
                }
            }
            if (good) {
                ans.pb(mp(k, j));
            }
        }
    }
    SORT(ans);

    for (ii x : ans) {
        cout << x.pB << " " << x.pA << endl;
    }

    if (ans.size() == 0) cout << "NONE" << endl;

    return 0;
}