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
    int k;
    bool flag = true;
    while (cin >> k && k) {
        if (flag) {
            flag = false;
        } else {
            cout << endl;
        }
        int nums[k];
        for (int i = 0; i < k; i++) {
            cin >> nums[i];
        }

        for (int a = 0; a < k; a++) {
            for (int b = a + 1; b < k; b++) {
                for (int c = b + 1; c < k; c++) {
                    for (int d = c + 1; d < k; d++) {
                        for (int e = d + 1; e < k; e++) {
                            for (int f = e + 1; f < k; f++) {
                                printf("%d %d %d %d %d %d\n", nums[a], nums[b], nums[c], nums[d], nums[e], nums[f]);
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}