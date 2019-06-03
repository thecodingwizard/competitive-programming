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
    int N;
    cin >> N;
    while (N--) {
        int A, B, C;
        cin >> A >> B >> C;
        for (int x = -100; x <= 22; x++) {
            for (int y = x+1; y <= 100; y++) {
                int z = A - x - y;
                if (z == x || z == y) continue;
                if (x*y*z!=B) continue;
                if (x*x+y*y+z*z!=C) continue;
                cout << x << " " << y << " " << z << endl;
                goto good;
            }
        }

        cout << "No solution." << endl;

        good:
        continue;
    }
    return 0;
}