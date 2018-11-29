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

int N, M, P;
int cost[51][51], save[51], memo[51][4097];
int operaToStore[12];

int tsp(int pos, int mask) {
    if (mask == pow(2, P) - 1) return -cost[pos][0];
    if (memo[pos][mask] != INF) return memo[pos][mask];
    int ans = -cost[pos][0];
    for (int i = 0; i < P; i++) {
        int nxt = operaToStore[i];
        if (nxt == pos || mask & (1 << i) || nxt == -1) continue;
        ans = max(ans, tsp(nxt, mask | (1 << i)) + save[nxt] - cost[pos][nxt]);
    }
    return memo[pos][mask] = ans;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> N >> M;
        for (int i = 0; i < 51; i++) for (int j = 0; j < 51; j++) cost[i][j] = INF;
        memset(save, 0, sizeof save);
        memset(operaToStore, -1, sizeof operaToStore);
        for (int i = 0; i < 51; i++) for (int j = 0; j < 4097; j++) memo[i][j] = INF;
        cost[0][0] = 0;

        for (int i = 0; i < M; i++) {
            int a, b;
            int dollars, cents;
            char dot;
            cin >> a >> b >> dollars >> dot >> cents;
            cost[a][b] = min(cost[a][b], dollars*100 + cents);
            cost[b][a] = min(cost[b][a], dollars*100 + cents);
        }

        for (int k = 0; k <= N; k++) for (int i = 0; i <= N; i++) for (int j = 0; j <= N; j++)
                    cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]);

        cin >> P;
        set<int> stores;
        for (int i = 0; i < P; i++) {
            int store;
            int dollars, cents;
            char dot;
            cin >> store >> dollars >> dot >> cents;
            if (stores.find(store) == stores.end()) {
                operaToStore[i] = store;
                stores.insert(store);
            }
            save[store] += dollars*100 + cents;
        }

        int ans = tsp(0, 0);
        if (ans <= 0) cout << "Don't leave the house" << endl;
        else printf("Daniel can save $%0.2f\n", double(ans)/100.0);
    }
    return 0;
}
