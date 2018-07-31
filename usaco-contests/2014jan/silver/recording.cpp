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

using namespace std;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define INF 1100000000
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
    freopen("recording.in", "r", stdin);
    freopen("recording.out", "w", stdout);

    int n; cin >> n;
    vii programs;
    F0R(i, n) {
        int a, b; cin >> a >> b;
        programs.push_back(mp(b, a));
    }
    sort(programs.begin(), programs.end());

    int a = 0, b = 0;
    int ans = 0;
    for (ii program : programs) {
        if (program.B < a) continue;
        if (program.B < b) {
            a = b;
            b = program.A;
            ans++;
        } else {
            b = program.A;
            ans++;
        }
    }
    cout << ans << endl;

    return 0;
}
