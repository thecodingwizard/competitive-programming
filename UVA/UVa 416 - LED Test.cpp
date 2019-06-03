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
#define LSOne(S) (S & (-S))
typedef vector<int> vi;

int N;
int digits[12];
int displays[10] = {
        126, 48, 109, 121, 51, 91, 95, 112, 127, 123
};

bool isValid(int i, int prev, int burnt) {
    if (i == N) return true;
    int digit = digits[i];
    for (int x = 0; x < 8; x++) {
        if ((burnt & (1 << x)) && (digit & (1 << x))) {
            return false;
        }
    }
    for (int num = 0; num <= 9; num++) {
        int display = displays[num];
        bool possible = true;
        for (int x = 0; x < 8; x++) {
            if (!(display & (1 << x)) && (digit & (1 << x))) {
                possible = false;
                break;
            }
        }
        if (possible && (num == prev - 1 || prev == -1)) {
            int prevBurnt = burnt;
            for (int x = 0; x < 8; x++) {
                if ((display & (1 << x)) && !(digit & (1 << x))) {
                    burnt |= (1 << x);
                }
            }
            if (isValid(i + 1, num, burnt)) return true;
            burnt = prevBurnt;
        }
    }
    return false;
}

int main() {
    while (cin >> N && N) {
        for (int i = 0; i < N; i++) {
            char c;
            int digit = 0;
            for (int j = 6; j >= 0; j--) {
                cin >> c;
                if (c == 'Y') digit |= (1 << j);
            }
            digits[i] = digit;
        }
        if (isValid(0, -1, 0)) {
            cout << "MATCH" << endl;
        } else {
            cout << "MISMATCH" << endl;
        }
    }
    return 0;
}