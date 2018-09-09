/*
ID: nathan.18
TASK: spin
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
#define SET2D(arr, val, dim1, dim2) F0R(i, dim1) F0R(j, dim2) arr[i][j] = val;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vl;

int main() {
    freopen("spin.in", "r", stdin);
    freopen("spin.out", "w", stdout);

    vii wheels[5];
    int speed[5];
    F0R(i, 5) {
        cin >> speed[i];
        int wedges; cin >> wedges;
        F0R(j, wedges) {
            int a, b; cin >> a >> b;
            wheels[i].push_back(mp(a, b));
        }
    }

    int count[370];
    F0R(i, 361) {
        memset(count, 0, sizeof count);
        F0R(deg, 360) {
            F0R(j, 5) {
                for (ii wedge : wheels[j]) {
                    int start = (wedge.A+speed[j]*i)%360;
                    if (deg >= start && deg - start <= wedge.B || deg + 360 - start <= wedge.B) {
                        count[deg]++;
                        break;
                    }
                }
            }
            if (count[deg] == 5) {
                cout << i << endl;
                return 0;
            }
        }
    }


    cout << "none" << endl;

    return 0;
}
