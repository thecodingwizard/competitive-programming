/*
ID: nathan.18
TASK: frac1
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

using namespace std;

#define INF 1000000000
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define PI acos(-1.0)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int main() {
    freopen("frac1.in", "r", stdin);
    freopen("frac1.out", "w", stdout);

    int n; cin >> n;
    vector<pair<double, ii>> fractions;
    for (int i = 0; i <= n; i++) for (int j = i; j <= n; j++) {
            if (i == 0 && j == 0) continue;
            fractions.push_back(mp(double(i)/double(j), mp(i, j)));
        }
    sort(fractions.begin(), fractions.end());
    double prev = -1;
    for (pair<double, ii> fraction : fractions) {
        if (prev == fraction.A) continue;
        prev = fraction.A;
        cout << fraction.B.A << "/" << fraction.B.B << endl;
    }
    return 0;
}
