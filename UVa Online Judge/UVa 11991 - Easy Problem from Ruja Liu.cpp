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

#define INF 1000000000

using namespace std;

int main() {
    map<int, vector<int>> data;
    int n, m, k, v, x;
    while (cin >> n >> m) {
        data.clear();
        for (int i = 1; i <= n; i++) {
            cin >> x;
            data[x].push_back(i);
        }
        for (int i = 0; i < m; i++) {
            cin >> k >> v;
            if (data.find(v) == data.end() || data[v].size() < k) {
                cout << "0" << endl;
            } else {
                cout << data[v][k - 1] << endl;
            }
        }
    }
    return 0;
}