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
#include <cstring>
#include <iomanip>

using namespace std;

#define INF 1000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
typedef vector<int> vi;

int memo[210][20][60];
int N, M, D, Q;
long long val[220];

int dp(int idx, int remaining, long long modulo) {
    if (memo[idx][remaining][modulo+D] != -1) return memo[idx][remaining][modulo+D];

    if ((modulo != 0 && remaining == 0) || idx > N) return memo[idx][remaining][modulo+D] = 0;
    if (modulo == 0 && remaining == 0) return memo[idx][remaining][modulo+D] = 1;

    return memo[idx][remaining][modulo+D] = dp(idx + 1, remaining - 1, (modulo + val[idx]) % D) + dp(idx + 1, remaining, modulo);
}

int main() {
    int x = 1;
    while (cin >> N >> Q && (N || Q)) {
        for (int i = 0; i < N; i++) cin >> val[i];
        cout << "SET " << x++ << ":" << endl;
        for (int q = 1; q <= Q; q++) {
            memset(memo, -1, sizeof(int) * 210 * 20 * 60);
            cin >> D >> M;
            cout << "QUERY " << q << ": " << dp(0, M, 0) << endl;
        }
    }
    return 0;
}
