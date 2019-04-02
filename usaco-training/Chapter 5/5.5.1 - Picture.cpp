/*
ID: nathan.18
TASK: picture
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
#include <ctime>
#include <list>

using namespace std;

template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define F0R1(i, a) for (int i=1; i<=(a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
#define F0Rd1(i, a) for (int i=a; i>0; i--)
#define SORT(vec) sort(vec.begin(), vec.end())
#define MIN(a, b) a = min(a, b)
#define MAX(a, b) a = max(a, b)

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
#define SET3D(arr, val, dim1, dim2, dim3) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) arr[i][j][k] = val;
#define SET4D(arr, val, dim1, dim2, dim3, dim4) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) F0R(l, dim4) arr[i][j][k][l] = val;
#define READGRID(arr, dim) F0R(i, dim) F0R(j, dim) cin >> arr[i][j];
#define all(x) (x).begin(), (x).end()

typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<ll> vl;

void setupIO(const string &PROB) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream infile(PROB + ".in");
    if (infile.good()) {
        freopen((PROB + ".in").c_str(), "r", stdin);
        freopen((PROB + ".out").c_str(), "w", stdout);
    }
}

/* ============================ */

int main() {
    setupIO("picture");

    int n; cin >> n;
    vector<pair<ii, ii>> horizEvents;
    vector<pair<ii, ii>> vertEvents;
    F0R(i, n) {
        int a, b, c, d; cin >> a >> b >> c >> d;

        horizEvents.pb(mp(mp(a, 0), mp(b, d)));
        horizEvents.pb(mp(mp(c, 1), mp(b, d)));

        vertEvents.pb(mp(mp(b, 0), mp(a, c)));
        vertEvents.pb(mp(mp(d, 1), mp(a, c)));
    }

    SORT(horizEvents);
    SORT(vertEvents);

    int ans = 0;

    multiset<ii> S;
    int curLoc = -INF;
    for (auto ev : horizEvents) {
        int len = ev.pA.pA - curLoc;
        int ct = 0;
        for (ii x : S) {
            if (!x.pB) {
                if (ct == 0) ans += len;
                ct++;
            } else {
                ct--;
                if (ct == 0) ans += len;
            }
        }
        
        if (!ev.pA.pB) {
            S.insert(mp(ev.pB.pA, 0));
            S.insert(mp(ev.pB.pB, 1));
        } else {
            S.erase(S.find(mp(ev.pB.pA, 0)));
            S.erase(S.find(mp(ev.pB.pB, 1)));
        }
        curLoc = ev.pA.pA;
    }
    assert(S.size() == 0);

    curLoc = -INF;
    for (auto ev : vertEvents) {
        int len = ev.pA.pA - curLoc;
        int ct = 0;
        for (ii x : S) {
            if (!x.pB) {
                if (ct == 0) ans += len;
                ct++;
            } else {
                ct--;
                if (ct == 0) ans += len;
            }
        }

        if (!ev.pA.pB) {
            S.insert(mp(ev.pB.pA, 0));
            S.insert(mp(ev.pB.pB, 1));
        } else {
            S.erase(S.find(mp(ev.pB.pA, 0)));
            S.erase(S.find(mp(ev.pB.pB, 1)));
        }
        curLoc = ev.pA.pA;
    }

    cout << ans << endl;

    return 0;
}
