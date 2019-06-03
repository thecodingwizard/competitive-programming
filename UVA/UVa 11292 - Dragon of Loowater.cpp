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
    int n, m;
    while (cin >> n >> m && (n || m)) {
        vi dragon, knights;
        dragon.assign(n, 0);
        knights.assign(m, 0);
        for (int i = 0; i < n; i++) cin >> dragon[i];
        for (int i = 0; i < m; i++) cin >> knights[i];
        sort(dragon.begin(), dragon.end());
        sort(knights.begin(), knights.end());
        int k = 0;
        int cost = 0;
        bool dead = false;
        for (int i = 0; i < dragon.size(); i++) {
            while (knights[k] < dragon[i] && k < m) k++;
            if (k == m) {
                dead = true;
                break;
            }
            cost += knights[k];
            k++;
        }
        if (dead) {
            cout << "Loowater is doomed!" << endl;
        } else {
            cout << cost << endl;
        }
    }
    return 0;
}