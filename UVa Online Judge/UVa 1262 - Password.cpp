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

char grid[6][5];
char grid2[6][5];
set<char> same[5];

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        n--;
        for (int i = 0; i < 5; i++) same[i].clear();
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 5; j++) {
                cin >> grid[i][j];
            }
        }
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 5; j++) {
                cin >> grid2[i][j];
            }
        }
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 5; j++) {
                char c = grid[i][j];
                for (int k = 0; k < 6; k++) {
                    if (c == grid2[k][j]) same[j].insert(c);
                }
            }
        }
        int fifth = 1;
        int fourth = same[4].size() * fifth;
        int third = same[3].size() * fourth;
        int second = same[2].size() * third;
        int first = same[1].size() * second;

        if (fourth == 0 || third == 0 || second == 0 || first == 0) {
            cout << "NO" << endl;
            continue;
        }

        int firstIndex = n / first;
        n = n % first;
        int secondIndex = n / second;
        n = n % second;
        int thirdIndex = n / third;
        n = n % third;
        int fourthIndex = n / fourth;
        n = n % fourth;
        int fifthIndex = n / fifth;
        if (firstIndex >= same[0].size() || secondIndex >= same[1].size() || thirdIndex >= same[2].size() || fourthIndex >= same[3].size() || fifthIndex >= same[4].size()) {
            cout << "NO" << endl;
        } else {
            cout << *next(same[0].begin(), firstIndex) << *next(same[1].begin(), secondIndex) << *next(same[2].begin(), thirdIndex) << *next(same[3].begin(), fourthIndex) << *next(same[4].begin(), fifthIndex) << endl;
        }
    }
    return 0;
}