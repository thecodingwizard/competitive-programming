/*
 * Lemma: With three vectors v_1, v_2, v_3, there's a way to assign signs to them s.t.
 * |v_1 +/- v_2 +/- v_3| <= max(|v_1|, |v_2|, |v_3|)
 */

#include <bits/stdc++.h>

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
#define LL_INF 4500000000000000000LL
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

void setupIO(const string &PROB = "") {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if (PROB.length() != 0) {
        ifstream infile(PROB + ".in");
        if (infile.good()) {
            freopen((PROB + ".in").c_str(), "r", stdin);
            freopen((PROB + ".out").c_str(), "w", stdout);
        }
    }
}

/* ============================ */

int main() {
    setupIO();

    int n; cin >> n;
    vector<pair<pll, int>> A;
    F0R(i, n) {
        int a, b; cin >> a >> b;
        A.pb(mp(mp(a, b), i));
    }
    sort(all(A), [](pair<pll, int> a, pair<pll, int> b) {
        return hypot(a.pA.pA, a.pA.pB) > hypot(b.pA.pA, b.pA.pB);
    });
    int out[n];
    pll a = A[0].pA;
    out[A[0].pB] = 1;
    int idx = 1;
    while (A.size() - idx >= 2) {
        pll b = A[idx++].pA;
        pll c = A[idx++].pA;

        double bestH = INF;
        ii ans;
        pll ans2;
        F0R(i, 2) {
            F0R(j, 2) {
                int x = i == 0 ? 1 : -1;
                int y = j == 0 ? 1 : -1;
                pll d = { a.pA + b.pA*x + c.pA*y, a.pB + b.pB*x + c.pB*y };
                if (hypot(d.pA, d.pB) < bestH) {
                    bestH = hypot(d.pA, d.pB);
                    ans = {x, y};
                    ans2 = d;
                }
            }
        }
        out[A[idx-1].pB] = ans.pB;
        out[A[idx-2].pB] = ans.pA;
        a = ans2;
    }
    if (idx != A.size()) {
        pll op1 = {a.pA + A[idx].pA.pA, a.pB + A[idx].pA.pB};
        pll op2 = {a.pA - A[idx].pA.pA, a.pB - A[idx].pA.pB};
        if (hypot(op1.pA, op1.pB) < hypot(op2.pA, op2.pB)) {
            out[A[idx].pB] = 1;
        } else {
            out[A[idx].pB] = -1;
        }
    }
    F0R(i, n) {
        if (i != 0) cout << " ";
        cout << out[i];
    }
    cout << endl;

    return 0;
}