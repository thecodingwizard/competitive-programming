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
#include <fstream>

using namespace std;

#define INF 1000000000
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define PI acos(-1.0)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int main() {
    freopen("fcount.in", "r", stdin);
    freopen("fcount.out", "w", stdout);

    int n;
    cin >> n;
    int nums[n+1]; for (int i = 0; i <= n; i++) cin >> nums[i];

    vi ans;
    priority_queue<int> pq;
    vi toReAdd;

    for (int excluded = 0; excluded <= n; excluded++) {
        for (int i = 0; i <= n; i++) if (i != excluded) pq.push(nums[i]);
        while (!pq.empty()) {
            int cur = pq.top(); pq.pop();
            for (int i = 0; i < cur; i++) {
                if (pq.size() == 0) goto bad;
                int next = pq.top(); pq.pop();
                if (next - 1 > 0) toReAdd.push_back(next - 1);
            }
            for (int i : toReAdd) pq.push(i);
            toReAdd.clear();
        }

        ans.push_back(excluded);

        bad:
        while (!pq.empty()) pq.pop();
        toReAdd.clear();
    }

    cout << ans.size() << endl;
    for (int i : ans) cout << i+1 << endl;

    return 0;
}
