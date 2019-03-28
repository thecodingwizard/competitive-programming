/*
ID: nathan.18
TASK: snail
LANG: C++11
*/

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

int n, b;
char A[120][120];
int best = 0;
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };
int curDist = 0;

void run(int x, int y, int d) {
    /* cout << "run " << x << " " << y << " " << d << endl; */
    assert(d >= 0 && d < 4);
    int a = x + dx[d], b = y + dy[d];
    int oldCurDist = curDist;
    if (a < 0 || a >= n || b < 0 || b >= n || A[a][b] == '#' || A[a][b] == '!') {}
    else {
        while (true) {
            curDist++;
            if (a < 0 || a >= n || b < 0 || b >= n || A[a][b] == '#') {
                curDist--;
                a -= dx[d]; b -= dy[d];
                assert(a >= 0 && a < n && b >= 0 && b < n);
                run(a, b, (d+1)%4);
                run(a, b, (d+3)%4);
                MAX(best, curDist);
                break;
            }
            if (A[a][b] == '!') {
                curDist--;
                a -= dx[d]; b -= dy[d];
                assert(a >= 0 && a < n && b >= 0 && b < n);
                MAX(best, curDist);
                break;
            }
            A[a][b] = '!';
            a += dx[d], b += dy[d];
        }
        while (!(a == x && b == y)) {
            A[a][b] = '.';
            a -= dx[d], b -= dy[d];
            assert(a >= 0 && a < n && b >= 0 && b < n);
        }
    }
    curDist = oldCurDist;
}

int main() {
    setupIO("snail");

    cin >> n >> b;
    F0R(i, n) F0R(j, n) A[i][j] = '.';
    F0R(i, b) {
        char c; int x; cin >> c >> x;
        A[x - 1][c - 'A'] = '#';
    }

    A[0][0] = '!';
    run(0, 0, 1);
    run(0, 0, 2);
    cout << best+1 << endl;
    
    return 0;
}

