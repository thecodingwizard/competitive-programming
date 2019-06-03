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


int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int game[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> game[i][j];
            }
        }

        int selected[n];
        for (int i = 0; i < n; i++) selected[i] = i;

        int ans = INF;
        do {
            int sum = 0;
            for (int i = 0; i < n; i++) {
                sum += game[i][selected[i]];
            }
            ans = min(ans, sum);
        } while (next_permutation(selected, selected + n));
        cout << ans << endl;
    }
    return 0;
}