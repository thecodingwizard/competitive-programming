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

#define MAXN 100002

struct Node {
    int val = 0;
    int l = -1, r = -1;
};

Node magic[20000100];
int idx = 100005;

int getLeft(int self) {
    if (magic[self].l == -1) {
        magic[self].l = idx++;
    }
    return magic[self].l;
}

int getRight(int self) {
    if (magic[self].r == -1) {
        magic[self].r = idx++;
    }
    return magic[self].r;
}

void add(int self, int x, int v, int lo, int hi) {
    magic[self].val += v;
    if (hi - lo == 1) return;
    int mid = (lo + hi)/2;
    if (mid <= x) {
        add(getRight(self), x, v, mid, hi);
    } else {
        add(getLeft(self), x, v, lo, mid);
    }
}

int query(int self, int a, int b, int lo, int hi) {
    if (a <= lo && b >= hi) return 0;
    else if (hi <= a || b <= lo) return magic[self].val;
    int mid = (lo + hi)/2;
    int l = magic[self].l, r = magic[self].r;
    return ((l != -1) ? query(l, a, b, lo, mid) : 0) + ((r != -1) ? query(r, a, b, mid, hi) : 0);
}

void bit_add(int idx, int y, int val) {
    for (; idx < MAXN; idx += LSOne(idx)) {
        add(idx, y, val, 0, MAXN);
    }
}

int bit_query(int y0, int y1, int idx) {
    int sum = 0;
    for (; idx; idx -= LSOne(idx)) {
        sum += query(idx, y0, y1, 0, MAXN);
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    freopen("friendcross.in", "r", stdin);
    freopen("friendcross.out", "w", stdout);

    int n, k, tmp; cin >> n >> k;
    int revA[n], revB[n];
    F0R(i, n) {
        cin >> tmp;
        revA[tmp] = i+1;
    }
    F0R(i, n) {
        cin >> tmp;
        revB[tmp] = i+1;
    }
    viii points;
    F0R1(i, n) {
        points.emplace_back(mp(revA[i], revB[i]), i);
    }
    sort(points.begin(), points.end(), [](const iii &a, const iii &b) {
        return a.pA.pA == b.pA.pA ? a.pA.pB > b.pA.pB : a.pA.pA > b.pA.pA;
    });

    ll ans = 0;
    for (iii point : points) {
//        if (point.pB - k >= 0) ans += bit_query(0, point.pB - k, point.pA.pB);
//        if (point.pB + k <= n) ans += bit_query(point.pB + k + 1, n+1, point.pA.pB);
        ans += bit_query(max(0, point.pB - k), min(n+1, point.pB + k + 1), point.pA.pB);
        bit_add(point.pA.pB, point.pB, 1);
    }
    cout << ans << endl;

    return 0;
}