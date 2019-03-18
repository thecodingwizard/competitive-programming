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

vii children[100];
int inDegree[100];
list<ii> tour;

void eulerTour(int node, list<ii>::iterator it) {
    for (int i = 0; i < children[node].size(); i++) {
        ii child = children[node][i];
        if (child.pB == 1) {
            children[node][i].pB = 0;
            for (int j = 0; j < children[child.pA].size(); j++) {
                ii x = children[child.pA][j];
                // Remove backedge
                if (x.pA == node && x.pB == 1) {
                    children[child.pA][j].pB = 0;
                    break;
                }
            }
            eulerTour(child.pA, tour.insert(it, mp(child.pA, node)));
        }
    }
}

int main() {
    int T; cin >> T;
    F0R1(caseNum, T) {
        int n; cin >> n;

        F0R(i, 100) children[i].clear();
        SET(inDegree, 0, 100);
        tour.clear();

        int start = 0;
        F0R(i, n) {
            int a, b; cin >> a >> b;
            children[a].pb(mp(b, 1));
            children[b].pb(mp(a, 1));
            inDegree[a]++;
            inDegree[b]++;
            if (i == 0) start = a;
        }
        assert(start != 0);

        bool good = true;
        FOR(i, 1, 51) {
            if (inDegree[i] % 2 != 0) {
                good = false;
            }
        }
        if (good) {
            eulerTour(start, tour.begin());
        }

        if (caseNum != 1) cout << endl;
        cout << "Case #" << caseNum << endl;

        if (good && tour.size() == n) {
            for (ii x : tour) {
                cout << x.pA << " " << x.pB << endl;
            }
        } else {
            cout << "some beads may be lost" << endl;
        }
    }

    return 0;
}
