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
    for (int a = 1; a <= 500; a++) {
        for (int b = a; b <= 667; b++) {
            for (int c = b; c <= 1000; c++) {
                long long sum = a + b + c;
                long long product = a * b * c;
                if (product <= 1000000) continue;
                long long d = (sum*1000000)/(product-1000000);

                if (d < c || sum + d > 2000) continue;

                if (fabs((a + b + c + d)/100.0 - (a * b * c * d)/100000000.0) < 1e-9) {
                    printf("%0.2f %0.2f %0.2f %0.2f\n", float(a)/100.0, float(b)/100.0, float(c)/100.0, float(d)/100.0);
                }
            }
        }
    }
    return 0;
}