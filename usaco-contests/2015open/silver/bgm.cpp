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

int ways[7][12];

ll calc(int num) {
    int m = num % (int) pow(8, 1);
    num -= m;
    int o = num % (int) pow(8, 2);
    num -= o;
    int g = num % (int) pow(8, 3);
    num -= g;
    int i = num % (int) pow(8, 4);
    num -= i;
    int s = num % (int) pow(8, 5);
    num -= s;
    int e = num % (int) pow(8, 6);
    num -= e;
    int b = num % (int) pow(8, 7);
    m /= pow(8, 0);
    o /= pow(8, 1);
    g /= pow(8, 2);
    i /= pow(8, 3);
    s /= pow(8, 4);
    e /= pow(8, 5);
    b /= pow(8, 6);
    if ((b+e+s+s+i+e)%7==0 || (g+o+e+s)%7 == 0 || (m+o+o)%7==0) {
        return (ll)ways[0][b]*ways[1][e]*ways[2][s]*ways[3][i]*ways[4][g]*ways[5][o]*ways[6][m];
    }
    return 0;
}

int main() {
    freopen("bgm.in", "r", stdin);
    freopen("bgm.out", "w", stdout);

    int n; cin >> n;
    memset(ways, 0, sizeof ways);
    int map[1000];
    map['B'] = 0;
    map['E'] = 1;
    map['S'] = 2;
    map['I'] = 3;
    map['G'] = 4;
    map['O'] = 5;
    map['M'] = 6;
    F0R(i, n) {
        char c; int x; cin >> c >> x;
        ways[map[c]][(x%7+7)%7]++;
    }

    long long ans = 0;
    F0R(i, pow(8, 7)) {
        ans += calc(i);
    }
    cout << ans << endl;

    return 0;
}
