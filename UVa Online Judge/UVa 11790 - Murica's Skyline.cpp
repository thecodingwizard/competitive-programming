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
    for (int testCase = 1; testCase <= c; testCase++) {
        int n;
        cin >> n;
        int A[n], B[n], LIS[n], LDS[n], lis = 0, lds = 0;
        for (int i = 0; i < n; i++) cin >> A[i];
        for (int i = 0; i < n; i++) cin >> B[i];
        memset(LIS, 0, n*sizeof(int));
        memset(LDS, 0, n*sizeof(int));

        for (int i = 0; i < n; i++) {
            int optimal = B[i];
            for (int j = 0; j < i; j++) {
                if (A[j] >= A[i]) continue;
                optimal = max(optimal, LIS[j] + B[i]);
            }
            LIS[i] = optimal;
            lis = max(lis, optimal);
        }
        for (int i = 0; i < n; i++) {
            int optimal = B[i];
            for (int j = 0; j < i; j++) {
                if (A[j] <= A[i]) continue;
                optimal = max(optimal, LDS[j] + B[i]);
            }
            LDS[i] = optimal;
            lds = max(lds, optimal);
        }

        cout << "Case " << testCase << ". ";
        if (lis >= lds) {
            cout << "Increasing (" << lis<< "). Decreasing (" << lds << ").";
        } else {
            cout << "Decreasing (" << lds << "). Increasing (" << lis << ").";
        }
        cout << endl;
    }
    return 0;
}
