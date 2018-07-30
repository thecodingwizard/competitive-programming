/*
ID: nathan.18
TASK: fracdec
LANG: C++11
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

vi ans;
int repeatingIndex = INF;
map<ii, int> seen;
int idx = 0;

void divide(int num, int divisor) {
    if (num == 0) return;
    if (seen.find(mp(num, divisor)) != seen.end()) {
        repeatingIndex = seen[mp(num, divisor)];
        return;
    }
    seen[mp(num, divisor)] = idx++;
    ans.push_back(num/divisor);
    divide((num%divisor)*10, divisor);
}

int numDigits(int num) {
    return to_string(num).length();
}

int main() {
    freopen("fracdec.in", "r", stdin);
    freopen("fracdec.out", "w", stdout);

    int n, d; cin >> n >> d;
    divide(n, d);

    int charCount = 0;
    F0R(i, ans.size()) {
        if (repeatingIndex == i) {
            cout << "(";
            charCount++;
        }
        if (charCount >= 76) {
            cout << endl;
            charCount = 0;
        }
        cout << ans[i];
        charCount += numDigits(ans[i]);
        if (charCount >= 76) {
            cout << endl;
            charCount = 0;
        }
        if (i == 0) {
            cout << ".";
            charCount++;
        }
        if (charCount >= 76) {
            cout << endl;
            charCount = 0;
        }
    }
    if (ans.size() == 1) {
        cout << "0";
        charCount++;
    }
    if (charCount >= 76) {
        cout << endl;
        charCount = 0;
    }
    if (repeatingIndex != INF) {
        cout << ")";
        charCount++;
    }
    cout << endl;

    return 0;
}
