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
    int n;
    cin >> n;
    int sum[110][110];
    for (int i = 0; i < 105; i++) for (int j = 0; j < 105; j++) sum[i][j] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> sum[i][j];
            if (i > 0) sum[i][j] += sum[i - 1][j];
            if (j > 0) sum[i][j] += sum[i][j - 1];
            if (i > 0 && j > 0) sum[i][j] -= sum[i - 1][j - 1];
        }
    }
    
    int maxSum = -INF;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = i; k < n; k++) {
                for (int l = j; l < n; l++) {
                    int val = sum[k][l];
                    if (i > 0) val -= sum[i - 1][l];
                    if (j > 0) val -= sum[k][j - 1];
                    if (i > 0 && j > 0) val += sum[i - 1][j - 1];
                    maxSum = max(maxSum, val);
                }
            }
        }
    }
    cout << maxSum << endl;
    
    return 0;
}