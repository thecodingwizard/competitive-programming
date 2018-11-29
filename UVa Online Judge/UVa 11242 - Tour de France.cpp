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
    int f, r;
    while (cin >> f && f && cin >> r) {
        double front[f], rear[r];
        for (int i = 0; i < f; i++) {
            cin >> front[i];
        }
        for (int i = 0; i < r; i++) {
            cin >> rear[i];
        }

        vector<double> drives;
        for (int i = 0; i < f; i++) {
            for (int j = 0; j < r; j++) {
                drives.push_back(rear[j]/front[i]);
            }
        }

        sort(begin(drives), end(drives));

        double maximum = 0;
        for (int i = 0; i < drives.size() - 1; i++) {
            double d1 = drives[i];
            double d2 = drives[i + 1];
            double spread = d2/d1;
            maximum = max(maximum, spread);
        }

        printf("%0.2f\n", maximum);
    }
    return 0;
}