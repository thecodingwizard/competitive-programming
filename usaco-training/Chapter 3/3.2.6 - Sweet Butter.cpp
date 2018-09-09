/*
ID: nathan.18
TASK: butter
LANG: C++11
*/

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
#define pA first
#define pB second
#define mp make_pair
#define pb push_back
#define PI acos(-1.0)
#define ll long long
#define MOD (int)(2e+9+11)
#define SET(vec, val, size) for (int i = 0; i < size; i++) vec[i] = val;
#define SET2D(arr, val, dim1, dim2) F0R(i, dim1) F0R(j, dim2) arr[i][j] = val;
typedef pair<int, int> ii;
typedef pair<ii, int> iii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vl;

int dist[800][800];
int main() {
    freopen("butter.in", "r", stdin);
    freopen("butter.out", "w", stdout);

    int n, p, c; cin >> n >> p >> c;
    int A[1500]; SET(A, 0, 1500);
    F0R(i, n) {
        int x; cin >> x;
        A[--x]++;
    }
    SET2D(dist, INF, 800, 800);
    vii adjList[800];
    F0R(i, c) {
        int a, b, w; cin >> a >> b >> w;
        --a; --b;
        adjList[a].push_back(mp(b, w));
        adjList[b].push_back(mp(a, w));
    }

    F0R(i, p) {
        priority_queue<ii, vii, greater<ii>> pq;
        pq.push(mp(0, i));
        dist[i][i] = 0;
        while (!pq.empty()) {
            ii next = pq.top(); pq.pop();
            if (next.pA > dist[i][next.pB]) continue;
            for (ii child : adjList[next.pB]) {
                if (dist[i][child.pA] > dist[i][next.pB] + child.pB) {
                    dist[i][child.pA] = dist[i][next.pB] + child.pB;
                    pq.push(mp(dist[i][child.pA], child.pA));
                }
            }
        }
    }

    int best = INF;
    F0R(i, p) {
        int sum = 0;
        F0R(j, p) {
            sum += dist[j][i]*A[j];
        }
        best = min(best, sum);
    }
    cout << best << endl;

    return 0;
}
