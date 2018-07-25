/*
ID: nathan.18
TASK: hamming
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

int main() {
    freopen("hamming.in", "r", stdin);
    freopen("hamming.out", "w", stdout);

    int n, b, d; cin >> n >> b >> d;

    vi numbers;
    for (int i = 0; i < (1 << b); i++) {
        bool good = true;
        for (int j : numbers) {
            int diff = 0;
            for (int k = 0; k < b; k++) {
                if ((i & (1 << k)) != (j & (1 << k))) diff++;
            }
            if (diff < d) good = false;
        }
        if (good) numbers.push_back(i);
        if (numbers.size() == n) break;
    }

    int ctr = 0;
    for (int i : numbers) {
        ctr++;
        if (ctr != 1) cout << " ";
        cout << i;
        if (ctr == 10) {
            ctr = 0;
            cout << endl;
        }
    }
    if (ctr != 0) cout << endl;
    return 0;
}
