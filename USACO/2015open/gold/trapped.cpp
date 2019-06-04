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

struct Haybale {
    int pos, weight;
    bool operator<(const Haybale &other) const {
        return pos < other.pos;
    }
    bool operator==(const Haybale &other) const {
        return pos == other.pos;
    }
};

int main() {
    freopen("trapped.in", "r", stdin);
    freopen("trapped.out", "w", stdout);

    int n; cin >> n;
    Haybale haybales[n];
    map<int, int> posMapping;
    int haybalePos[n];
    F0R(i, n) {
        cin >> haybales[i].weight >> haybales[i].pos;
    }
    sort(haybales, haybales+n);
    F0R(i, n) {
        posMapping.insert(mp(haybales[i].pos, i));
        haybalePos[i] = haybales[i].pos;
    }
    sort(haybales, haybales + n, [](Haybale a, Haybale b) { return a.weight < b.weight; });
    reverse(haybales, haybales + n);
    bool badInterval[n-1]; memset(badInterval, false, sizeof badInterval);

    set<Haybale> placed;
    for (Haybale haybale : haybales) {
        if (placed.size() == 0) {
            placed.insert(haybale);
            continue;
        }
        if (placed.rbegin()->pos > haybale.pos) {
            auto nextOnRight = placed.upper_bound(haybale);
            int dist = nextOnRight->pos - haybale.pos;
            if (dist <= haybale.weight && dist <= nextOnRight->weight) {
                int start = posMapping[haybale.pos], end = posMapping[nextOnRight->pos];
                FOR(i, start, end) badInterval[i] = true;
            }
        }
        if (placed.begin()->pos < haybale.pos) {
            auto nextOnLeft = placed.lower_bound(haybale);
            if (nextOnLeft != placed.begin()) {
                nextOnLeft--;
                int dist = haybale.pos - nextOnLeft->pos;
                if (dist <= haybale.weight && dist <= nextOnLeft->weight) {
                    int end = posMapping[haybale.pos], start = posMapping[nextOnLeft->pos];
                    FOR(i, start, end) badInterval[i] = true;
                }
            }
        }
        placed.insert(haybale);
    }

    int ans = 0;
    F0R(i, n-1) if (badInterval[i]) ans += haybalePos[i+1]-haybalePos[i];
    cout << ans << endl;

    return 0;
}
