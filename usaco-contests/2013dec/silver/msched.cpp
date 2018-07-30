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
    freopen("msched.in", "r", stdin);
    freopen("msched.out", "w", stdout);

    int n; cin >> n;
    ii cows[n]; F0R(i, n) cin >> cows[i].B >> cows[i].A;
    sort(cows, cows+n);

    priority_queue<int, vi, greater<int>> pq;
    F0R(i, n) {
        pq.push(cows[i].B);
        if (pq.size() > cows[i].A) {
            pq.pop();
        }
    }

    int ans = 0;
    while (!pq.empty()) {
        ans += pq.top(); pq.pop();
    }
    cout << ans << endl;

    return 0;
}
