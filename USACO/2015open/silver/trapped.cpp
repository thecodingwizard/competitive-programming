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

#define INF 1000000000
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

int main() {
    freopen("trapped.in", "r", stdin);
    freopen("trapped.out", "w", stdout);

    int n, b; cin >> n >> b;
    vii haybales;
    F0R(i, n) {
        int a, b; cin >> a >> b;
        haybales.push_back(mp(b, a));
    }
    SORT(haybales);

    int before = -1, after = INF;
    F0R(i, n) {
        ii haybale = haybales[i];
        if (haybale.A < b) before = i;
        else { after = i; break; }
    }

    if (before == -1 || after == INF) {
        cout << "-1" << endl;
        return 0;
    }

    int farthest = after;
    int ans = INF;
    F0Rd(i, after) {
        ii haybale = haybales[i];
        while (farthest < n && haybales[farthest].A - haybale.A > haybales[farthest].B) {
            farthest++;
        }
        if (farthest < n) {
            ans = min(ans, haybales[farthest].A - haybale.A - haybale.B);
        }
    }

    farthest = before;
    FOR(i, after, n) {
        ii haybale = haybales[i];
        while (farthest >= 0 && haybale.A - haybales[farthest].A > haybales[farthest].B) {
            farthest--;
        }
        if (farthest >= 0) {
            ans = min(ans, haybale.A - haybales[farthest].A - haybale.B);
        }
    }

    if (ans == INF) cout << "-1" << endl;
    else cout << max(ans, 0) << endl;

    return 0;
}
