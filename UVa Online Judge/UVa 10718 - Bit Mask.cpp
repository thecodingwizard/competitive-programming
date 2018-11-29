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

using namespace std;

#define INF 1000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
typedef vector<int> vi;

int main() {
    long long n, l, u, ans;
    while (cin >> n >> l >> u) {
        ans = 0;
        for (long long i = 31; i >= 0; i--) {
            if (n & (1LL << i)) {
                if ((1LL << i) <= l - ans) ans |= (1LL << i);
            } else {
                if ((1LL << i) <= u - ans) ans |= (1LL << i);
            }
        }
        cout << ans << endl;
    }
    return 0;
}