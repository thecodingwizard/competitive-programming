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

struct MaxQueue {
    //         value, index
    deque<pair<int,   int  >> dq;
    int L = 0, R = -1;

    void insert(int x) {
        while (!dq.empty() && dq.back().A <= x) {
            dq.pop_back();
        }
        dq.emplace_back(x, ++R);
    }

    int size() { return R - L + 1; }

    void del() {
        if (dq.front().B == L++) dq.pop_front();
    }

    int query() { return dq.front().A; }
};

int main() {
    freopen("crowded.in", "r", stdin);
    freopen("crowded.out", "w", stdout);

    int n, d; cin >> n >> d;
    vector<pair<int, ii>> leftCows;
    vector<pair<int, ii>> rightCows;
    F0R(i, n) {
        int a, b; cin >> a >> b;
        leftCows.push_back(mp(a, mp(b, i)));
        leftCows.push_back(mp(a+d, mp(-1, -1)));
        rightCows.push_back(mp(a-d, mp(-1, -1)));
        rightCows.push_back(mp(a, mp(b, i)));
    }
    sort(leftCows.begin(), leftCows.end());
    sort(rightCows.begin(), rightCows.end());
    reverse(rightCows.begin(), rightCows.end());

    bool leftCrowded[n]; memset(leftCrowded, false, sizeof leftCrowded);
    MaxQueue left;
    for (pair<int, ii> cow : leftCows) {
        if (cow.B.A == -1) left.del();
        else {
            if (left.size() > 0 && left.query() >= 2*cow.B.A) {
                leftCrowded[cow.B.B] = true;
            }
            left.insert(cow.B.A);
        }
    }

    int ans = 0;
    MaxQueue right;
    for (pair<int, ii> cow : rightCows) {
        if (cow.B.A == -1) right.del();
        else {
            if (right.size() > 0 && right.query() >= 2*cow.B.A && leftCrowded[cow.B.B]) {
                ans++;
            }
            right.insert(cow.B.A);
        }
    }

    cout << ans << endl;

    return 0;
}
