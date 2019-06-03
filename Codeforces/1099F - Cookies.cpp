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
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
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
#define MOD2 1000000007
#define SET(vec, val, size) for (int i = 0; i < size; i++) vec[i] = val;
#define SET2D(arr, val, dim1, dim2) F0R(i, dim1) F0R(j, dim2) arr[i][j] = val;
#define SET3D(arr, val, dim1, dim2, dim3) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) arr[i][j][k] = val;
#define SET4D(arr, val, dim1, dim2, dim3, dim4) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) F0R(l, dim4) arr[i][j][k][l] = val;
#define READGRID(arr, dim) F0R(i, dim) F0R(j, dim) cin >> arr[i][j];
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<ll> vl;

void setupIO(const string &PROB) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream infile(PROB + ".in");
    if (infile.good()) {
        freopen((PROB + ".in").c_str(), "r", stdin);
        freopen((PROB + ".out").c_str(), "w", stdout);
    }
}

/* ============================ */

class FenwickTree {
private:
    vector<ll> ft;

public:
    FenwickTree() {}
    FenwickTree(int n) { ft.assign(n + 1, 0); }

    ll rsq(int b) {
        ll sum = 0; for (; b; b -= LSOne(b)) sum += ft[b];
        return sum; }

    ll rsq(int a, int b) {
        return rsq(b) - (a == 1 ? 0 : rsq(a - 1)); }

    void adjust(int k, ll v) {
        for (; k < (int)ft.size(); k += LSOne(k)) ft[k] += v; }
};

int n;
ll t;
ll A[100000];
ll B[100000];
pair<int, ll> P[100000];
vector<pair<int, ll>> children[100000];

FenwickTree cost(1001000);
FenwickTree total(1001000);
ll cookiesAvail[1001000];

ll getNumCookies() {
    if (t < 0) return 0;
    int lo = 1, hi = 1000001, mid, ans = 0;
    while (lo < hi) {
        mid = (lo + hi) / 2;
        if (cost.rsq(mid) <= t) {
            lo = mid + 1;
            ans = mid;
        } else {
            hi = mid;
        }
    }
    ll leftoverTime = (ans != 0) ? t - cost.rsq(ans) : t;
    ll numCookies = (ans != 0) ? total.rsq(ans) : 0;
    ll extraToTake = (ans < 1000000) ? leftoverTime/(ans+1) : 0;
    assert(extraToTake <= cookiesAvail[ans+1]);
    numCookies += extraToTake;
    return numCookies;
}

ll run(int node) {
    cost.adjust(B[node], B[node]*A[node]);
    total.adjust(B[node], A[node]);
    cookiesAvail[B[node]] += A[node];

    ll best = getNumCookies();

    ll bestChild = 0, secondBestChild = 0;
    for (pair<int, ll> child : children[node]) {
        t -= child.pB*2;
        ll contender = run(child.pA);
        if (contender > bestChild) {
            secondBestChild = bestChild;
            bestChild = contender;
        } else if (contender > secondBestChild) {
            secondBestChild = contender;
        }
        t += child.pB*2;
    }

    if (node == 0) best = max(best, bestChild);
    else best = max(best, secondBestChild);

    cost.adjust(B[node], -B[node]*A[node]);
    total.adjust(B[node], -A[node]);
    cookiesAvail[B[node]] -= A[node];

    return best;
}

int main() {
    cin >> n >> t;
    F0R(i, n) cin >> A[i];
    F0R(i, n) cin >> B[i];
    P[0] = { -1, 0 };
    FOR(i, 1, n) {
        int a;
        ll l; cin >> a >> l;
        --a;
        P[i] = { a, l };
        children[a].pb(mp(i, l));
    }
    SET(cookiesAvail, 0, 1001000);

    cout << run(0) << endl;

    return 0;
}