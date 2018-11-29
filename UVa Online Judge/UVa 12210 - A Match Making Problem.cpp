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
    int b, s;
    int c = 1;
    while (cin >> b >> s && (b || s)) {
        vi male, female;
        male.assign(b, 0);
        female.assign(s, 0);
        for (int i = 0; i < b; i++) cin >> male[i];
        for (int i = 0; i < s; i++) cin >> female[i];
        sort(male.begin(), male.end());
        sort(female.begin(), female.end());

        cout << "Case " << c++ << ": " << max(b - s, 0);
        if (b - s > 0) {
            cout << " " << male[0];
        }
        cout << endl;
    }
    return 0;
}