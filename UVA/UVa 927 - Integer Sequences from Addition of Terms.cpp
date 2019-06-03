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
    int C;
    cin >> C;
    while (C--) {
        int i;
        cin >> i;
        int coefficients[i + 1];
        for (int x = 0; x <= i; x++) {
            cin >> coefficients[x];
        }
        int d, k;
        cin >> d >> k;
        int x = 0, a = 1;
        while (x + a*d < k) {
            x += a * d;
            a++;
        }
        long long ans = 0;
        for (x = 0; x <= i; x++) {
            ans += coefficients[x] * pow(a, x);
        }
        cout << ans << endl;
    }
    return 0;
}