/*
ID: nathan.18
TASK: prefix
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

int main() {
    freopen("prefix.in", "r", stdin);
    freopen("prefix.out", "w", stdout);

    vector<string> prefixes;
    string s; while (cin >> s && s != ".") prefixes.push_back(s);
    s = "";
    string t; while (cin >> t) s += t;
    int dp[s.length()+10]; memset(dp, 0, sizeof dp);

    F0Rd(i, s.length()) {
        for (const auto &prefix : prefixes) {
            if (prefix.length() > s.length()-i) continue;
            for (int j = 0; j < prefix.length(); j++) if (prefix[j] != s[i+j]) goto bad;

            dp[i] = max(dp[i], dp[i + prefix.length()] + (int)prefix.length());

            bad:
            continue;
        }
    }

    cout << dp[0] << endl;

    return 0;
}
