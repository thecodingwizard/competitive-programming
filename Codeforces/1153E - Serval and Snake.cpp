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

int main() {
    int n; cin >> n;

    int start = -1, end = -1;
    vi lines;
    for (int i = 1; i <= n; i++) {
        cout << "? " << "1 " << i << " " << n << " " << i << endl;
        int resp; cin >> resp;
        if (resp != 0) {
            if (start == -1) start = end = i;
            else end = i;
            if (resp & 1) {
                lines.pb(i);
            }
        } else if (end != -1) break;
    }
    vii ans;
    if (lines.size() == 2) {
        for (int col : lines) {
            int lo = 1, hi = n + 1, mid;
            while (lo < hi) {
                mid = (lo + hi) / 2;

                cout << "? " << lo << " " << col << " " << mid << " " << col << endl;
                int x;
                cin >> x;

                if (x & 1) {
                    hi = mid;
                } else {
                    lo = mid + 1;
                }
            }
            ans.pb(mp(lo, col));
        }
    } else {
        lines.clear();
        start = end = -1;
        for (int i = 1; i <= n; i++) {
            cout << "? " << i << " 1 " << i << " " << n << endl;
            int resp; cin >> resp;
            if (resp != 0) {
                if (start == -1) start = end = i;
                else end = i;
                if (resp & 1) {
                    lines.pb(i);
                }
            } else if (end != -1) break;
        }
        assert(lines.size() == 2);
        int colAns = -1;
        for (int row : lines) {
            if (colAns == -1) {
                int lo = 1, hi = n + 1, mid;
                while (lo < hi) {
                    mid = (lo + hi) / 2;

                    cout << "? " << row << " " << lo << " " << row << " " << mid << endl;
                    int x;
                    cin >> x;

                    if (x & 1) {
                        hi = mid;
                    } else {
                        lo = mid + 1;
                    }
                }
                colAns = lo;
            }
            ans.pb(mp(row, colAns));
        }
    }
    cout << "!";
    for (ii x : ans) cout << " " << x.pA << " " << x.pB;
    cout << endl;

    return 0;
}
