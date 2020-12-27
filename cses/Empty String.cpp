#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define ii pair<int, int>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define inf 1000000010

const int mod = 1e9+7;

string s;
int ncr[500][500];

int memo[500][500];
// dp(i, j) = number of ways to empty the substring s[i...j]
ll dp(int i, int j) {
    // if i > j this means that our string is empty; there is one way
    if (i > j) return 1;
    if (memo[i][j] != -1) return memo[i][j];

    ll ans = 0;

    // otherwise, our goal is to match character s[i]
    // with the character that it's going to be paired with
    for (int x = i+1; x <= j; x += 2) {
        // let's try matching s[i] with s[x]
        if (s[i] == s[x]) {
            // we'll split the range [i...j] into [i...x] and [x+1...j]
            // left = # of operations needed to empty [i...x]
            // right = # of operations needed to empty [x+1...j]
            int left = (x-i+1)/2, right = (j-x)/2;

            // In total, we need left+right operations to empty [i...j]
            // some of these operations are for the left range
            // some of these operations are for the right range
            // there are (left+right) choose (left) ways to order
            // the left/right operations
            ll waysToArrangeOperations = ncr[left+right][left];

            // There are dp(i+1, x-1) different ordered ways we can
            // process the left range
            // There are dp(x+1, j) different ordered ways we can
            // process the right range
            // Therefore, there are dp(i+1, x-1)*dp(x+1, j) different
            // ordered ways we can process the entire range
            // assuming we process the left range and then the right range
            ll numUniqueWays = dp(i+1, x-1)*dp(x+1, j) % mod;

            // Of course, we can intermix the left operations and the right
            // operations; we don't have to process the left range completely
            // before processing the right range.
            // So, there are numUniqueWays*waysToArrangeOperations total ways
            // to process the entire range
            ans = (ans + numUniqueWays*waysToArrangeOperations) % mod;
        }
    }

    return memo[i][j] = ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> s;
    int n = s.length();

    ncr[0][0] = 1;
    F0R(i, n) {
        ncr[i][0] = 1;
        FOR(j, 1, i+1) {
            ncr[i][j] = (ncr[i-1][j-1]+ncr[i-1][j])%mod;
        }
    }

    F0R(i, n) F0R(j, n) memo[i][j] = -1;
    cout << dp(0, n-1) << endl;

    return 0;
}
