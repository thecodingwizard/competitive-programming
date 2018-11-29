#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_set>
#include <string>
#define INF 1000000000

using namespace std;

int main() {
    int l;
    while (cin >> l && l) {
        bool sign = true;
        char dir = 'x', c1, c2;
        string tmp;
        for (int i = 1; i < l; i++) {
            cin >> tmp;
            c1 = tmp[0];
            c2 = tmp[1];
            if (tmp == "No") continue;
            if (dir == 'x' && c1 == '-') sign = !sign;
            if (dir == 'y' && c2 == 'y' && c1 == '+') sign = !sign;
            if (dir == 'z' && c2 == 'z' && c1 == '+') sign = !sign;
            if (dir == 'x') dir = c2;
            else if (dir == 'y' && c2 == 'y') dir = 'x';
            else if (dir == 'z' && c2 == 'z') dir = 'x';
        }
        cout << (sign ? '+' : '-') << dir << endl;
    }
    return 0;
}