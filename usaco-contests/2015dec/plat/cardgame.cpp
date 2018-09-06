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

int main() {
    freopen("cardgame.in", "r", stdin);
    freopen("cardgame.out", "w", stdout);

    int n; cin >> n;
    bool taken[100001];
    SET(taken, false, 100001);
    int elsie[n];
    set<int> bessie;
    set<int> bessie2;
    F0R(i, n) {
        cin >> elsie[i];
        taken[elsie[i]] = true;
    }
    FOR(i, 1, 2*n+1) {
        if (!taken[i]) {
            bessie.insert(i);
            bessie2.insert(i);
        }
    }

    int highCard[n], lowCard[n];
    F0R(i, n) {
        int e = elsie[i];
        auto it = bessie.lower_bound(e);
        if (it == bessie.end()) {
            highCard[i] = i == 0 ? 0 : highCard[i - 1];
        } else {
            bessie.erase(it);
            highCard[i] = i == 0 ? 1 : highCard[i - 1] + 1;
        }
    }
    F0Rd(i, n) {
        int e = elsie[i];
        auto it = bessie2.lower_bound(e);
        if (it == bessie2.begin()) {
            lowCard[i] = i == n-1 ? 0 : lowCard[i + 1];
        } else {
            it--;
            bessie2.erase(it);
            lowCard[i] = i == n - 1 ? 1 : lowCard[i + 1] + 1;
        }
    }

    int best = max(lowCard[0], highCard[n-1]);
    F0R(i, n-1) {
        best = max(best, highCard[i] + lowCard[i+1]);
    }
    cout << best << endl;

    return 0;
}
