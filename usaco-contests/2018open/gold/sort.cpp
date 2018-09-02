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
#define SET(vec, val, size) for (int i = 0; i < size; i++) vec[i] = val;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int n;
int tree[100001];
ii nums[100001];

void adjust(int b) {
    for (; b < n+1; b += LSOne(b)) tree[b]++;
}
int query(int b) {
    int sum = 0;
    for (; b; b -= LSOne(b)) sum += tree[b];
    return sum;
}

int main() {
    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);

    cin >> n;
    F0R(i, n) {
        cin >> nums[i].A;
        nums[i].B = i+1;
    }
    sort(nums, nums+n);

    int ans = 1;
    FOR(i, 1, n+1) {
        adjust(nums[i-1].B);
        ans = max(ans, i - query(i));
    }

    cout << ans << endl;

    return 0;
}
