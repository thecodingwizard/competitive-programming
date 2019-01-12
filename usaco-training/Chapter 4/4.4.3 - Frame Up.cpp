/*
ID: nathan.18
TASK: frameup
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
typedef pair<int, ii> iii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<ll> vl;

void fastscan(int&n) {bool negative=false;register int c;n=0;c=getchar();if(c=='-') {negative=true;c=getchar();}
    for(;(c>47&&c<58);c=getchar()){n=n*10+c-48;}
    if(negative){n*=-1;}}

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

struct frame {
    int maxX = 0, minX = INF, maxY = 0, minY = INF;

    void addPt(int x, int y) {
        maxX = max(maxX, x);
        minX = min(minX, x);
        maxY = max(maxY, y);
        minY = min(minY, y);
    }
};

set<char> children[1000];
vector<vector<char>> ans;
int inDegree[1000];
bool visited[1000];
int magic = 0;
map<char, frame> frames;

vector<char> cur;
void topoSort() {
    for (pair<char, frame> x : frames) {
        char a = x.pA;
        if (inDegree[a] == 0 && !visited[a]) {
            visited[a] = true;
            cur.push_back(a);
            if (cur.size() == magic) {
                vector<char> next(cur);
                ans.pb(next);
            }
            for (char child : children[a]) inDegree[child]--;
            topoSort();
            for (char child : children[a]) inDegree[child]++;
            cur.pop_back();
            visited[a] = false;
        }
    }
}

int main() {
    setupIO("frameup");

    int h, w; cin >> h >> w;
    char grid[h][w]; F0R(i, h) F0R(j, w) cin >> grid[i][j];

    F0R(i, h) F0R(j, w) {
            if (grid[i][j] != '.') frames[grid[i][j]].addPt(i, j);
        }

    for (pair<char, frame> x : frames) {
        frame a = x.pB;
        FOR(i, a.minX, a.maxX + 1) {
            int j = a.minY;
            if (grid[i][j] != x.pA) {
                children[x.pA].insert(grid[i][j]);
            }
            j = a.maxY;
            if (grid[i][j] != x.pA) {
                children[x.pA].insert(grid[i][j]);
            }
        }
        FOR(j, a.minY, a.maxY + 1) {
            int i = a.minX;
            if (grid[i][j] != x.pA) {
                children[x.pA].insert(grid[i][j]);
            }
            i = a.maxX;
            if (grid[i][j] != x.pA) {
                children[x.pA].insert(grid[i][j]);
            }
        }
    }

    SET(inDegree, 0, 1000);
    SET(visited, false, 1000);
    for (pair<char, frame> x : frames) {
        char a = x.pA;
        for (char p : children[a]) inDegree[p]++;
        magic++;
    }
    topoSort();

    SORT(ans);

    for (vector<char> x : ans) {
        for (char y : x) {
            cout << y;
        }
        cout << endl;
    }

    return 0;
}
