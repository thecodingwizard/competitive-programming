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

int main() {
    int t; cin >> t;
    F0R1(caseNum, t) {
        int n, q; cin >> n >> q;
        ii A[q];
        F0R(i, q) {
            cin >> A[i].pA >> A[i].pB;
            A[i].pB++;
        }
        bool taken[q]; F0R(i, q) taken[i] = false;
        sort(A, A+q);

        viii events;
        F0R(i, q) {
            events.emplace_back(A[i].pA, mp(i, 0));
            events.emplace_back(A[i].pB, mp(i, 1));
        }
        SORT(events);
        int ans = INF;
        F0R(i, q) {
            int takenIdx = -1;
            int toSubtract = 0;
            int subtractIgnore[q]; F0R(i, q) subtractIgnore[i] = 0;
            int minSeats = INF, minIdx = -1;
            for (iii x : events) {
                int u = x.pB.pA;
                if (!x.pB.pB) {
                    // starting
                    if (taken[u]) {
                        if (takenIdx == -1 || A[takenIdx].pB < A[u].pB) {
                            if (takenIdx != -1) toSubtract += x.pA - A[takenIdx].pA;
                            takenIdx = u;
                        }
                    } else {
                        subtractIgnore[u] = toSubtract;
                        if (takenIdx != -1) {
                            subtractIgnore[u] += x.pA - A[takenIdx].pA;
                        }
                    }
                } else {
                    // ending
                    if (taken[u]) {
                        if (takenIdx == u) {
                            toSubtract += A[u].pB - A[u].pA;
                            takenIdx = -1;
                        }
                    } else {
                        int subtracted = toSubtract;
                        if (takenIdx != -1) {
                            subtracted += x.pA - A[takenIdx].pA + 1;
                        }
                        subtracted -= subtractIgnore[u];
                        int seats = A[u].pB - A[u].pA - subtracted;
                        if (minSeats > seats) {
                            minSeats = seats;
                            minIdx = u;
                        }
                    }
                }
            }
            assert(minIdx != -1);
            taken[minIdx] = true;
            MIN(ans, minSeats);
            assert(minSeats >= 0);
        }

        cout << "Case #" << caseNum << ": " << ans << endl;
    }

    return 0;
}
