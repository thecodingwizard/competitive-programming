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
    freopen("censor.in", "r", stdin);
    freopen("censor.out", "w", stdout);

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
