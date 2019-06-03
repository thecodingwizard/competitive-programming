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
#include <ctime>
#include <list>

using namespace std;

template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define F0R1(i, a) for (int i=1; i<=(a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
#define F0Rd1(i, a) for (int i=a; i>0; i--)
#define SORT(vec) sort(vec.begin(), vec.end())
#define RSORT(vec) sort(vec.rbegin(), vec.rend())
#define MIN(a, b) a = min(a, b)
#define MAX(a, b) a = max(a, b)

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
#define all(x) (x).begin(), (x).end()

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

class SegmentTree {
private: vi st, A, maxPS;
    int n;
    int left (int p) { return p << 1; }
    int right(int p) { return (p << 1) + 1; }

    void build(int p, int L, int R) {
        if (L == R) {
            st[p] = A[L];
            maxPS[p] = max(A[L], 0);
        } else {
            build(left(p) , L              , (L + R) / 2);
            build(right(p), (L + R) / 2 + 1, R          );
            int p1 = st[left(p)], p2 = st[right(p)];
            st[p] = p1 + p2;
            maxPS[p] = max(maxPS[left(p)], st[left(p)] + maxPS[right(p)]);
            maxPS[p] = max(0, maxPS[p]);
        } }

    int rsq(int p, int L, int R, int i, int j) {
        if (i >  R || j <  L) return -INF;
        if (L >= i && R <= j) return st[p];

        int p1 = rsq(left(p) , L              , (L+R) / 2, i, j);
        int p2 = rsq(right(p), (L+R) / 2 + 1, R          , i, j);

        if (p1 == -INF) return p2;
        if (p2 == -INF) return p1;
        return p1 + p2; }

    int rprefixq(int p, int L, int R, int i, int j) {
        if (i >  R || j <  L) return -INF;
        if (L >= i && R <= j) return maxPS[p];

        int p1 = rprefixq(left(p) , L              , (L+R) / 2, i, j);
        int p2 = rprefixq(right(p), (L+R) / 2 + 1, R          , i, j);

        if (p1 == -INF) return p2;
        if (p2 == -INF) return p1;
        return max(p1, rsq(left(p), L, (L+R)/2, i, j) + p2); }

    int update_point(int p, int L, int R, int idx, int new_value) {
        int i = idx, j = idx;

        if (i > R || j < L)
            return st[p];

        if (L == i && R == j) {
            A[i] = new_value;
            maxPS[p] = max(new_value, 0);
            return st[p] = new_value;
        }

        int p1, p2;
        p1 = update_point(left(p) , L              , (L + R) / 2, idx, new_value);
        p2 = update_point(right(p), (L + R) / 2 + 1, R          , idx, new_value);

        maxPS[p] = max(max(maxPS[left(p)], st[left(p)] + maxPS[right(p)]), 0);
        return st[p] = p1 + p2;
    }

public:
    SegmentTree(const vi &_A) {
        A = _A; n = (int)A.size();
        st.assign(4 * n, 0);
        maxPS.assign(4*n, 0);
        build(1, 0, n - 1);
    }

    int rsq(int i, int j) { return rsq(1, 0, n - 1, i, j); }
    int rprefixq(int i, int j) { return rprefixq(1, 0, n - 1, i, j); }

    int update_point(int idx, int new_value) {
        return update_point(1, 0, n - 1, idx, new_value); }
};

int main() {
    int t; cin >> t;
    F0R1(caseNum, t) {
        int n; cin >> n;
        int s; cin >> s;
        int A[n]; F0R(i, n) cin >> A[i];

        map<int, int> ctr;
        map<int, vi> locations;
        vi initVal;
        F0R(i, n) {
            int next = A[i];
            locations[next].pb(i);
            if (ctr[next] == s) {
                initVal.pb(-s);
            } else if (ctr[next] < s) {
                initVal.pb(1);
            } else {
                initVal.pb(0);
            }
            ctr[next]++;
        }
        SegmentTree ST(initVal);

        int ans = 0;
        map<int, int> indexes;
        F0R(i, n) {
            MAX(ans, ST.rprefixq(i, n - 1));
            int next = A[i];
            int curIdx = indexes[next] + s;
            if (curIdx < locations[next].size()) ST.update_point(locations[next][curIdx], 1);
            if (curIdx < locations[next].size() - 1) ST.update_point(locations[next][curIdx + 1], -s);
            indexes[next]++;
        }
        cout << "Case #" << caseNum << ": " << ans << endl;
    }

    return 0;
}
