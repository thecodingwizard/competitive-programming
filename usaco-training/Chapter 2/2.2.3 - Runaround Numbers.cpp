/*
ID: nathan.18
TASK: runround
LANG: C++
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

#define INF 1000000000
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define PI acos(-1.0)
#define ll long long
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

set<int> seen;
int digits[10];

bool isRunaround(int m) {
    seen.clear();
    int digitCt = 0;
    while (m > 0) {
        if (m%10 == 0 || seen.count(m%10)>0) return false;
        digits[digitCt++] = m%10;
        seen.insert(m%10);
        m /= 10;
    }
    seen.clear();
    reverse(digits, digits+digitCt);
    int curIdx = 0;
    while (seen.find(digits[curIdx]) == seen.end()) {
        seen.insert(digits[curIdx]);
        curIdx += digits[curIdx];
        curIdx %= digitCt;
    }
    return seen.size() == digitCt && curIdx == 0;
}

int main() {
    freopen("runround.in", "r", stdin);
    freopen("runround.out", "w", stdout);

    int m; cin >> m;
    while (!isRunaround(++m));

    cout << m << endl;

    return 0;
}
