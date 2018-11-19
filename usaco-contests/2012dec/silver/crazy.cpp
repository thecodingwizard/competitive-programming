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

// returns the area, which is half the determinant
double area(const vector<ii> &P) {
    double result = 0.0, x1, y1, x2, y2;
    for (int i = 0; i < (int)P.size()-1; i++) {
        x1 = P[i].pA; x2 = P[i+1].pA;
        y1 = P[i].pB; y2 = P[i+1].pB;
        result += (x1 * y2 - x2 * y1);
    }
    return fabs(result) / 2.0; }

struct vec { double x, y;  // name: `vec' is different from STL vector
    vec(double _x, double _y) : x(_x), y(_y) {} };

vec toVec(ii a, ii b) {       // convert 2 points to vector a->b
    return vec(b.pA - a.pA, b.pB - a.pB); }

double dot(vec a, vec b) { return (a.x * b.x + a.y * b.y); }

double norm_sq(vec v) { return v.x * v.x + v.y * v.y; }

double angle(ii a, ii o, ii b) {  // returns angle aob in rad
    vec oa = toVec(o, a), ob = toVec(o, b);
    return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob))); }

double cross(vec a, vec b) { return a.x * b.y - a.y * b.x; }

// note: to accept collinear points, we have to change the `> 0'
// returns true if point r is on the left side of line pq
bool ccw(ii p, ii q, ii r) {
    return cross(toVec(p, q), toVec(p, r)) > 0; }

// returns true if point p is in either convex/concave polygon P
bool inPolygon(ii pt, const vector<ii> &P) {
    if ((int)P.size() == 0) return false;
    double sum = 0;    // assume the first vertex is equal to the last vertex
    for (int i = 0; i < (int)P.size()-1; i++) {
        if (ccw(pt, P[i], P[i+1]))
            sum += angle(P[i], pt, P[i+1]);                   // left turn/ccw
        else sum -= angle(P[i], pt, P[i+1]); }                 // right turn/cw
    return fabs(fabs(sum) - 2*PI) < EPS; }

int main() {
    freopen("crazy.in", "r", stdin);
    freopen("crazy.out", "w", stdout);

    int n, c; cin >> n >> c;
    map<ii, pair<ii, ii>> A;
    vii B;
    F0R(i, n) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        if (A.count(mp(x1, y1))) {
            A[mp(x1, y1)].pB = mp(x2, y2);
        } else {
            A[mp(x1, y1)].pA = mp(x2, y2);
        }
        if (A.count(mp(x2, y2))) {
            A[mp(x2, y2)].pB = mp(x1, y1);
        } else {
            A[mp(x2, y2)].pA = mp(x1, y1);
        }
    }
    F0R(i, c) {
        int a, b; cin >> a >> b;
        B.pb(mp(a, b));
    }
    vector<pair<double, vii>> communities;
    set<ii> visited;
    for (const auto& x : A) {
        if (visited.count(x.pA)) continue;
        vector<ii> toAppend;
        ii next = x.pA;
        while (next.pA != -1) {
            visited.insert(next);
            toAppend.pb(next);
            ii op1 = A[next].pA, op2 = A[next].pB;
            if (visited.count(op1) && visited.count(op2)) {
                next.pA = -1;
            } else if (visited.count(op1)) {
                next = op2;
            } else {
                next = op1;
            }
        }
        toAppend.pb(x.pA);
        communities.pb(mp(area(toAppend), toAppend));
    }
    SORT(communities);

    int ct[1000];
    SET(ct, 0, 1000);

    for (ii cow : B) {
        bool flag = false;
        F0R(i, communities.size()) {
            if (inPolygon(cow, communities[i].pB)) {
                flag = true;
                ct[i]++;
                break;
            }
        }
        if (!flag) ct[999]++;
    }

    int ans = 0;
    F0R(i, communities.size()) {
        ans = max(ans, ct[i]);
    }
    cout << max(ans, ct[999]) << endl;

    return 0;
}