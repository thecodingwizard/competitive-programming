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
#define MOD2 1000000007
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

int n, k, inDegree[100000];
set<int> children[100000];

void bad() {
    cout << "No" << endl;
    exit(0);
}

int main() {
    cin >> n >> k;
    F0R(i, n-1) {
        int a, b; cin >> a >> b;
        --a; --b;
        inDegree[a]++;
        inDegree[b]++;
        children[a].insert(b);
        children[b].insert(a);
    }
    set<ii> nodes;
    F0R(i, n) nodes.insert(mp(inDegree[i], i));
    while (true) {
        k--;
        if (nodes.empty()) break;
        map<int, int> dmg;
        while (!nodes.empty()) {
            ii next = *nodes.begin();
            if (next.pA == 1) {
                dmg[*children[next.pB].begin()]++;
                children[*children[next.pB].begin()].erase(next.pB);
                nodes.erase(next);
            } else if (next.pA < 3) {
                bad();
            } else {
                break;
            }
        }
        bool alreadyOne = false;
        for (const auto &x : dmg) {
            nodes.erase(mp(inDegree[x.pA], x.pA));
            if (x.pB < 3) bad();
            inDegree[x.pA] -= x.pB;
            if (inDegree[x.pA] > 0) nodes.insert(mp(inDegree[x.pA], x.pA));
            else if (alreadyOne) bad();
            else alreadyOne = true;
        }
    }
    if (k == -1) cout << "Yes" << endl;
    else cout << "No" << endl;

    return 0;
}
