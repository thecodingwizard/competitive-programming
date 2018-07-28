/*
ID: nathan.18
TASK: concom
LANG: C++
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

int n, sharesOwned[101][101], curCompany[101];
bool visited[101];

void process(int company) {
    if (visited[company]) return;
    visited[company] = true;
    FOR(i, 1, 101) curCompany[i] += sharesOwned[company][i];
    FOR(i, 1, 101) if (i != company && curCompany[i] > 50) process(i);
}

int main() {
    freopen("concom.in", "r", stdin);
    freopen("concom.out", "w", stdout);

    cin >> n;
    F0R(i, n) {
        int a, b, c; cin >> a >> b >> c; sharesOwned[a][b] = c;
    }

    FOR(i, 1, 101) {
        memset(curCompany, 0, sizeof curCompany);
        memset(visited, false, sizeof visited);

        process(i);

        FOR(j, 1, 101) {
            if (i != j && curCompany[j] > 50) {
                cout << i << " " << j << endl;
            }
        }
    }

    return 0;
}
