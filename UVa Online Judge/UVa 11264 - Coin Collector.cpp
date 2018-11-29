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
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        long long coins[n];
        for (int i = 0; i < n; i++) cin >> coins[i];

        long long sum = 0, ct = 0;
        for (int j = 0; j < n; j++) {
            if (j != n - 1 && sum + coins[j] >= coins[j+1]) continue;
            ct++;
            sum += coins[j];
        }
        cout << ct << endl;
    }
    return 0;
}