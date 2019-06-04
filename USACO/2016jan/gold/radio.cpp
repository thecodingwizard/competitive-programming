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

int n, m;
int fx, fy, bx, by;
string fj, bes;
int dp[1001][1001];
ii fjPos[1001], besPos[1001];

int cost(int i, int j) {
    return (fjPos[i].A-besPos[j].A)*(fjPos[i].A-besPos[j].A)+(fjPos[i].B-besPos[j].B)*(fjPos[i].B-besPos[j].B);
}

int main() {
    freopen("radio.in", "r", stdin);
    freopen("radio.out", "w", stdout);

    cin >> n >> m;
    cin >> fx >> fy >> bx >> by;
    cin >> fj >> bes;

    fjPos[0] = mp(fx, fy);
    besPos[0] = mp(bx, by);

    int dx[100], dy[100];
    dx['N'] = 0;
    dy['N'] = 1;
    dx['E'] = 1;
    dy['E'] = 0;
    dx['S'] = 0;
    dy['S'] = -1;
    dx['W'] = -1;
    dy['W'] = 0;
    FOR(i, 1, n+1) {
        fjPos[i] = mp(fjPos[i - 1].A + dx[fj[i-1]], fjPos[i - 1].B + dy[fj[i-1]]);
    }
    FOR(i, 1, m+1) {
        besPos[i] = mp(besPos[i - 1].A + dx[bes[i-1]], besPos[i - 1].B + dy[bes[i-1]]);
    }

    F0R(i, 1000) F0R(j, 1000) dp[i][j] = INF;
    dp[0][0] = 0;

    F0R(i, n+1) {
        F0R(j, m+1) {
            if (i == 0 && j == 0) continue;
            dp[i][j] = min(i - 1 >= 0 ? dp[i - 1][j] : INF, min(j - 1 >= 0 ? dp[i][j - 1] : INF, i - 1 >= 0 && j - 1 >= 0 ? dp[i - 1][j - 1] : INF)) + cost(i, j);
        }
    }

    cout << dp[n][m] << endl;

    return 0;
}
