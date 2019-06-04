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

int n, m, q;

void compose(int *dest, int *start, int *permutation) {
    F0R(i, n) {
        dest[i] = start[permutation[i]];
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    freopen("shuffle.in", "r", stdin);
    freopen("shuffle.out", "w", stdout);

    cin >> n >> m >> q;
    int A[n];
    F0R(i, n) {
        if (i < m) {
            int x; cin >> x;
            A[i] = x - 2;
            if (A[i] < 0) A[i] = n-1;
        } else {
            A[i] = i-1;
        }
    }
    int C[n]; F0R(i, n) C[i] = i;
    int functions[32][n];
    F0R(j, n) {
        functions[0][A[j]] = C[j];
    }

    F0R1(i, 31) {
        compose(functions[i], functions[i-1], functions[i-1]);
    }

    int x = n - m + 1;
    int in[n];
    F0Rd(i, 32) {
        if (x & (1 << i)) {
            F0R(j, n) in[j] = C[j];
            compose(C, in, functions[i]);
        }
    }

    reverse(C, C+n);

    F0R(i, q) {
        int x; cin >> x;
        cout << C[(x+n-m)%n]+1 << endl;
    }

    return 0;
}