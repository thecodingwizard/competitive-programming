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
#include <cassert>

using namespace std;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define INF 1000000000
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define pb push_back
#define PI acos(-1.0)
#define ll long long
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int main() {
    freopen("invite.in", "r", stdin);
    freopen("invite.out", "w", stdout);

    int n, g; cin >> n >> g;
    vi cowGroups[n+10];
    set<int> groups[g+10];
    F0R(i, g) {
        int x; cin >> x;
        F0R(j, x) {
            int cow; cin >> cow;
            cowGroups[cow].push_back(i);
            groups[i].insert(cow);
        }
    }
    queue<int> toProcess; toProcess.push(1);
    bool processed[n+10]; memset(processed, false, sizeof processed);
    int ans = 0;
    while (!toProcess.empty()) {
        int next = toProcess.front(); toProcess.pop();
        if (processed[next]) continue;
        processed[next] = true;
        ans++;
        for (int group : cowGroups[next]) {
            groups[group].erase(next);
            if (groups[group].size() == 1) toProcess.push(*groups[group].begin());
        }
    }
    cout << ans << endl;

    return 0;
}
