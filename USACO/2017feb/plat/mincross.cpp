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

class FenwickTree {
private:
    vi ft;

public:
    FenwickTree() {}
    FenwickTree(int n) { ft.assign(n + 1, 0); }

    int rsq(int b) {
        int sum = 0; for (; b; b -= LSOne(b)) sum += ft[b];
        return sum; }

    int rsq(int a, int b) {
        return rsq(b) - (a == 1 ? 0 : rsq(a - 1)); }

    void adjust(int k, int v) {
        for (; k < (int)ft.size(); k += LSOne(k)) ft[k] += v; }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    freopen("mincross.in", "r", stdin);
    freopen("mincross.out", "w", stdout);

    int n; cin >> n;
    ii A[n], B[n];
    F0R(i, n) {
        int x; cin >> x;
        A[x-1].pA = i+1;
        B[x-1].pB = i+1;
    }
    F0R(i, n) {
        int x; cin >> x;
        A[x-1].pB = i+1;
        B[x-1].pA = i+1;
    }
    FenwickTree FT(n*2+10);
    FenwickTree FT2(n*2+10);

    sort(A, A+n, [](const ii& a, const ii& b) {
        return a.pA > b.pA;
    });
    sort(B, B+n, [](const ii& a, const ii& b) {
        return a.pA > b.pA;
    });

    ll cur = 0;
    F0R(i, n) {
        cur += FT.rsq(A[i].pB);
        FT.adjust(A[i].pB, 1);
    }
    ll best = cur;

    F0Rd(i, n) {
        cur -= FT.rsq(A[i].pB)-1;
        cur += FT.rsq(A[i].pB, 2*n+10)-1;
        best = min(best, cur);
    }


    cur = 0;
    F0R(i, n) {
        cur += FT2.rsq(B[i].pB);
        FT2.adjust(B[i].pB, 1);
    }
    best = min(best, cur);

    F0Rd(i, n) {
        cur -= FT2.rsq(B[i].pB)-1;
        cur += FT2.rsq(B[i].pB, 2*n+10)-1;
        best = min(best, cur);
    }

    cout << best << endl;

    return 0;
}