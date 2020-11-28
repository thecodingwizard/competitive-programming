/*
 * https://github.com/dolphingarlic/CompetitiveProgramming/blob/master/COI/COI%2016-palinilap.cpp
 *
 * For each index, binary search to find the longest palindrome centered at i.
 * Then, we can extend this palindrome by changing a character on the boundary;
 * run a second binary search to see how much we can extend the palindrome if we changed
 * one of the characters on the boundary.
 *
 * Finally, for each character, calculate how much we could gain by changing that character
 * to something else.
 *
 * You can add a special character (#) between each string so you don't have to worry
 * about even length palindromes: aaaa ==> #a#a#a#a#
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
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define inf 1000000010

const ll M = 1e9+9, P = 9973;

int n;
string s[2];
ll hsh[2][210001];
ll pw[210001];
ll extra[210001][26];
ll numPalindromes[210001];
int deltaDelta[210001];

ll getHash(int a, int b, int c) {
    assert(a >= 0 && a < n && b >= 0 && b < n);
    if (c == 1) {
        int tmp = a;
        a = n-1 - b;
        b = n-1 - tmp;
    }
    return (hsh[c][b+1]-(hsh[c][a]*pw[b-a+1])%M+M)%M;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string tmp; cin >> tmp;
    s[0].resize((int)tmp.size()*2+1);
    for (int i = 0; i < (int)tmp.size(); i++) {
        s[0][i*2] = '#';
        s[0][i*2+1] = tmp[i];
    }
    s[0][(int)tmp.size()*2] = '#';
    n = s[0].length();
    s[1] = s[0];
    reverse(all(s[1]));

    hsh[0][0] = 1;
    hsh[1][0] = 1;
    pw[0] = 1;
    F0R(i, n) {
        hsh[0][i+1] = ((hsh[0][i]*P)%M+s[0][i])%M;
        hsh[1][i+1] = ((hsh[1][i]*P)%M+s[1][i])%M;
        pw[i+1] = pw[i]*P%M;
    }

    ll base = 0;
    F0R(i, n) {
        // calculate radius of palindrome
        int lo = 0, hi = min(i, n-i-1)+1, r = 0;
        while (lo < hi) {
            int mid = (lo+hi)/2;
            bool valid = getHash(i-mid, i, 0) == getHash(i, i+mid, 1);

            if (valid) {
                r = mid;
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        if (r != 0) {
            deltaDelta[i-r]++;
            deltaDelta[i+1]-=2;
            deltaDelta[i+r+2]++;
        }
        base += (r+1)/2;
        F0R(j, 26) extra[i][j] += (r+1)/2;

        int x = i-r-1, y = i+r+1;
        if (x < 0 || x >= n || y < 0 || y >= n) continue;

        // fix the boundary, calculate the new radius of palindrome
        lo = 0, hi = min(i-r-1, n-(i+r+1)-1)+1; int r2 = 0;
        while (lo < hi) {
            int mid = (lo+hi)/2;
            bool valid = getHash(i-r-1-mid, i-r-2, 0) == getHash(i+r+2, i+r+1+mid, 1);

            if (valid) {
                r2 = mid;
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        r2++;

        assert(s[0][x] != '#' && s[1][y] != '#');
        extra[x][s[0][y]-'a'] += r2/2;
        extra[y][s[0][x]-'a'] += r2/2;
    }

    ll delta = 0, tot = 0;
    F0R(i, n) {
        delta += deltaDelta[i];
        tot += delta;
        numPalindromes[i] = tot/2;
    }

    ll best = 0;
    F0R(i, n) {
        if (i%2 == 1) {
            F0R(j, 26) {
                best = max(best, extra[i][j] - numPalindromes[i]);
            }
        }
    }
    cout << base+best << endl;

    return 0;
}
