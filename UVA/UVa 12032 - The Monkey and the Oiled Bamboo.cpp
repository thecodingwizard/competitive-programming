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

int t, n, rungs[100001];

bool can(int k) {
    int cur = 0;
    for (int i = 0; i < n; i++) {
        if (rungs[i] - cur > k) return false;
        if (rungs[i] - cur == k) {
            cur = rungs[i];
            k--;
        } else {
            cur = rungs[i];
        }
    }
    return true;
}

int main() {
    cin >> t;
    for (int c = 1; c <= t; c++) {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> rungs[i];
        int hi = 10000010, lo = 0, mid = 0, ans = 0;
        while (hi - lo > 1) {
            mid = (hi + lo)/2;
            if (can(mid)) { hi = mid; ans = mid; }
            else lo = mid;
        }
        cout << "Case " << c << ": " << ans << endl;
    }
    return 0;
}