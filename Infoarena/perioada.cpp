/*
 * See: https://github.com/MetalBall887/Competitive-Programming/blob/master/infoarena/infoarena%20perioada.cpp
 *
 * If a string of size n has a period of size k, then:
 * s[k...n] = s[1...n-k] (one indexed).
 *
 * So the prefix of size n-k must equal the suffix of size n-k.
 *
 * We can check this with string hashing.
 *
 * Then, to solve the problem, just brute force all divisors of the query length.
 */

#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define mod 1000000007

int n; 
ll H[100000];
ll pwr[100000];
ll hsh(int start, int end) {
    return (H[end] - (start == 0 ? 0 : H[start-1]) + mod) * pwr[n - start - 1] % mod;
}

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);
    freopen("perioada.in", "r", stdin);
    freopen("perioada.out", "w", stdout);

    cin >> n;
    string s; cin >> s;

    H[0] = s[0] - 'a';
    pwr[0] = 1;
    for (int i = 1; i < n; i++) {
        pwr[i] = pwr[i-1]*26%mod;
        H[i] = (H[i-1]+(s[i]-'a')*pwr[i])%mod;
    }

    vector<int> divisors[n+1];
    for (int i = 1; i <= n; i++) {
        for (int j = i+i; j <= n; j += i) {
            divisors[j].push_back(i);
        }
    }

    int m; cin >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b; --a; --b;
        int ans = 0;
        for (int d : divisors[b-a+1]) {
            if (hsh(a+d, b) == hsh(a, b-d)) ans++;
        }
        cout << ans << "\n";
    }

    return 0;
}
