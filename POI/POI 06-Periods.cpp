/*
 * Same solution as editorial:
 *
 * - For a given string A, if X is a prefix of A and X is also a suffix of A, then we can form a period Q where Q consists of A
 *   except we exclude the suffix X. (The length of X must be less than or equal to half the length of A.)
 * - So for babababa, since "ba" is both a prefix and a suffix, we chop off the "ba" suffix and "bababa" is a valid period.
 * - To maximize the length of the period, we need to minimize the length of the prefix-suffix X.
 * - Therefore, we just need a way to find, for every prefix of the given string, we need to find the minimum length of a prefix-suffix.
 *   (If no such prefix-suffix exists, then there is no period for that prefix.)
 * - We can do this with a variation of the KMP string matching algorithm.
 * - In particular, we need to generate the prefix function array: https://cp-algorithms.com/string/prefix-function.html
 * - The prefix function pi[i] = longest prefix of given_string[0...i] which is also a suffix of this substring.
 *   - We can compute this in O(1) time; see the cp-algorithms link.
 * - Next, to get the smallest possible prefix-suffix, notice that if X is a prefix-suffix, then a prefix-suffix
 *   of X is also a valid prefix-suffix of the entire substring.
 * - So, after finding pi[i], we then check pi[pi[i]], then pi[pi[pi[i]]], and so on (note that you may need to
 *   subtract one depending on your array indexing).
 *   - We stop right before the next pi[i] is 0, since a pi[i] of 0 means that no prefix-suffix exists.
 * - See impl below for more details
 */

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int n;
string s;
int pi[1000000];

int main() {
    cin >> n >> s;

    pi[0] = 0;
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j]) {
            j = pi[j-1];
        }
        if (s[i] == s[j]) {
            j++;
        } else {
            assert(j == 0);
        }
        pi[i] = j;
    }

    ll ans = 0;
    for (int i = 1; i < n; i++) {
        if (pi[i] == 0) continue;
        if (pi[pi[i]-1] != 0) pi[i] = pi[pi[i]-1];
        ans += (i + 1 - pi[i]);
    }
    cout << ans << endl;

    return 0;
}
