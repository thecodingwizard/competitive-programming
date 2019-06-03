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
#define LSOne(S) (S & (-S))
typedef vector<int> vi;


int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, p;
        cin >> n >> p;
        int bars[p];
        for (int i = 0; i < p; i++) cin >> bars[i];
        for (int i = 0; i < (1 << p); i++) {
            int sum = 0;
            for (int j = 0; j < p; j++) {
                if (i & (1 << j)) {
                    sum += bars[j];
                }
            }
            if (sum == n) {
                cout << "YES" << endl;
                goto good;
            }
        }
        cout << "NO" << endl;
        good: continue;
    }
    return 0;
}