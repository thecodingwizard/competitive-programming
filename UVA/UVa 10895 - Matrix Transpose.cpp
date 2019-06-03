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
    int m, n, r, val, tmp[80];
    map<int, map<int, int>> data;

    while (cin >> m >> n) {
        data.clear();
        for (int x = 1; x <= m; x++) {
            cin >> r;
            for (int j = 0; j < r; j++) {
                cin >> tmp[j];
            }
            for (int j = 0; j < r; j++) {
                cin >> val;
                int y = tmp[j];
                data[y][x] = val;
            }
        }
        cout << n << " " << m << endl;
        for (int x = 1; x <= n; x++) {
            cout << data[x].size();
            for (auto &it : data[x]) {
                cout << " " << it.first;
            }
            cout << endl;
            bool flag = true;
            for (auto &it : data[x]) {
                if (!flag) {
                    cout << " ";
                } else {
                    flag = false;
                }
                cout << it.second;
            }
            cout << endl;
        }
    }
    return 0;
}