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
    freopen("cowjog.in", "r", stdin);
    freopen("cowjog.out", "w", stdout);

    int n, t; cin >> n >> t;
    vector<ll> lanes;
    for (int i = 0; i < n; i++) {
        ll start, speed; cin >> start >> speed;
        ll end = -(start + speed*t);
        if (lanes.size() == 0 || lanes.back() <= end) {
            lanes.push_back(end);
        } else {
            *upper_bound(lanes.begin(), lanes.end(), end) = end;
        }
    }

    cout << lanes.size() << endl;

    return 0;
}
