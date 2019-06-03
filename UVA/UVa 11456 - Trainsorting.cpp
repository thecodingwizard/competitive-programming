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
    int c;
    cin >> c;
    while (c--) {
        int n;
        cin >> n;
        int A[n], L[n], LIS[n], LDS[n], lis = 0, lds = 0;
        for (int i = 0; i < n; i++) cin >> A[n-i-1];

        for (int i = 0; i < n; i++) {
            int pos = lower_bound(L, L + lis, A[i]) - L;
            L[pos] = A[i];
            LIS[i] = pos + 1;
            if (pos + 1 >= lis) lis = pos + 1;
        }
        for (int i = 0; i < n; i++) L[i] = 0;
        for (int i = 0; i < n; i++) {
            int pos = upper_bound(L, L + lds, A[i], [](int a, int b){ return a > b; }) - L;
            L[pos] = A[i];
            LDS[i] = pos + 1;
            if (pos + 1 >= lds) lds = pos + 1;
        }

        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans = max(ans, LIS[i] + LDS[i] - 1);
        }

        cout << ans << endl;
    }
    return 0;
}
