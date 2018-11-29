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

int n, m;
int vessels[1000001];
int containers[1001];

bool can(int c) {
    memset(containers, 0, 1001);
    int container_index = 0;
    for (int i = 0; i < n; i++) {
        if (containers[container_index] + vessels[i] > c) container_index++;
        containers[container_index] += vessels[i];
        if (container_index >= m) return false;
        if (containers[container_index] > c) return false;
    }
    return true;
}

int main() {
    while (cin >> n >> m) {
        for (int i = 0; i < n; i++) cin >> vessels[i];
        int lo = 0, hi = 1000000000, mid = 0, ans = 0;
        while (hi - lo > 1) {
            mid = (lo + hi)/2;
            if (can(mid)) { hi = mid; ans = mid; }
            else lo = mid;
        }
        cout << ans << endl;
    }
    return 0;
}