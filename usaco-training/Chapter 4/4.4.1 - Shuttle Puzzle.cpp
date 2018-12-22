/*
ID: nathan.18
TASK: shuttle
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

/* For every k in the range 0...n!-1 inclusive, returns a unique permutation of s */
/* See: https://stackoverflow.com/questions/1995328/are-there-any-better-methods-to-do-permutation-of-string */
string permutation(int k, string x) {
    string s = x;
    for (int j = 1; j < s.size(); ++j) {
        swap(s[k % (j + 1)], s[j]);
        k = k / (j + 1);
    }
    return s;
}
int fact(int n) {
    int x = 1;
    while (n > 0) {
        x *= n--;
    }
    return x;
}

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

struct State {
    int mask;
    int empty;
    vi path;
};

int main() {
    setupIO("shuttle");

    int n; cin >> n;
    int init = 0;
    int goal = 0;
    int len = n*2 + 1;
    F0R(i, n) {
        init |= (1 << n + i + 1);
        goal |= (1 << i);
    }


    queue<State> q;
    State initState;
    initState.mask = init;
    initState.empty = n;
    q.push(initState);

    while (!q.empty()) {
        State next = q.front(); q.pop();
        if (next.mask == goal && next.empty == n) {
            // print
            int ct = 0;
            for (int x : next.path) {
                if (ct != 0) {
                    cout << " ";
                }
                cout << (len - x);
                ct++;
                if (ct == 20) {
                    cout << endl;
                    ct = 0;
                }
            }
            if (ct != 0) cout << endl;
            break;
        }
        // left jumps
        if (next.empty < len - 1) {
            int target = next.empty + 2;
            int white = next.mask & (1 << target);
            if (white && !(next.mask & (1 << (target - 1)))) {
                State toAdd;
                int newMask = next.mask;
                newMask |= (1 << next.empty);
                newMask &= ~(1 << target);
                toAdd.mask = newMask;
                toAdd.empty = target;
                for (int x : next.path) toAdd.path.pb(x);
                toAdd.path.pb(target);
                q.push(toAdd);
            }
        }
        // left moves forward
        if (next.empty <= len - 1) {
            int target = next.empty + 1;
            int white = next.mask & (1 << target);
            if (white) {
                State toAdd;
                int newMask = next.mask;
                newMask |= (1 << next.empty);
                newMask &= ~(1 << target);
                toAdd.mask = newMask;
                toAdd.empty = target;
                for (int x : next.path) toAdd.path.pb(x);
                toAdd.path.pb(target);
                q.push(toAdd);
            }
        }
        // right moves forward
        if (next.empty > 0) {
            int target = next.empty - 1;
            int white = next.mask & (1 << target);
            if (!white) {
                State toAdd;
                int newMask = next.mask;
                newMask &= ~(1 << next.empty);
                newMask &= ~(1 << target);
                toAdd.mask = newMask;
                toAdd.empty = target;
                for (int x : next.path) toAdd.path.pb(x);
                toAdd.path.pb(target);
                q.push(toAdd);
            }
        }
        // right jumps
        if (next.empty > 1) {
            int target = next.empty - 2;
            int white = next.mask & (1 << target);
            if (!white && (next.mask & (1 << (target + 1)))) {
                State toAdd;
                int newMask = next.mask;
                newMask &= ~(1 << next.empty);
                newMask &= ~(1 << target);
                toAdd.mask = newMask;
                toAdd.empty = target;
                for (int x : next.path) toAdd.path.pb(x);
                toAdd.path.pb(target);
                q.push(toAdd);
            }
        }
    }

    return 0;
}
