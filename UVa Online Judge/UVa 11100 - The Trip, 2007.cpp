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
    bool first = true;
    while (cin >> n && n) {
        if (first) first = false;
        else cout << endl;
        int bags[n];
        for (int i = 0; i < n; i++) cin >> bags[i];
        sort(bags, bags + n);
        int pieces = 1, counter = 1;
        for (int i = 0; i < n - 1; i++) {
            if (bags[i] == bags[i + 1]) {
                counter++;
                pieces = max(pieces, counter);
            } else {
                counter = 1;
            }
        }
        cout << pieces << endl;
        for (int i = 0; i < pieces; i++) {
            bool space = false;
            for (int j = i; j < n; j += pieces) {
                if (space) cout << " ";
                else space = true;
                cout << bags[j];
            }
            cout << endl;
        }
    }
    return 0;
}