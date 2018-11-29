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
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int n, computers[10][2];
vi indexes;

double calc(int a, int b) {
    double x = computers[a][0] - computers[b][0];
    double y = computers[a][1] - computers[b][1];
    return 16.00 + sqrt(x*x+y*y);
}

int main() {
    int networkNum = 1;
    while (cin >> n && n) {
        indexes.clear();
        for (int i = 0; i < n; i++) {
            cin >> computers[i][0] >> computers[i][1];
            indexes.push_back(i);
        }

        double shortest = INF;
        vi network;
        do {
            double length = 0;
            double maxLength = -1;
            for (int x = 0; x < n; x++) {
                if (x == n - 1) continue;
                double dist = calc(indexes[x], indexes[x+1]);
                length += dist;
                maxLength = max(maxLength, dist);
            }
            if (length < shortest) {
                shortest = length;
                network = indexes;
            }
        } while (next_permutation(indexes.begin(), indexes.end()));

        cout << "**********************************************************" << endl;
        cout << "Network #" << networkNum++ << endl;

        for (int i = 0; i < n; i++) {
            if (i == n - 1) continue;
            int a = network[i], b = network[i+1];
            printf("Cable requirement to connect (%d,%d) to (%d,%d) is %0.2f feet.\n", computers[a][0], computers[a][1], computers[b][0], computers[b][1], calc(a, b));
        }

        printf("Number of feet of cable required is %0.2f.\n", shortest);
    }
    return 0;
}
