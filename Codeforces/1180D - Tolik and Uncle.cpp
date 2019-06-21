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

    int n, m; cin >> n >> m;
//    vii ans;
    F0R1(vertStart, n/2) {
        F0R1(i, m) {
            cout << vertStart << " " << i << "\n";
            cout << n - vertStart + 1 << " " << m - i + 1 << "\n";
//            ans.pb(mp(vertStart, i));
//            ans.pb(mp(n - vertStart + 1, m - i + 1));
        }
    }
    if (n % 2 != 0) {
        F0R1(i, m / 2) {
            cout << n/2+1 << " " << i << "\n";
            cout << n/2+1 << " " << m - i + 1 << "\n";
//            ans.pb(mp(n/2+1, i));
//            ans.pb(mp(n/2+1, m - i + 1));
        }
        if (m % 2 != 0) {
            cout << n/2+1 << " " << m/2 + 1 << "\n";
//            ans.pb(mp(n/2+1, m / 2 + 1));
        }
    }

    // Checker
//    set<ii> seen;
//    ii prev = ans[0];
//    int ct[n+1][m+1];
//    SET2D(ct, 0, n+1, m+1);
//    ct[prev.pA][prev.pB]++;
//    FOR(i, 1, ans.size()) {
//        ii nxt = ans[i];
//        ii d = mp(nxt.pA - prev.pA, nxt.pB - prev.pB);
//        if (seen.count(d)) {
//            assert(false);
//        } else {
//            seen.insert(d);
//        }
//        ct[nxt.pA][nxt.pB]++;
//        prev = nxt;
//    }
//    F0R1(i, n) F0R1(j, m) assert(ct[i][j] == 1);

//    for (ii x : ans) {
//        cout << x.pA << " " << x.pB << endl;
//    }

    return 0;
}