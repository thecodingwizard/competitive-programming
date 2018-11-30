/*
Hidden Password
===============

Sometimes the programmers have very strange ways of hiding their
passwords. Billy "Hacker" Geits chooses a string S composed of L (5
<= L <= 100,000) lowercase letters ('a'..'z') with length L. Then
he makes and sorts all L-1 one-letter left cyclic shifts of the
string. He then takes as a password one prefix of the
lexicographically first of the obtained strings (including S).

For example consider the string "alabala". The sorted cyclic
one-letter left shifts (including the initial string) are:

aalabal
abalaal
alaalab
alabala
balaala
laalaba
labalaa

Lexicographically, first string is 'aalabal'. The first letter of
this string ('a') is the 'a' that was in position 6 in the initial
string (counting the first letter in the string as position 0).

Write a program that, for given string S, finds the start position
of the first letter of the sorted list of cyclic shifts of the
string. If the first element appears more than once in the sorted
list, then the program should output the smallest possible initial
position.

PROGRAM NAME: hidden

INPUT FORMAT:

* Line 1: A single integer: L

* Line 2..?: All L characters of the the string S, broken across
lines such that each line has 72 characters except the last one,
which might have fewer.

SAMPLE INPUT:

7
alabala

OUTPUT FORMAT:

* Line 1: A single integer that is the start position of the first
letter, as described above.

SAMPLE OUTPUT:

6
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
#define PI acos(-1.0)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int main() {
    int l;
    cin >> l;
    char s[200001];
    for (int i = 0; i < l; i++) {
        cin >> s[i];
        s[i + l] = s[i];
    }

    int i = 0, j = 1, k;
    while (j <= l) {
        for (k = 0; k < l; k++) if (s[i + k] != s[j + k]) break;
        if (s[i + k] == s[j + k]) break;
        if (s[i + k] < s[j + k]) j += k + 1;
        else i += k + 1;
        if (i == j) j++;
    }
    cout << i << endl;
    return 0;
}
