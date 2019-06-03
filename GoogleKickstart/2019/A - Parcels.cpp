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

int r, c;
bool A[250][250];
int dist[250][250];
int ans;
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

int max_x1py1, min_x1py1, max_x1ny1, min_x1ny1;

void run(int k) {
    queue<ii> q;
    SET2D(dist, INF, r, c);
    F0R(i, r) {
        F0R(j, c) {
            if (A[i][j]) {
                dist[i][j] = 0;
                q.push(mp(i, j));
            }
        }
    }
    int curAns = 0;
    while (!q.empty()) {
        ii u = q.front(); q.pop();
        F0R(i, 4) {
            ii v = { u.pA + dx[i], u.pB + dy[i] };
            if (v.pA < 0 || v.pA >= r || v.pB < 0 || v.pB >= c || dist[v.pA][v.pB] != INF) continue;
            dist[v.pA][v.pB] = dist[u.pA][u.pB] + 1;
            if (dist[v.pA][v.pB] > k) {
                MAX(max_x1py1, v.pA + v.pB);
                MAX(max_x1ny1, v.pA - v.pB);
                MIN(min_x1py1, v.pA + v.pB);
                MIN(min_x1ny1, v.pA - v.pB);
            }
            MAX(curAns, dist[v.pA][v.pB]);
            q.push(v);
        }
    }
    MIN(ans, curAns);
}

bool can(int k) {
    max_x1py1 = max_x1ny1 = -INF;
    min_x1py1 = min_x1ny1 = INF;
    run(k);
    if (max_x1py1 == -INF) return true;
    F0R(i, r) {
        F0R(j, c) {
            if (A[i][j]) continue;
            // Try A[i][j] in O(1)
            int a = i + j, b = i - j;
            int dist = 0;
            MAX(dist, abs(max_x1py1 - a));
            MAX(dist, abs(min_x1py1 - a));
            MAX(dist, abs(max_x1ny1 - b));
            MAX(dist, abs(min_x1ny1 - b));
            if (dist <= k) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int t; cin >> t;
    F0R1(caseNum, t) {
        ans = INF;

        cin >> r >> c;
        F0R(i, r) F0R(j, c) {
            char x; cin >> x; A[i][j] = x == '1';
        }

        int lo = 0, hi = 501, mid, ans = 0;
        while (lo < hi) {
            mid = (lo + hi)/2;
            if (can(mid)) {
                ans = mid;
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }

        cout << "Case #" << caseNum << ": " << ans << endl;
    }

    return 0;
}

