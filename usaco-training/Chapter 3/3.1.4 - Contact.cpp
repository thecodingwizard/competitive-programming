/*
ID: nathan.18
TASK: contact
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
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int main() {
    freopen("contact.in", "r", stdin);
    freopen("contact.out", "w", stdout);

    int a, b, n; cin >> a >> b >> n;
    string s, tmp;
    while (cin >> tmp) {
        s += tmp;
    }

    map<int, vector<string>> ans;
    map<string, int> ct;
    FOR(i, a, b+1) {
        ct.clear();
        F0R(j, (int)s.length()-i+1) {
            string sub = s.substr(j, i);
            if (ct.count(sub)) ct[sub]++;
            else ct[sub] = 1;
        }
        for (pair<string, int> sub : ct) {
            ans[sub.B].push_back(sub.A);
        }
    }

    auto it = ans.rbegin();
    while (n-- && it != ans.rend()) {
        cout << it->A << endl;
        int ctr = 0;
        for (string s : it->B) {
            if (++ctr == 7) {
                ctr = 1;
                cout << endl;
            } else if (ctr != 1) {
                cout << " ";
            }
            cout << s;
        }
        cout << endl;
        it++;
    }

    return 0;
}
