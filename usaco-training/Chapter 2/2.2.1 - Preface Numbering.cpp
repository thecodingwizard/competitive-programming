/*
ID: nathan.18
TASK: preface
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

map<char, int> counter;

void run(int num) {
    if (num >= 1000) {
        counter['M'] += num/1000;
        run(num%1000);
    } else if (num >= 500) {
        if (num < 900) {
            counter['D'] += num/500;
            run(num%500);
        } else {
            counter['C']++;
            counter['M']++;
            run(num%100);
        }
    } else if (num >= 100) {
        if (num < 400) {
            counter['C'] += num/100;
            run(num%100);
        } else {
            counter['C']++; counter['D']++;
            run(num%100);
        }
    } else if (num >= 50) {
        if (num < 90) {
            counter['L'] += num/50;
            run(num%50);
        } else {
            counter['X']++; counter['C']++;
            run(num%10);
        }
    } else if (num >= 10) {
        if (num < 40) {
            counter['X'] += num/10;
            run(num%10);
        } else {
            counter['X']++; counter['L']++;
            run(num%10);
        }
    } else if (num >= 5) {
        if (num < 9) {
            counter['V'] += num/5;
            run(num%5);
        } else {
            counter['I']++; counter['X']++;
        }
    } else if (num >= 1) {
        if (num < 4) {
            counter['I'] += num;
        } else {
            counter['I']++; counter['V']++;
        }
    }
}

int main() {
    freopen("preface.in", "r", stdin);
    freopen("preface.out", "w", stdout);

    int n; cin >> n;
    char chars[7] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
    for (char c : chars) counter.insert(mp(c, 0));

    for (int i = 1; i <= n; i++) {
        run(i);
    }

    for (char c : chars) if (counter[c] != 0) cout << c << " " << counter[c] << endl;

    return 0;
}
