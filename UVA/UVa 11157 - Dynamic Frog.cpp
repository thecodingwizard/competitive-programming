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

int n, d, t;
vi stones;

int main() {
    cin >> t;
    for (int caseNum = 1; caseNum <= t; caseNum++) {
        cin >> n >> d;
        stones.clear();
        for (int i = 0; i < n; i++) {
            char c, x;
            int y;
            cin >> c >> x >> y;
            stones.push_back(y);
            if (c == 'B') {
                stones.push_back(y);
            }
        }
        sort(stones.begin(), stones.end());

        int prev = 0, ans = 0;
        n = stones.size();
        for (int i = 0; i < n; i += 2) {
            ans = max(ans, stones[i] - prev);
            prev = stones[i];
        }
        ans = max(ans, d - prev);
        prev = d;
        for (int i = n % 2 == 0 ? n - 1 : n - 2; i > 0; i -= 2) {
            ans = max(ans, prev - stones[i]);
            prev = stones[i];
        }
        ans = max(ans, prev);

        cout << "Case " << caseNum << ": " << ans << endl;
    }
    return 0;
}