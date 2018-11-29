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
    int t;
    cin >> t;
    for (int caseNum = 1; caseNum <= t; caseNum++) {
        int n;
        cin >> n;
        bool fertile[n+10], covered[n+10];
        for (int i = 0; i < n; i++) {
            char c;
            cin >> c;
            fertile[i] = c == '.';
            covered[i] = false;
        }

        int ct = 0;
        for (int i = 1; i <= n; i++) {
            if (fertile[i - 1] && !covered[i - 1]) {
                ct++;
                covered[i - 1] = true;
                covered[i] = true;
                covered[i + 1] = true;
            }
        }
        cout << "Case " << caseNum << ": " << ct << endl;
    }
    return 0;
}