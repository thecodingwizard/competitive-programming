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

using namespace std;

#define INF 1000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
typedef vector<int> vi;

int p, q, r, s, t, u;

double solve(double x) {
    return p * exp(-x) + q * sin(x) + r * cos(x) + s * tan(x) + t * x * x + u;
}

int main() {
    while (cin >> p >> q >> r >> s >> t >> u) {
        bool increasing = solve(0) < solve(1);
        double lo = 0.0, hi = 1.0, mid = 0.0;
        while (fabs(hi - lo) > EPS) {
            mid = (lo + hi)/2.0;
            if (increasing) {
                if (solve(mid) < 0) lo = mid;
                else hi = mid;
            } else {
                if (solve(mid) > 0) lo = mid;
                else hi = mid;
            }
        }
        if (fabs(solve(mid)) > 1e-5) {
            cout << "No solution" << endl;
        } else {
            printf("%0.4f\n", mid);
        }
    }
    return 0;
}