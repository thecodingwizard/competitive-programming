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

// distance A[i][j][k]
// Time it takes to walk from j'th hole in the i'th floor
// to the k'th hole on the (i+1)'th hole.
int A[150][20][20];
bool visited[150][20];
int dist[150][20];
vii S;
int n, m;

void topoSort(int curFloor, int curHole) {
    if (curFloor == n-1) return;
    visited[curFloor][curHole] = true;
    F0R(i, m) {
        if (!visited[curFloor+1][i]) {
            topoSort(curFloor + 1, i);
        }
    }
    S.pb(mp(curFloor, curHole));
}

int main() {
    string name;
    while (cin >> name) {
        SET3D(A, INF, 150, 20, 20);
        SET2D(visited, false, 150, 20);
        SET2D(dist, INF, 150, 20);
        S.clear();
        cin >> n >> m;
        F0R(i, n-1) {
            F0R(j, m) {
                F0R(k, m) {
                    cin >> A[i][j][k];
                }
            }
        }

        F0R(i, m) {
            topoSort(0, i);
            dist[0][i] = 0;
        }

        reverse(S.begin(), S.end());

        for (ii x : S) {
            F0R(i, m) {
                MIN(dist[x.pA+1][i], dist[x.pA][x.pB] + A[x.pA][x.pB][i]);
            }
        }

        int ans = INF;
        F0R(i, m) MIN(ans, dist[n-1][i]);

        cout << name << endl;
        cout << ans + (n-1)*2 << endl;
    }

    return 0;
}
