#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_set>
#include <string>
#define INF 1000000000

using namespace std;

int n;
bool differences[3010] = {false};

int main() {
    while (cin >> n) {
        int prev = INF, cur;
        bool bad = false;
        for (int i = 0; i < n; i++) {
            cin >> cur;
            if (prev == INF) {
                prev = cur;
                continue;
            }
            if (abs(prev - cur) < 3010) differences[abs(prev - cur)] = true;
            prev = cur;
        }
        for (int i = 1; i < n; i++) {
            if (!differences[i]) {
                bad = true;
                break;
            }
        }
        if ((bad && n != 1) || n == 0) cout << "Not jolly" << endl;
        else cout << "Jolly" << endl;
        for (bool &difference : differences) {
            difference = false;
        }
    }
    return 0;
}