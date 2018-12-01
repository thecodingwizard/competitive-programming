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

#define MAXN 100100

struct Node {
    Node* left;
    Node* right;
    int val;

    Node() {
        val = 0;
        left = right = NULL;
    }

    Node* getLeft() {
        if (left == NULL) left = new Node;
        return left;
    }

    Node* getRight() {
        if (right == NULL) right = new Node;
        return right;
    }

    void add(int x, int v, int lo, int hi) {
        val += v;
        if (hi - lo == 1) return;
        int mid = (lo + hi)/2;
        if (mid <= x) {
            getRight()->add(x, v, mid, hi);
        } else {
            getLeft()->add(x, v, lo, mid);
        }
    }

    int query(int a, int b, int lo, int hi) {
        if (a <= lo && b >= hi) return val;
        else if (hi <= a || b <= lo) return 0;
        int mid = (lo + hi)/2;
        return (left ? left->query(a, b, lo, mid) : 0) + (right ? right->query(a, b, mid, hi) : 0);
    }
};

Node BIT[MAXN];

void bit_add(int idx, int y, int val) {
    for (; idx < MAXN; idx += LSOne(idx)) {
        BIT[idx].add(y, val, 0, MAXN);
    }
}

int bit_query(int y0, int y1, int idx) {
    int sum = 0;
    for (; idx; idx -= LSOne(idx)) {
        sum += BIT[idx].query(y0, y1, 0, MAXN);
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    freopen("friendcross.in", "r", stdin);
    freopen("friendcross.out", "w", stdout);

    int n, k; cin >> n >> k;
    int A[n], B[n], revA[n], revB[n];
    F0R(i, n) {
        cin >> A[i];
        A[i];
        revA[A[i]] = i+1;
    }
    F0R(i, n) {
        cin >> B[i];
        B[i];
        revB[B[i]] = i+1;
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
        // query (point.pA.pB ... n, 0 ... point.pB - k - 1, point.pB + k + 1 ... n)
        if (point.pB - k >= 0) ans += bit_query(0, point.pB - k, point.pA.pB);
        if (point.pB + k <= n+5) ans += bit_query(point.pB + k + 1, n+10, point.pA.pB);
        // update tree
        bit_add(point.pA.pB, point.pB, 1);
    }
    cout << ans << endl;

    return 0;
}