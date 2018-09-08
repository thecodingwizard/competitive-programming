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
#define MOD (int)(2e+9+11)
#define SET(vec, val, size) for (int i = 0; i < size; i++) vec[i] = val;
#define SET2D(arr, val, dim1, dim2) F0R(i, dim1) F0R(j, dim2) arr[i][j] = val;
typedef pair<int, int> ii;
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

FenwickTree ftLeft(100001), ftRight(100001);
int n;

bool can(int m) {
    int lo = 0, hi = 100001, mid;
    while (lo + 1 < hi) {
        mid = (lo + hi)/2;
        int leftTot = ftLeft.rsq(100001);
        int leftBot = ftLeft.rsq(mid);
        int rightTot = ftRight.rsq(100001);
        int rightBot = ftRight.rsq(mid);
        int bot = max(leftBot, rightBot);
        int top = max(leftTot-leftBot, rightTot - rightBot);
        if (top > m && bot > m) return false;
        if (top <= m && bot <= m) return true;
        if (top > m) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    return false;
}

int main() {
    freopen("balancing.in", "r", stdin);
    freopen("balancing.out", "w", stdout);

    cin >> n;
    ii cows[n];
    set<int> yCoords;
    F0R(i, n) {
        cin >> cows[i].A >> cows[i].B;
        yCoords.insert(cows[i].B);
    }
    map<int, int> coordCompress;
    int ctr = 1;
    for (int coord : yCoords) {
        coordCompress[coord] = ctr++;
    }
    sort(cows, cows+n);
    F0R(i, n) {
        cows[i].B = coordCompress[cows[i].B];
        ftRight.adjust(cows[i].B, 1);
    }

    int best = INF;
    F0R(i, n) {
        ftRight.adjust(cows[i].B, -1);
        ftLeft.adjust(cows[i].B, 1);

        int lo = 0, hi = n+10, mid, ans = INF;
        while (lo + 1 < hi) {
            mid = (lo + hi)/2;
            if (can(mid)) {
                hi = mid;
                ans = hi;
            } else {
                lo = mid;
            }
        }
        best = min(best, ans);
    }
    cout << best << endl;

    return 0;
}
