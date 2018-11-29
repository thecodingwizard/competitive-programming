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
    int n, d, r;
    while (cin >> n >> d >> r && (n || d || r)) {
        vi morning, evening;
        morning.assign(n, 0);
        evening.assign(n, 0);
        for (int i = 0; i < n; i++) cin >> morning[i];
        for (int i = 0; i < n; i++) cin >> evening[i];
        sort(begin(morning), end(morning));
        sort(begin(evening), end(evening));

        int x = 0;
        for (int i = 0; i < n; i++) {
            if (morning[i] + evening[n - i - 1] > d) x += morning[i] + evening[n - i - 1] - d;
        }
        cout << x * r << endl;
    }
    return 0;
}