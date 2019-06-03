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
    double k;
    while (cin >> k) {
        double x = INF, y = 1, tmp;
        int count = 0;
        for (; x > y; y++) {
            x = (k * y)/(y-k);

            if (modf(x, &tmp) == 0 && x > 0 && !isinf(x)) {
                // is valid solution
                count++;
            }
            if (x < 0) x = INF;
        }
        cout << count << endl;
        x = INF; y = 1;
        for (; x > y; y++) {
            x = (k * y)/(y-k);

            if (modf(x, &tmp) == 0 && x > 0 && !isinf(x)) {
                // is valid solution
                printf("1/%d = 1/%d + 1/%d\n", int(k), int(x), int(y));
            }
            if (x < 0) x = INF;
        }
    }
    return 0;
}