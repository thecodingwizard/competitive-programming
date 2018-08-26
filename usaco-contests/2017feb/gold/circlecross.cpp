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
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define SORT(vec) sort(vec.begin(), vec.end())

#define INF 1000000010
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define pb push_back
#define PI acos(-1.0)
#define ll long long
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

class FenwickTree {
private:
    vi ft;

public:
    FenwickTree() {}
    // initialization: n + 1 zeroes, ignore index 0
    FenwickTree(int n) { ft.assign(n + 1, 0); }

    int rsq(int b) {                                     // returns RSQ(1, b)
        int sum = 0; for (; b; b -= LSOne(b)) sum += ft[b];
        return sum; }

    int rsq(int a, int b) {                              // returns RSQ(a, b)
        return rsq(b) - (a == 1 ? 0 : rsq(a - 1)); }

    // adjusts value of the k-th element by v (v can be +ve/inc or -ve/dec)
    void adjust(int k, int v) {                    // note: n = ft.size() - 1
        for (; k < (int)ft.size(); k += LSOne(k)) ft[k] += v; }
};

int main() {
    freopen("circlecross.in", "r", stdin);
    freopen("circlecross.out", "w", stdout);

    int n; cin >> n;
    int cows[2*n]; F0R(i, 2*n) cin >> cows[i];
    int pos[2*n]; memset(pos, -1, sizeof pos);

    int ans = 0;
    FenwickTree ft(2*n);
    F0R(i, 2*n) {
        int cow = cows[i];
        if (pos[cow] != -1) {
            int overlaps = i - pos[cow] - 1 - ft.rsq(pos[cow]+1, i);
            ans += overlaps;
            ft.adjust(pos[cow]+1, 1);
            ft.adjust(i+1, 1);
        } else {
            pos[cow] = i;
        }
    }
    cout << ans << endl;

    return 0;
}
