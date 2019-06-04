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

int main() {
    freopen("cardgame.in", "r", stdin);
    freopen("cardgame.out", "w", stdout);

    int n; cin >> n;
    vi elsie, bessie;
    bool taken[100001]; F0R(i, 100001) taken[i] = false;
    F0R(i, n) {
        int x; cin >> x;
        taken[x] = true;
        elsie.push_back(x);
    }
    FOR(i, 1, n*2+1) {
        if (!taken[i]) bessie.push_back(i);
    }
    SORT(bessie);

    set<int> small, big;
    F0R(i, n) {
        if (i < n/2) small.insert(bessie[i]);
        else big.insert(bessie[i]);
    }

    int score = 0;
    F0R(i, n) {
        int card = elsie[i];
        if (i < n/2) {
            // high card
            auto it = big.lower_bound(card);
            if (it == big.end()) continue;
            big.erase(it);
            score++;
        } else {
            // low card
            auto it = small.lower_bound(card);
            if (it == small.begin()) continue;
            it--;
            small.erase(it);
            score++;
        }
    }

    cout << score << endl;

    return 0;
}
