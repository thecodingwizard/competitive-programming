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

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define SORT(vec) sort(vec.begin(), vec.end())

#define INF 1000000010
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define pb push_back
#define PI acos(-1.0)
#define ll long long
#define MOD (int)(2e+9+11)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int main() {
    freopen("cownomics.in", "r", stdin);
    freopen("cownomics.out", "w", stdout);

    int n, m; cin >> n >> m;
    int cows[2*n][m];
    int value[1000];
    value['A'] = 1;
    value['C'] = 2;
    value['G'] = 4;
    value['T'] = 8;
    int hash[m]; F0R(i, m) hash[i] = rand() % MOD;
    F0R(i, 2*n) {
        int sum = 0;
        F0R(j, m) {
            char c; cin >> c;
            sum += value[c]*(hash[j]);
            cows[i][j] = sum;
        }
    }

    set<int> seen;
    int best = INF;
    int i = 0, j = 0;
    while (j < m) {
        seen.clear();
        bool flag = false;
        F0R(k, n) {
            int val = cows[k][j] - cows[k][i];
            seen.insert(val);
        }
        F0R(k, n) {
            int val = cows[n+k][j] - cows[n+k][i];
            if (seen.count(val)) {
                flag = true;
                j++;
                break;
            }
        }
        if (flag) continue;
        best = min(best, j-i);
        i++;
    }
    cout << best << endl;

    return 0;
}
