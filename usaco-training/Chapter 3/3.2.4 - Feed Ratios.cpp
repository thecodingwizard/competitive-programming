/*
ID: nathan.18
TASK: ratios
LANG: C++11
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
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
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
typedef pair<int, int> ii;
typedef pair<ii, int> iii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vl;

int main() {
    freopen("ratios.in", "r", stdin);
    freopen("ratios.out", "w", stdout);

    int a, b, c; cin >> a >> b >> c;
    int A[3][3];
    F0R(i, 3) F0R(j, 3) cin >> A[i][j];

    int x, y, z;
    map<iii, int> valid;
    FOR(i, 1, 250) {
        valid.insert(mp(mp(mp(a*i, b*i), c*i), i));
    }

    F0R(i, 100)
        F0R(j, 100)
            F0R(k, 100) {
                x = A[0][0]*i + A[1][0]*j + A[2][0]*k;
                y = A[0][1]*i + A[1][1]*j + A[2][1]*k;
                z = A[0][2]*i + A[1][2]*j + A[2][2]*k;
                if (valid.count(mp(mp(x, y), z))) {
                    cout << i << " " << j << " " << k << " " << valid[mp(mp(x, y), z)] << endl;
                    return 0;
                }
            }
    cout << "NONE" << endl;

    return 0;
}
