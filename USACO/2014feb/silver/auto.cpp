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
    freopen("auto.in", "r", stdin);
    freopen("auto.out", "w", stdout);

    int w, n; cin >> w >> n;
    map<string, int> pos;
    string words[w]; F0R(i, w) { cin >> words[i]; pos.insert(mp(words[i], i+1)); }
    sort(words, words+w);

    F0R(i, n) {
        int k; string word;
        cin >> k >> word;
        auto it = lower_bound(words, words+w, word);
        it += k-1;
        if (it-words >= w || strncmp(it->c_str(), word.c_str(), word.size()) != 0) {
            cout << "-1" << endl;
        } else {
            cout << pos[*it] << endl;
        }
    }

    return 0;
}
