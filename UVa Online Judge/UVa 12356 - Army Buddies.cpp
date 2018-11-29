#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_set>
#include <string>
#include <map>

#define INF 1000000000

using namespace std;

int main() {
    int s, b, l, r;
    int left[100010];
    int right[100010];
    while (cin >> s >> b && (s || b)) {
        for (int i = 1; i <= s; i++) {
            left[i] = i - 1;
            right[i] = i + 1;
        }
        left[1] = -1;
        right[s] = -1;
        while(b-- > 0) {
            cin >> l >> r;
            left[right[r]] = left[l];
            right[left[l]] = right[r];
            if (left[l] != -1) {
                cout << left[l];
            } else {
                cout << "*";
            }
            cout << " ";
            if (right[r] != -1) {
                cout << right[r];
            } else {
                cout << "*";
            }
            cout << endl;
        }
        cout << "-" << endl;
    }

    return 0;
}