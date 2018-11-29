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

int n, m, p, f;
int memo[10201][101];
int val[101], weight[101];

int dp(int moneySpent, int item) {
    if (item == n) {
        if (moneySpent <= m || (moneySpent > 2000 && moneySpent <= m+200)) return 0;
        return -500000;
    }
    if (memo[moneySpent][item] != -1) return memo[moneySpent][item];
    int money = m-moneySpent;
    if (money+200 >= weight[item]) {
        int with = dp(moneySpent + weight[item], item+1);
        int without = dp(moneySpent, item+1);
        return memo[moneySpent][item] = max(with + val[item], without);
    } else {
        int without = dp(moneySpent, item+1);
        return memo[moneySpent][item] = without;
    }
}

int main() {
    while (cin >> m >> n) {
        memset(memo, -1, sizeof(int)*10201*101);
        for (int i = 0; i < n; i++) cin >> weight[i] >> val[i];
        cout << dp(0, 0) << endl;
    }
    return 0;
}
