/*
ID: nathan.18
TASK: starry
LANG: C++
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

int w, h;
bool A[100][100], visited[100][100], visited2[100][100];
char ans[100][100];
int dx[8] = { -1, -1, -1, 0, 1, 1, 1, 0 };
int dy[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };
int posVal[8] = { 1, 2, 4, 8, 4, 2, 1, 8 };
map<int, int> clusterRotate[4];

void visit(int x, int y) {
    if (visited[x][y]) return;
    visited[x][y] = true;
    int val[8]; SET(val, 0, 8);
    F0R(i, 8) {
        int x1 = x + dx[i], y1 = y + dy[i];
        if (x1 < 0 || x1 >= w || y1 < 0 || y1 >= h) continue;
        if (!A[x1][y1]) continue;
        F0R(j, 4) val[j] += posVal[(i+j*2)%8];
        visit(x1, y1);
    }
    F0R(i, 4) clusterRotate[i][val[i]]++;
}

void assign(int x, int y, char c) {
    if (visited2[x][y]) return;
    visited2[x][y] = true;
    ans[x][y] = c;
    F0R(i, 8) {
        int x1 = x + dx[i], y1 = y + dy[i];
        if (x1 < 0 || x1 >= w || y1 < 0 || y1 >= h) continue;
        if (!A[x1][y1]) continue;
        assign(x1, y1, c);
    }
}

int main() {
    setupIO("starry");
    cin >> h >> w;
    F0R(i, w) F0R(j, h) {
            char c; cin >> c;
            A[i][j] = c == '1';
        }
    SET2D(visited, false, w, h);
    SET2D(visited2, false, w, h);

    map<map<int, int>, char> clusters;
    char ctr = 'a';
    F0R(i, w) {
        F0R(j, h) {
            if (A[i][j] && !visited[i][j]) {
                F0R(x, 4) clusterRotate[x].clear();
                visit(i, j);
                map<int, int> cluster = clusterRotate[0];
                if (clusters.count(cluster) == 0) {
                    F0R(x, 4) {
                        clusters[clusterRotate[x]] = ctr;
                    }
                    ctr++;
                }
                assign(i, j, clusters[cluster]);
            }
            if (!A[i][j]) ans[i][j] = '0';
        }
    }
    F0R(i, w) {
        F0R(j, h) {
            cout << ans[i][j];
        }
        cout << endl;
    }

    return 0;
}

