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

set<pll> stuff[500100];
bool visited[500100];

bool cmp(ll a, ll b) {
    set<pll> A = stuff[a], B = stuff[b];
    if (A.size() != B.size()) {
        return A.size() < B.size();
    }
    return A < B;
}

int main() {
    int n; cin >> n;
    ll A[n][3];
    SET(visited, false, 500100);
    vector<pll> ordered;
    F0R(i, n) {
        F0R(j, 3) {
            cin >> A[i][j];
        }
        FOR(j, 1, 3) {
            stuff[A[i][j]].insert(mp(A[i][0], i));
        }
        ordered.pb(mp(A[i][0], i));
    }
    SORT(ordered);
    reverse(ordered.begin(), ordered.end());

    ll ans = 0;
    for (pll item : ordered) {
        int idx = static_cast<int>(item.pB);
        ll a = A[idx][1], b = A[idx][2];
        if (visited[a] && visited[b]) continue;
        if (visited[b] || cmp(a, b)) {
            // choose a over b
            visited[a] = true;
            stuff[b].erase(item);
            ans += item.pA;
        } else {
            visited[b] = true;
            stuff[a].erase(item);
            ans += item.pA;
        }
    }
    cout << ans << endl;

    return 0;
}