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
    freopen("spainting.in", "r", stdin);
    freopen("spainting.out", "w", stdout);

    ll n, m, k; cin >> n >> m >> k;
    ll dp[n+10];
    int mod = (int)1e+9+7;
    dp[0] = 0;

    FOR(i, 1, n+1) {
        if (i < k) dp[i] = (dp[i-1]*m+m)%mod;
        else dp[i] = (m*(dp[i-1])+mod-((m-1)*(dp[i-k])%mod))%mod;
    }

    ll ans = 1;
    F0R(i, n) ans = (m*ans)%mod;

    cout << (ans+mod-(dp[n]-dp[n-1]))%mod << endl;

    return 0;
}
