/*
ID: nathan.18
TASK: job
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
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vl;

int main() {
    freopen("job.in", "r", stdin);
    freopen("job.out", "w", stdout);

    int n, m1, m2; cin >> n >> m1 >> m2;
    int A[m1], B[m2];
    int nextA[m1], nextB[m2];
    F0R(i, m1) cin >> A[i]; F0R(i, m2) cin >> B[i];
    F0R(i, m1) nextA[i] = A[i]; F0R(i, m2) nextB[i] = B[i];

    vi nextTimes;

    F0R(i, n) {
        int bestIdx = 0;
        F0R(j, m1) {
            if (nextA[bestIdx] > nextA[j]) {
                bestIdx = j;
            }
        }
        nextTimes.pb(nextA[bestIdx]);
        nextA[bestIdx] += A[bestIdx];
    }

    SORT(nextTimes);
    int ans1 = nextTimes[n-1];

    int ans2 = 0;
    F0Rd(i, n) {
        int bestIdx = 0;
        F0R(j, m2) {
            if (nextTimes[i] + nextB[j] < nextTimes[i] + nextB[bestIdx]) {
                bestIdx = j;
            }
        }
        ans2 = max(ans2, nextTimes[i] + nextB[bestIdx]);
        nextB[bestIdx] += B[bestIdx];
    }

    cout << ans1 << " " << ans2 << endl;

    return 0;
}