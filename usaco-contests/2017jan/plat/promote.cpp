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

int n;
int A[100001];
int pa[100001];
int idx[100001];
vi children[100001];
int childrenCt[100001];
int ans[100001];

int dfs(int node, int startIdx) {
    idx[node] = startIdx;
    int childCt = 0;
    for (int child : children[node]) {
        childCt += dfs(child, startIdx + childCt + 1) + 1;
    }
    return childrenCt[node] = childCt;
}

int main() {
    freopen("promote.in", "r", stdin);
    freopen("promote.out", "w", stdout);

    cin >> n;
    vii ratings;
    F0R(i, n) {
        cin >> A[i];
        ratings.pb(mp(A[i], i+1));
    }
    SORT(ratings);
    reverse(ratings.begin(), ratings.end());
    pa[1] = 0;
    F0R(i, n-1) {
        int p; cin >> p;
        pa[i] = p;
        children[p].pb(i+2);
    }

    FenwickTree ft(n+10);
    dfs(1, 1);
    for (ii cow : ratings) {
        ans[cow.pB] = ft.rsq(idx[cow.pB], idx[cow.pB] + childrenCt[cow.pB]);
        ft.adjust(idx[cow.pB], 1);
    }
    F0R1(i, n) {
        cout << ans[i] << endl;
    }

    return 0;
}