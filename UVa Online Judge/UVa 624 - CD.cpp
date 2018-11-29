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


int N, n;
int tracks[100000];
int best;
unsigned long long bestMask;

void backtrack(int sum, unsigned long long mask, int i) {
    if (i > n) return;
    if (sum > best) {
        best = sum;
        bestMask = mask;
    }
    if (sum + tracks[i] <= N) {
        backtrack(sum + tracks[i], mask | (1 << i), i + 1);
    }
    backtrack(sum, mask, i + 1);
}

int main() {
    while (cin >> N >> n) {
        best = 0;
        for (int i = 0; i < n; i++) cin >> tracks[i];

        backtrack(0, 0, 0);

        for (int i = 0; i < n; i++) {
            if (bestMask & (1 << i)) {
                cout << tracks[i] << " ";
            }
        }
        cout << "sum:" << best << endl;
    }
    return 0;
}