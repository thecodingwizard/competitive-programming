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

struct SegmentTree {
    int n;
    vi st;
    vi A;

    int build(int p, int l, int r) {
        if (l == r) {
            return st[p] = A[l];
        }
        int lhs = build(p<<1, l, (l+r)/2);
        int rhs = build((p<<1)+1, (l+r)/2+1, r);
        return st[p] = max(lhs, rhs);
    }

    int query(int p, int l, int r, int L, int R) {
        if (l <= L && r >= R) return st[p];
        if (l > R || r < L) return 0;
        int lhs = query(p << 1, l, r, L, (L+R)/2);
        int rhs = query((p << 1) + 1, l, r, (L+R)/2 + 1, R);
        return max(lhs, rhs);
    }
};

int main() {
    int t; cin >> t;
    F0R1(caseNum, t) {
        int n, k; cin >> n >> k;
        int A[n], B[n]; F0R(i, n) cin >> A[i]; F0R(i, n) cin >> B[i];

        ll finalAns = 0;
        set<ii> seen;
        for (int run = 0; run < 2; run++) {
            SegmentTree a, b;
            F0R(i, n) a.A.pb(A[i]);
            F0R(i, n) b.A.pb(B[i]);
            a.st.assign(4*n, 0);
            b.st.assign(4*n, 0);
            a.n = n;
            b.n = n;
            a.build(1, 0, n - 1);
            b.build(1, 0, n - 1);

            F0R(i, n) {
                int lo = i, hi = n, mid, ans = i - 1;
                while (lo < hi) {
                    mid = (lo + hi)/2;
                    int aMax = a.query(1, i, mid, 0, n-1);
                    if (aMax == A[i]) {
                        ans = mid + 1;
                        lo = mid + 1;
                    } else {
                        hi = mid;
                    }
                }
                lo = i;
                int maxA = ans;
                hi = ans;
                ans = -1;
                while (lo < hi) {
                    mid = (lo + hi)/2;
                    int bMax = b.query(1, i, mid, 0, n-1);
                    if (A[i] - k > bMax) {
                        lo = mid + 1;
                    } else {
                        ans = mid;
                        hi = mid;
                    }
                }
                if (ans == -1) continue;
                int lower = ans;
                ans = -1;
                lo = lower;
                hi = maxA;
                while (lo < hi) {
                    mid = (lo + hi)/2;
                    int bMax = b.query(1, i, mid, 0, n-1);
                    if (A[i] + k < bMax) {
                        hi = mid;
                    } else {
                        lo = mid + 1;
                        ans = mid + 1;
                    }
                }
                if (ans == -1) continue;
                int upper = ans;
                if (run == 0) {
                    if (A[lower] == A[upper - 1]) {
                        seen.insert(mp(lower, upper));
                    }
                } else {
                    if (A[n - lower - 1] == A[n - upper - 2]) {
                        /* if (seen.count(mp(n - lower - 1, n - upper - 1))) upper--; */
                    }
                }
                finalAns += upper - lower;
                cout << finalAns << endl;
            }

            reverse(A, A+n);
            reverse(B, B+n);
        }

        cout << "Case #" << caseNum << ": " << finalAns << endl;
    }

    return 0;
}
