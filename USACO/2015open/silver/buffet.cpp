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
#include <unordered_set>

using namespace std;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define SORT(vec) sort(vec.begin(), vec.end())

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
    freopen("buffet.in", "r", stdin);
    freopen("buffet.out", "w", stdout);

    int n, e; cin >> n >> e;
    ll dp[1000];
    vi adjList[1000];
    int quality[1000];
    vii patches;
    int mapping[1000];
    int reverseMapping[1000];
    F0R(i, n) {
        int q, d; cin >> q >> d;
        quality[i] = q;
        patches.push_back(mp(q, i));
        F0R(j, d) {
            int x; cin >> x;
            adjList[i].push_back(--x);
        }
    }
    SORT(patches);

    F0R(i, n) {
        mapping[i] = patches[i].B;
        reverseMapping[patches[i].B] = i;
    }

    ll dist[1000];
    F0R(i, n) dp[i] = 0;
    F0Rd(i, n) {
        dp[i] = quality[mapping[i]];
        F0R(j, 1000) dist[j] = LL_INF;
        queue<ii> q; q.push(mp(i, 0));
        while (!q.empty()) {
            ii next = q.front(); q.pop();
            if (dist[next.A] != LL_INF) continue;
            dist[next.A] = (ll)next.B*e;
            for (int child : adjList[mapping[next.A]]) {
                q.push(mp(reverseMapping[child], next.B+1));
            }
        }

        F0R(j, n) {
            if (quality[mapping[j]] <= quality[mapping[i]]) continue;
            dp[i] = max(dp[i], quality[mapping[i]] + dp[j] - dist[j]);
        }
    }

    ll best = 0;
    F0R(i, n) best = max(best, dp[i]);

    cout << best << endl;

    return 0;
}
