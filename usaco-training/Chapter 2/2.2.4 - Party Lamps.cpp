/*
ID: nathan.18
TASK: lamps
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

#define LIT 1
#define UNLIT 0
#define EITHER 2
int main() {
    freopen("lamps.in", "r", stdin);
    freopen("lamps.out", "w", stdout);

    int n, c; cin >> n >> c;
    bool lit[n+1];
    int given[n+1];
    int x;
    for (int i = 0; i <= n; i++) given[i] = EITHER;
    while (cin >> x && x != -1) given[x] = LIT;
    while (cin >> x && x != -1) given[x] = UNLIT;

    vector<string> answers;
    for (int i = 0; i < (1 << 4); i++) {
        if (__builtin_popcount(i)%2 != c%2 || __builtin_popcount(i) > c) continue;
        memset(lit, true, sizeof lit);
        // 0 0 0 0 = button 1, button 2, button 3, button 4
        if (i & (1 << 0)) {
            // button 1 pressed
            for (int j = 1; j <= n; j++) lit[j] = !lit[j];
        }
        if (i & (1 << 1)) {
            // 2 pressed
            for (int j = 1; j <= n; j += 2) lit[j] = !lit[j];
        }
        if (i & (1 << 2)) {
            // 3 pressed
            for (int j = 2; j <= n; j += 2) lit[j] = !lit[j];
        }
        if (i & (1 << 3)) {
            // 4 pressed
            for (int j = 1; j <= n; j += 3) lit[j] = !lit[j];
        }
        bool good = true;
        for (int j = 1; j <= n; j++) {
            if (given[j] == EITHER) continue;
            if (given[j] != lit[j]) good = false;
        }
        if (!good) continue;

        string s;
        for (int j = 1; j <= n; j++) {
            if (lit[j]) s += '1'; else s += '0';
        }
        answers.push_back(s);
    }

    if (answers.size() == 0) cout << "IMPOSSIBLE" << endl;
    else {
        sort(answers.begin(), answers.end());
        for (string s : answers) cout << s << endl;
    }

    return 0;
}
