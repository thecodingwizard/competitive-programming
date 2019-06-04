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

#define INF 1100000000
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

map<string, int> memo;
int dp(string s) {
    if (memo.count(s)) return memo[s];
    int ans = 1;
    int l = s.length();
    for (int i = 1; i * 2 < l; i++) {
        if (s.substr(0, i) == s.substr(l - i, i)) {
            ans += dp(s.substr(i, l - i));
        }
        if (s.substr(0, i) == s.substr(i, i)) {
            ans += dp(s.substr(i, l - i));
        }
        if (s.substr(0, i) == s.substr(l - i, i)) {
            ans += dp(s.substr(0, l - i));
        }
        if (s.substr(l - i * 2, i) == s.substr(l - i, i)) {
            ans += dp(s.substr(0, l - i));
        }
    }
    return memo[s] = ans%2014;
}

int main() {
    freopen("scode.in", "r", stdin);
    freopen("scode.out", "w", stdout);

    string s; cin >> s;
    cout << (dp(s)-1+2014)%2014 << endl;

    return 0;
}
