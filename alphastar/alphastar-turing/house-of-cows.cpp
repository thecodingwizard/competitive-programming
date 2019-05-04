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
#define READGRID(arr, dim) F0R(i, dim) F0R(j, dim) cin >> arr[i][j];
typedef pair<int, int> ii;
typedef pair<ii, int> iii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vl;

class FenwickTree {
private:
    vi ft;

public:
    FenwickTree() {}
    FenwickTree(int n) { ft.assign(n + 1, 0); }

    int rsq(int b) {
        int sum = 0; for (; b; b -= LSOne(b)) sum += ft[b];
        return sum; }

    int rsq(int a, int b) {
        return rsq(b) - (a == 1 ? 0 : rsq(a - 1)); }

    void adjust(int k, int v) {
        for (; k < (int)ft.size(); k += LSOne(k)) ft[k] += v; }
};

int ct[150000];
vi stuff[150000];

int main() {
    int n, m; cin >> n >> m;
    SET(ct, 0, 150000);
    F0R(i, m) {
        int x; cin >> x;
        F0R(j, x) {
            int a; cin >> a;
            stuff[i].pb(a);
            ct[a]++;
        }
    }
    ii ans[150000];

    F0R1(i, n) {
        ans[i].pA = 0;
        ans[i].pB = INF;
    }

    FenwickTree FT(m+10);
    F0R(path, m) {
        map<int, ii> nodes;
        for (int i : stuff[path]) nodes[i] = mp(0, 0);
        for (int i : stuff[path]) {
            int val = ct[i];
            FT.adjust(val, 1);
        }
        for (auto const& node : nodes) {
            nodes[node.pA].pB = FT.rsq(ct[node.pA], m+3) - 1;
            nodes[node.pA].pA = FT.rsq(ct[node.pA] + 1, m+3);
        }
        for (int i : stuff[path]) {
            int val = ct[i];
            FT.adjust(val, -1);
        }
        for (auto const& node : nodes) {
            ans[node.pA].pA = max(ans[node.pA].pA, node.pB.pA);
            ans[node.pA].pB = min(ans[node.pA].pB, node.pB.pB);
        }
    }

    F0R1(i, n) {
        cout << ans[i].pA << " " << ans[i].pB << endl;
    }

    return 0;
}