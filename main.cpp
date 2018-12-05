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

int n, m, k, q;
set<pair<int, ii>> paths;
vii children[200000];
int color[200000];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    freopen("grass.in", "r", stdin);
    freopen("grass.out", "w", stdout);

    cin >> n >> m >> k >> q;
    F0R(i, m) {
        int a, b, l; cin >> a >> b >> l;
        --a; --b;
        children[a].pb(mp(b, l));
        children[b].pb(mp(a, l));
    }
    F0R(i, n) {
        cin >> color[i];
    }

    F0R(i, n) {
        for (ii child : children[i]) {
            if (color[i] != color[child.pA]) {
                paths.insert(mp(child.pB, mp(i, child.pA)));
            }
        }
    }

    F0R(i, q) {
        int a, b; cin >> a >> b;
        --a;
        int prevColor = color[a];
        color[a] = b;
        for (ii child : children[a]) {
            if (prevColor != color[child.pA]) {
                paths.erase(mp(child.pB, mp(a, child.pA)));
                paths.erase(mp(child.pB, mp(child.pA, a)));
            }
            if (color[a] != color[child.pA]) {
                paths.insert(mp(child.pB, mp(a, child.pA)));
                paths.insert(mp(child.pB, mp(child.pA, a)));
            }
        }
        pair<int, ii> best = *paths.begin();
        cout << best.pA << endl;
    }

    return 0;
}