/*
ID: nathan.18
TASK: maze1
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

int w, h;
set<pair<ii, ii>> blocked;

int distances[101][39];
int combinedDistances[101][39];

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

int main() {
    freopen("maze1.in", "r", stdin);
    freopen("maze1.out", "w", stdout);

    cin >> w >> h;
    cin.ignore();
    vii exits;
    F0R(i, 2*h+1) {
        string line; getline(cin, line);
        F0R(j, 2*w+1) {
            char c = line[j];
            if (i%2 == 0) {
                if (c == '-' && i > 0) {
                    blocked.insert(mp(mp(i/2, (j-1)/2), mp(i/2-1, (j-1)/2)));
                    blocked.insert(mp(mp(i/2-1, (j-1)/2), mp(i/2, (j-1)/2)));
                }
                if (c == ' ' && i == h*2) {
                    exits.push_back(mp(i/2-1, (j-1)/2));
                }
                if (c == ' ' && i == 0) {
                    exits.push_back(mp(0, (j-1)/2));
                }
            } else {
                if (c == '|' && j > 0) {
                    blocked.insert(mp(mp((i-1)/2, j/2), mp((i-1)/2, j/2-1)));
                    blocked.insert(mp(mp((i-1)/2, j/2-1), mp((i-1)/2, j/2)));
                }
                if (c == ' ' && j == w*2)  {
                    exits.push_back(mp((i-1)/2, j/2-1));
                }
                if (c == ' ' && j == 0)  {
                    exits.push_back(mp((i-1)/2, 0));
                }
            }
        }
    }

    memset(distances, 0, sizeof distances);
    memset(combinedDistances, 0, sizeof combinedDistances);

    queue<pair<int, ii>> q; q.push(mp(0, exits[0]));
    while (!q.empty()) {
        pair<int, ii> next = q.front(); q.pop();
        int x = next.B.A, y = next.B.B, dist = next.A;
        if (distances[x][y] != 0) continue;
        distances[x][y] = dist;
        F0R(i, 4) {
            int a = x + dx[i], b = y + dy[i];
            if (a < 0 || a >= h || b < 0 || b >= w || blocked.find(mp(mp(x, y), mp(a, b))) != blocked.end()) continue;
            q.push(mp(dist+1, mp(a, b)));
        }
    }

    F0R(i, h) F0R(j, w) {
            combinedDistances[i][j] = distances[i][j];
        }

    memset(distances, 0, sizeof distances);
    q.push(mp(0, exits[1]));
    while (!q.empty()) {
        pair<int, ii> next = q.front(); q.pop();
        int x = next.B.A, y = next.B.B, dist = next.A;
        if (distances[x][y] != 0) continue;
        distances[x][y] = dist;
        F0R(i, 4) {
            int a = x + dx[i], b = y + dy[i];
            if (a < 0 || a >= h || b < 0 || b >= w || blocked.find(mp(mp(x, y), mp(a, b))) != blocked.end()) continue;
            q.push(mp(dist+1, mp(a, b)));
        }
    }

    int ans = 0;
    F0R(i, h) F0R(j, w) {
            ans = max(ans, min(combinedDistances[i][j], distances[i][j]) + 1);
        }
    cout << ans << endl;

    return 0;
}
