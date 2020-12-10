/*
 * Slope Trick
 *
 * - https://usaco.guide/adv/slope
 * - https://codeforces.com/blog/entry/47094?#comment-315161
 */

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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    ll ans = 0;
    priority_queue<int> pq;
    F0R(i, n) {
        int x; cin >> x; x -= i;
        pq.push(x);

        if (pq.top() > x) {
            ans += pq.top()-x;
            pq.pop();
            pq.push(x);
        }
    }
    cout << ans << endl;

    return 0;
}

/*

// O(n^2) dp

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

ll dp[3000][3000];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    int A[n], B[n];
    F0R(i, n) {
        cin >> A[i]; A[i]-=i;
        B[i] = A[i];
    }
    sort(B, B+n);
    
    F0R(i, n) {
        F0R(j, n) {
            dp[i][j] = min((i==0?0:dp[i-1][j])+abs(A[i]-B[j]), j==0?numeric_limits<ll>::max():dp[i][j-1]);
        }
    }

    cout << dp[n-1][n-1] << endl;

    return 0;
}

*/
