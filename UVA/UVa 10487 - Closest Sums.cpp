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

using namespace std;

#define INF 1000000000
typedef vector<int> vi;

int main() {
    int n, case_num = 1;
    while (cin >> n) {
        if (n == 0) break;
        cout << "Case " << case_num++ << ":" << endl;

        int nums[n];
        for (int i = 0; i < n; i++) {
            cin >> nums[i];
        }
        int m, query, closest = INF;
        cin >> m;
        for (int i = 0; i < m; i++) {
            cin >> query;
            for (int a = 0; a < n; a++) {
                for (int b = 0; b < n; b++) {
                    if (a == b) continue;
                    if (abs(query - nums[b] - nums[a]) < abs(query - closest)) closest = nums[b] + nums[a];
                }
            }

            cout << "Closest sum to " << query << " is " << closest << "." << endl;
        }
    }
    return 0;
}