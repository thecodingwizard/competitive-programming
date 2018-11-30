/*
Censoring
=========

Farmer John has purchased a subscription to Good Hooveskeeping
magazine for his cows, so they have plenty of material to read
while waiting around in the barn during milking sessions.
Unfortunately, the latest issue contains a rather inappropriate
article on how to cook the perfect steak, which FJ would rather his
cows not see (clearly, the magazine is in need of better editorial
oversight).

FJ has taken all of the text from the magazine to create the string
S of length at most 10^6 characters. From this, he would like to
remove occurrences of a substring T to censor the inappropriate
content. To do this, Farmer John finds the _first_ occurrence of T
in S and deletes it. He then repeats the process again, deleting
the first occurrence of T again, continuing until there are no more
occurrences of T in S. Note that the deletion of one occurrence
might create a new occurrence of T that didn't exist before.

Please help FJ determine the final contents of S after censoring is
complete.

PROBLEM NAME: censor

INPUT FORMAT:

The first line will contain S. The second line will contain T. The
length of T will be at most that of S, and all characters of S and
T will be lower-case alphabet characters (in the range a..z).

OUTPUT FORMAT:

The string S after all deletions are complete. It is guaranteed
that S will not become empty during the deletion process.

SAMPLE INPUT:

whatthemomooofun
moo

SAMPLE OUTPUT:

whatthefun
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
#include <math.h>
#include <assert.h>

using namespace std;

#define INF 1000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define ii pair<int, int>
typedef vector<int> vi;
typedef vector<ii> vii;

long long pwr[16];

int main() {
    string s, t; cin >> s >> t;
    int n = s.length();
    int tLen = t.length();
    int base = 23, mod = 2e+9+11;
    int censored = 0;
    for (char c : t) {
        censored = ((long long)censored * base + c) % mod;
    }
    int h;
    h = 0;
    int i = 1;
    long long pwr = 1;
    for (int x = 0; x < tLen; x++) pwr = (long long) pwr * base % mod;
    string myString;
    for (int c = 1; c <= n; c++) {
        myString.push_back(s[c - 1]);
        h = ((long long) h * base + myString[i - 1]) % mod;
        if (i - tLen - 1 >= 0){
            h -= (myString[i - tLen - 1] * pwr) % mod;
            if (h < 0) h += mod;
        }
        assert(h >= 0);
        if (h == censored) {
            i -= tLen;
            h = 0;
            for (int k = i - tLen + 1; k <= i; k++) {
                if (k < 1) continue;
                h = ((long long) h * base + myString[k - 1]) % mod;
            }

            for (int k = i; k > i - tLen; k--) {
                myString.pop_back();
            }
        }
        i++;
    }
    cout << myString << endl;
    return 0;
}
