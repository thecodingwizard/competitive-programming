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

void fastscan(int &n) {
    bool negative = false;
    register int c;
    n = 0;
    c = getchar();
    if (c == '-') {
        negative = true;
        c = getchar();
    }
    for (; (c > 47 && c < 58); c = getchar()) { n = n * 10 + c - 48; }
    if (negative) { n *= -1; }
}

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

struct point {
    double x, y;   // only used if more precision is needed
    point() { x = y = 0.0; }                      // default constructor
    point(double _x, double _y) : x(_x), y(_y) {}        // user-defined
    bool operator<(point other) const { // override less than operator
        if (fabs(x - other.x) > EPS)                 // useful for sorting
            return x < other.x;          // first criteria , by x-coordinate
        return y < other.y;
    }          // second criteria, by y-coordinate
    // use EPS (1e-9) when testing equality of two floating points
    bool operator==(point other) const {
        return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS));
    }
};

int n;
vector<point> A;
int D[300];

int dist(point p1, point p2) {
    return abs(p2.x - p1.x) + abs(p2.y - p1.y);
}

int angle(int x) {
    int x1 = x - 1, x2 = x, x3 = x + 1;
    if (x1 < 0) x1 = n - 1;
    if (x3 >= n) x3 = 0;
    point a = A[x1], b = A[x2], c = A[x3];
    bool res = (a.x - b.x) * (c.y - b.y) - (c.x - b.x) * (a.y - b.y) > 0;
    if (res) return 1;
    return 0;
}

multiset<string> H;

void add(string a) {
    H.insert(a);
}

int main() {
    setupIO("lightsout");

    // Step 1: Read in data
    cin >> n;
    F0R(i, n) {
        int a, b;
        cin >> a >> b;
        A.pb(point(a, b));
    }

    // Step 2: Calculate min distance from each point to exit
    int cwDist[n], ccwDist[n];
    F0R(i, n) {
        if (i == 0) cwDist[i] = 0;
        else cwDist[i] = cwDist[i - 1] + dist(A[i], A[i - 1]);
    }
    ccwDist[0] = 0;
    FORd(i, 1, n) {
        if (i == n - 1) ccwDist[i] = dist(A[0], A[n - 1]);
        else ccwDist[i] = ccwDist[i + 1] + dist(A[i], A[i + 1]);
    }
    F0R(i, n) D[i] = min(cwDist[i], ccwDist[i]);

    // Step 3: Create map of all possible hashes O(n^2)
    FOR(j, 1, n) {
        int i = j;
        string s = "x" + to_string(angle(i)) + ";";
        add(s);
        while (true) {
            i++;
            if (i == n) break;
            s += to_string(dist(A[i], A[i - 1])) + "," + to_string(angle(i)) + ";";
            add(s);
        }
    }

    // Step 4: Simulate walking from every point
    int best = 0;
    FOR(j, 1, n) {
        int i = j;
        string s = "x" + to_string(angle(i)) + ";";
        int curDist = 0;
        while (true) {
            if (H.count(s) == 1) {
                best = max(best, D[i] + curDist - D[j]);
                break;
            }
            i++;
            if (i == n) break;
            s += to_string(dist(A[i], A[i - 1])) + "," + to_string(angle(i)) + ";";
            curDist += dist(A[i], A[i - 1]);
        }
    }
    cout << best << endl;

    return 0;
}

