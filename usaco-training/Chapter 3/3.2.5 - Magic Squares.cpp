/*
ID: nathan.18
TASK: msquare
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
#define pA first
#define pB second
#define mp make_pair
#define pb push_back
#define PI acos(-1.0)
#define ll long long
#define MOD (int)(2e+9+11)
#define SET(vec, val, size) for (int i = 0; i < size; i++) vec[i] = val;
#define SET2D(arr, val, dim1, dim2) F0R(i, dim1) F0R(j, dim2) arr[i][j] = val;
typedef pair<int, int> ii;
typedef pair<ii, int> iii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vl;

string calcC(string x) {
    return string() + x[0] + x[6] + x[1] + x[3] + x[4] + x[2] + x[5] + x[7];
}

string calcB(string x) {
    return string() + x[3] + x[0] + x[1] + x[2] + x[5] + x[6] + x[7] + x[4];
}

string calcA(string x) {
    return string() + x[7] + x[6] + x[5] + x[4] + x[3] + x[2] + x[1] + x[0];
}

int main() {
    freopen("msquare.in", "r", stdin);
    freopen("msquare.out", "w", stdout);

    string target; F0R(i, 8) { string x; cin >> x; target += x; }
    if (target == "12345678") {
        cout << "0" << endl << endl;
        return 0;
    }

    queue<pair<string, string>> q;
    set<string> visited;
    q.push(mp("12345678", ""));

    while (!q.empty()) {
        pair<string, string> next = q.front(); q.pop();
        if (visited.count(next.pA)) continue;
        visited.insert(next.pA);

        if (next.pA == target) {
            cout << next.pB.length();
            F0R(i, next.pB.length()) {
                if (i % 60 == 0) cout << endl;
                cout << next.pB[i];
            }
            cout << endl;
            return 0;
        }

        q.push(mp(calcA(next.pA), next.pB + "A"));
        q.push(mp(calcB(next.pA), next.pB + "B"));
        q.push(mp(calcC(next.pA), next.pB + "C"));
    }

    return 0;
}
