/*
ID: nathan.18
TASK: humble
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
#include <unordered_set>

using namespace std;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define INF 1100000000
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

int main() {
    freopen("humble.in", "r", stdin);
    freopen("humble.out", "w", stdout);

    int k, n; cin >> k >> n;
    int nums[k];
    set<int> curNums;
    F0R(i, k) {
        cin >> nums[i];
        curNums.insert(nums[i]);
    }

    F0R(i, k) {
        auto it = curNums.begin();
        while (it != curNums.end()) {
            int nextNum = nums[i]*(*it);
            if (nextNum < 0) break; // overflow, too big so we don't need to consider it
            curNums.insert(nextNum);
            if (curNums.size() > n) {
                curNums.erase(--curNums.end());
                if (*--curNums.end() < nextNum) {
                    break;
                }
            }
            it++;
        }
    }

    cout << *--curNums.end() << endl;

    return 0;
}
