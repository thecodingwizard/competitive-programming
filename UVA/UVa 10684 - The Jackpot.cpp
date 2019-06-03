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
    int n, nums[10001];
    while (cin >> n && n) {
        for (int i = 0; i < n; i++) cin >> nums[i];
        int ans = -1, sum = 0;
        for (int i = 0; i < n; i++) {
            sum += nums[i];
            if (sum < 0) sum = 0;
            ans = max(ans, sum);
        }
        if (ans <= 0) {
            cout << "Losing streak." << endl;
        } else {
            cout << "The maximum winning streak is " << ans << "." << endl;
        }
    }
    return 0;
}