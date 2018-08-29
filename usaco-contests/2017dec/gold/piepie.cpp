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

#define INF 1000000010
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define pb push_back
#define PI acos(-1.0)
#define ll long long
#define MOD (int)(2e+9+11)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int main() {
    freopen("piepie.in", "r", stdin);
    freopen("piepie.out", "w", stdout);

    int n, d; cin >> n >> d;
    int X[2*n], Y[2*n]; F0R(i, 2*n) cin >> X[i] >> Y[i];
    int dist[2*n];
    queue<int> q;
    set<ii> bes, elsie;
    F0R(i, 2*n) {
        if (i >= n) {
            if (X[i] == 0) {
                dist[i] = 1;
                q.push(i);
            } else {
                dist[i] = INF;
                elsie.insert(mp(X[i], i));
            }
        } else {
            if (Y[i] == 0) {
                dist[i] = 1;
                q.push(i);
            } else {
                dist[i] = INF;
                bes.insert(mp(Y[i], i));
            }
        }
    }
    while (!q.empty()) {
        int next = q.front(); q.pop();
        if (next >= n) {
            auto it = bes.lower_bound(mp(Y[next]-d, -1));
            while (it != bes.end() && Y[it->B] <= Y[next]) {
                dist[it->B] = dist[next]+1;
                q.push(it->B);
                it = bes.erase(it);
            }
        } else {
            auto it = elsie.lower_bound(mp(X[next]-d, -1));
            while (it != elsie.end() && X[it->B] <= X[next]) {
                dist[it->B] = dist[next]+1;
                q.push(it->B);
                it = elsie.erase(it);
            }
        }
    }
    F0R(i, n) {
        if (dist[i] == INF) cout << "-1" << endl;
        else cout << dist[i] << endl;
    }

    return 0;
}
