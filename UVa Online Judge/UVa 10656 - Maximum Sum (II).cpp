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
    while (cin >> n && n) {
        bool first = true;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            if (x > 0) {
                if (first) first = false;
                else cout << " ";
                cout << x;
            }
        }
        if (first) cout << "0";
        cout << endl;
    }
    return 0;
}