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
    int testCases;
    cin >> testCases;
    int A, B, C;
    long long sum[21][21][21]; // sum[i][j][k] = sum of rect with corners (0, 0) and (i, j) at layer k
    while (testCases--) {
        cin >> A >> B >> C;
        for (int i = 0; i < A; i++) {
            for (int j = 0; j < B; j++) {
                for (int k = 0; k < C; k++) {
                    cin >> sum[i][j][k];
                    if (j > 0) sum[i][j][k] += sum[i][j - 1][k];
                    if (i > 0) sum[i][j][k] += sum[i - 1][j][k];
                    if (i > 0 && j > 0) sum[i][j][k] -= sum[i - 1][j - 1][k];
                }
            }
        }
        long long ans = -(1LL << 32), val;
        for (int i = 0; i < A; i++) {
            for (int j = 0; j < B; j++) {
                for (int k = i; k < A; k++) {
                    for (int l = j; l < B; l++) {
                        // greedy 1-D Max Sum
                        val = 0;
                        for (int z = 0; z < C; z++) {
                            val += sum[k][l][z];
                            if (i > 0) val -= sum[i - 1][l][z];
                            if (j > 0) val -= sum[k][j - 1][z];
                            if (i > 0 && j > 0) val += sum[i - 1][j - 1][z];
                            ans = max(ans, val);
                            if (val < 0) val = 0;
                        }
                    }
                }
            }
        }
        cout << ans << endl;
        if (testCases) cout << endl;
    }
    return 0;
}