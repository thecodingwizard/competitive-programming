/*
ID: nathan.18
TASK: race3
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

void setupIO(string PROB) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    ifstream infile(PROB + ".in");
    if (infile.good()) {
        freopen((PROB + ".in").c_str(), "r", stdin);
        freopen((PROB + ".out").c_str(), "w", stdout);
    }
}

/* ============================ */

int n = 0;
vi children[50];
bool visited[100];
set<int> l, r;
int forbidden;

bool canReach(int node, int dest) {
    if (visited[node]) return false;
    visited[node] = true;
    if (forbidden == node) return false;
    if (node == dest) return true;
    for (int child : children[node]) {
        if (canReach(child, dest)) return true;
    }
    return false;
}

int main() {
    setupIO("race3");

    int x;
    while (true) {
        while (cin >> x && x != -2) {
            if (x == -1) goto exit;
            if (n != x) children[n].pb(x);
        }
        n++;

        continue;

        exit:
        break;
    }

    vi unavoidable, splitting;
    FOR(i, 1, n-1) {
        forbidden = i;
        SET(visited, false, 100);
        if (!canReach(0, n-1)) unavoidable.pb(i);
    }

    forbidden = -1;
    for (int test : unavoidable) {
        bool good = true;

        l.clear(); r.clear();
        forbidden = test;
        set<int> setChildren;
        for (int child : children[test]) setChildren.insert(child);
        FOR(i, 0, n) {
            if (i == test) continue;
            SET(visited, false, 100);
            if (canReach(i, n-1)) {
                r.insert(i);
            } else {
                SET(visited, false, 100);
                if (canReach(0, i)) {
                    l.insert(i);
                    if (setChildren.count(i) > 0) good = false;
                } else good = false;
            }
        }
        forbidden = -1;

        FOR(i, 1, n-1) {
            if (i == test) continue;
            bool left = l.count(i) > 0;
            for (int child : children[i]) {
                if (child == test) continue;
                if (left && l.count(child) == 0) good = false;
                if (!left && l.count(child) > 0) good = false;
            }
        }
        if (good) splitting.pb(test);
    }

    cout << unavoidable.size();
    for (int x : unavoidable) cout << " " << x;
    cout << endl << splitting.size();
    for (int x : splitting) cout << " " << x;
    cout << endl;

    return 0;
}