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

#define INF 1000000000

using namespace std;

int main() {
    int N, B, SG, SB, tmp;
    multiset<int, greater<int>> green, blue;

    cin >> N;
    for (int round = 0; round < N; round++) {
        green.clear();
        blue.clear();

        cin >> B >> SG >> SB;
        int greenSoldiers[B];
        int blueSoldiers[B];
        for (int i = 0; i < SG; i++) {
            cin >> tmp;
            green.insert(tmp);
        }
        for (int i = 0; i < SB; i++) {
            cin >> tmp;
            blue.insert(tmp);
        }

        while (!(green.empty() || blue.empty())) {
            auto git = green.begin();
            auto bit = blue.begin();
            int i = 0;
            for (; i < B; i++) {
                if (git == green.end() || bit == blue.end()) {
                    break;
                }
                greenSoldiers[i] = *git;
                blueSoldiers[i] = *bit;
                green.erase(git++);
                blue.erase(bit++);
            }

            for (int j = 0; j < i; j++) {
                int g = greenSoldiers[j];
                int b = blueSoldiers[j];
                if (g > b) {
                    green.insert(g - b);
                } else if (b > g) {
                    blue.insert(b - g);
                }
            }
        }

        if (green.empty() && blue.empty()) {
            cout << "green and blue died" << endl;
        }
        if (green.empty() && !blue.empty()) {
            cout << "blue wins" << endl;
            for (int soldier : blue) {
                cout << soldier << endl;
            }
        }
        if (!green.empty() && blue.empty()) {
            cout << "green wins" << endl;
            for (int soldier : green) {
                cout << soldier << endl;
            }
        }
        if (round != N - 1) cout << endl;
    }
    return 0;
}