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
#define RSORT(vec) sort(vec.rbegin(), vec.rend())
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
    int t; cin >> t;
    F0R1(caseNum, t) {
        int p, q; cin >> p >> q;
        vii vertEvents, horizEvents;
        vertEvents.pb(mp(0, 0));
        horizEvents.pb(mp(0, 0));
        F0R(i, p) {
            int x, y; char d; cin >> x >> y >> d;
            if (d == 'N') {
                vertEvents.pb(mp(y + 1, 1));
            } else if (d == 'E') {
                horizEvents.pb(mp(x + 1, 1));
            } else if (d == 'S') {
                vertEvents.pb(mp(0, 1));
                vertEvents.pb(mp(y, -1));
            } else {
                horizEvents.pb(mp(0, 1));
                horizEvents.pb(mp(x, -1));
            }
        }
        SORT(horizEvents);
        SORT(vertEvents);
        int best = 0;
        ii bestCoord = { 0, 0 };
        int ct = 0;
        for (int i = 0; i < horizEvents.size(); i++) {
            int loc = horizEvents[i].pA;
            ct += horizEvents[i].pB;
            while (i + 1 < horizEvents.size() && horizEvents[i + 1].pA == loc) {
                i++;
                ct += horizEvents[i].pB;
            }
            int otherCt = 0;
            for (int j = 0; j < vertEvents.size(); j++) {
                int otherLoc = vertEvents[j].pA;
                otherCt += vertEvents[j].pB;
                while (j + 1 < vertEvents.size() && vertEvents[j + 1].pA == otherLoc) {
                    j++;
                    otherCt += vertEvents[j].pB;
                }
                int opt = ct + otherCt;
                if (best < opt) {
                    best = opt;
                    bestCoord = { loc, otherLoc };
                }
            }
        }
        cout << "Case #" << caseNum << ": " << bestCoord.pA << " " << bestCoord.pB << endl;
    }

    return 0;
}