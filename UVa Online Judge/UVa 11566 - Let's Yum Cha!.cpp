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
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int N, x, T, K;
int weight[300];
double val[300];
double memo[1101][201][23];

double dp(int money, int item, int dishes) {
    if (item == K*2 || dishes == N*2) return 0;
    if (memo[money][item][dishes] != -1) return memo[money][item][dishes];
    if (money >= weight[item]) {
        return memo[money][item][dishes] = max(dp(money - weight[item], item+1, dishes+1)+val[item], dp(money, item+1, dishes));
    }
    return memo[money][item][dishes] = dp(money, item+1, dishes);
}

int main() {
    while (cin >> N >> x >> T >> K && (N || x || T || K)) {
        N++;
        for (int i = 0; i < 1101; i++) for (int j = 0; j < 201; j++) for (int k = 0; k < 23; k++) memo[i][j][k] = -1;
        for (int i = 0; i < K; i++) {
            cin >> weight[i];
            double sum = 0, tmp;
            for (int j = 0; j < N; j++) { cin >> tmp; sum += tmp; }
            val[i] = sum / double(N);
        }
        for (int i = 0; i < K; i++) {
            weight[i+K] = weight[i];
            val[i+K] = val[i];
        }


        printf("%0.2f\n", dp((int)floor(N * x / 1.1L) - N * T, 0, 0));
    }
    return 0;
}
