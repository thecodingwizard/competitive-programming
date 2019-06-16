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

struct magic {
    int a, b, c, h;
};

bool operator==(magic a, magic b) {
    return a.a == b.a && a.b == b.b && a.c == b.c && a.h == b.h;
}

int main() {
    setupIO();

    int n, m; cin >> n >> m;
    int A[n][m];
    F0R(i, n) {
        F0R(j, m) {
            char c; cin >> c;
            A[i][j] = c - 'a';
        }
    }
    magic B[n][m];
    F0R(i, n) {
        F0R(j, m) {
            B[i][j].h = -1;
        }
    }
    F0R(j, m) {
        for (int i = 0; i < n;) {
            int tgt = A[i][j];
            int height = 0;
            while (i+height<n&&A[i+height][j] == tgt) height++;
            int stop1 = i + height;
            if (stop1 == n) break;
            int height2 = 0;
            tgt = A[i + height][j];
            while (i+height+height2<n&&A[i+height+height2][j] == tgt) height2++;
            if (height2 != height) {
                if (height2 > height) i = stop1;
                else i += height-height2;
                continue;
            }
            int stop2 = i + height + height2;
            if (stop2 == n) break;
            int height3 = 0;
            tgt = A[i + height+height2][j];
            while (i+height+height2+height3<n&&A[i+height+height2+height3][j] == tgt && height3 != height) height3++;
            if (height3 != height) {
                i = stop1;
                continue;
            }
            int stop3 = i + height + height2 + height3;
            B[i][j].a = A[i][j]; B[i][j].b = A[i+height][j]; B[i][j].c = A[i+height+height2][j];
            B[i][j].h = height;
            i = i + height;
        }
    }

    ll ans = 0;
    F0R(i, n) {
        F0R(j, m) {
            if (B[i][j].h == -1) continue;
            int width = 0;
            while (j+width < m && B[i][j] == B[i][j+width]) width++;
            ans += width*(width+1)/2;
            j += width-1;
        }
    }
    cout << ans << endl;

    return 0;
}