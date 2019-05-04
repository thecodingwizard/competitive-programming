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
    int t; cin >> t;
    F0R1(caseNum, t) {
        int p, q; cin >> p >> q;
        set<int> interestingX, interestingY;
        interestingX.insert(0); interestingY.insert(0); interestingX.insert(q); interestingY.insert(q);
        vector<pair<ii, char>> lines;
        F0R(i, p) {
            int x, y; char d; cin >> x >> y >> d;
            interestingX.insert(x - 1);
            interestingX.insert(x + 1);
            interestingY.insert(y - 1);
            interestingY.insert(y + 1);
            lines.pb(mp(mp(x, y), d));
        }
        int best = 0;
        ii bestCoord = { 0, 0 };
        for (auto x : interestingX) {
            if (x < 0 || x >= q) continue;
            for (auto y : interestingY) {
                if (y < 0 || y >= q) continue;
                int ct = 0;
                for (auto line : lines) {
                    if (line.pB == 'N') {
                        if (line.pA.pA == y && line.pA.pB > x) ct++;
                    } else if (line.pB == 'E') {
                        if (line.pA.pB == x && line.pA.pA < y) ct++;
                    } else if (line.pB == 'S') {
                        if (line.pA.pA == y && line.pA.pB < x) ct++;
                    } else {
                        if (line.pA.pB == x && line.pA.pA > y) ct++;
                    }
                }
                cout << ct << endl;
                if (ct > best) {
                    best = ct;
                    bestCoord = { x, y };
                }
            }
        }
        cout << "Case #" << caseNum << ": " << bestCoord.pA << " " << bestCoord.pB << endl;
    }

    return 0;
}