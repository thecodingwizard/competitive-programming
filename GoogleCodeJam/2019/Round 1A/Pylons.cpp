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

int r, c;
bool taken[20][20];
ii nextOne[20][20];

bool run(int a, int b) {
    if (taken[a][b]) return false;
    taken[a][b] = true;
    bool done = true;
    F0R(i, r) {
        F0R(j, c) {
            if (!taken[i][j]) done = false;
        }
    }
    if (done) {
        nextOne[a][b] = mp(-1, -1);
        return true;
    }
    F0R(i, r) {
        F0R(j, c) {
            if (i == a || j == b) continue;
            if (i + j == a + b) continue;
            if (j - i == b - a) continue;
            if (run(i, j)) {
                nextOne[a][b] = mp(i, j);
                return true;
            }
        }
    }
    taken[a][b] = false;
    return false;
}

vii ansTwo[21];
vii ansThree[21];

int main() {
    FOR(i, 5, 21) {
        r = 2; c = i;
        SET2D(taken, false, 20, 20);
        run(0, 0);
        ii nxt = mp(0, 0);
        while (nxt.pA != -1) {
            ansTwo[i].pb(nxt);
            nxt = nextOne[nxt.pA][nxt.pB];
        }
    }
    FOR(i, 4, 8) {
        r = 3; c = i;
        SET2D(taken, false, 20, 20);
        ii nxt;
        if (i % 2 == 0) {
            run(0, 0);
            nxt = mp(0, 0);
        } else {
            run(0, 2);
            nxt = mp(0, 2);
        }
        while (nxt.pA != -1) {
            ansThree[i].pb(nxt);
            nxt = nextOne[nxt.pA][nxt.pB];
        }
    }
    FOR(i, 8, 12) {
        // 4 + (4, 5, 6, 7)
        for (auto x : ansThree[4]) ansThree[i].pb(x);
        for (auto x : ansThree[i-4]) {
            x.pB += 4;
            ansThree[i].pb(x);
        }
    }
    FOR(i, 12, 20) {
        // 4 + 4 + (4, 5, 6, 7, 8, 9, 10, 11)
        for (auto x : ansThree[4]) ansThree[i].pb(x);
        for (auto x : ansThree[4]) {
            x.pB += 4;
            ansThree[i].pb(x);
        }
        for (auto x : ansThree[i - 8]) {
            x.pB += 8;
            ansThree[i].pb(x);
        }
    }
    F0R(i, 5) {
        for (auto x : ansThree[4]) {
            x.pB += i*4;
            ansThree[20].pb(x);
        }
    }

    int t; cin >> t;
    F0R1(caseNum, t) {
        cin >> r >> c;
//        vii ansChecker;
        if (c < 5) {
            SET2D(taken, false, 20, 20);
            bool ans = run(0, 0);

            cout << "Case #" << caseNum << ": ";
            if (!ans) cout << "IMPOSSIBLE" << endl;
            else {
                cout << "POSSIBLE" << endl;
                ii nxt = mp(0, 0);
                while (nxt.pA != -1) {
                    cout << nxt.pA + 1 << " " << nxt.pB + 1 << endl;
//                    ansChecker.pb(nxt);
                    nxt = nextOne[nxt.pA][nxt.pB];
                }
            }
        } else {
            cout << "Case #" << caseNum << ": POSSIBLE" << endl;
            int offset = 0;
            if (r & 1) {
                // output one three
                for (auto x : ansThree[c]) {
                    cout << x.pA + 1 << " " << x.pB + 1 << endl;
//                    ansChecker.pb(x);
                }
                F0R(i, (r-3)/2) {
                    for (auto x : ansTwo[c]) {
                        cout << x.pA + 4 + i*2  << " " << x.pB + 1 << endl;
//                        ansChecker.pb(mp(x.pA + 3 + i*2, x.pB));
                    }
                }
            } else {
                F0R(i, r/2) {
                    for (auto x : ansTwo[c]) {
                        cout << x.pA + 1 + i*2  << " " << x.pB + 1 << endl;
//                        ansChecker.pb(mp(x.pA + i*2, x.pB));
                    }
                }
            }
        }
//        if (ansChecker.size() != 0) {
//            bool visited[r][c]; SET2D(visited, false, r, c);
//            ii prev = {-1, -1};
//            for (ii x : ansChecker) {
//                assert(x.pA < r && x.pB < c && x.pA >= 0 && x.pB >= 0);
//                assert(!visited[x.pA][x.pB]);
//                visited[x.pA][x.pB] = true;
//                if (prev.pA == -1) {
//                    prev = x;
//                    continue;
//                }
//                int i = x.pA, j = x.pB, a = prev.pA, b = prev.pB;
//                if (i == a || j == b) assert(false);
//                if (i + j == a + b) {
//                    assert(false);
//                }
//                if (j - i == b - a) assert(false);
//                prev = x;
//            }
//            F0R(i, r) {
//                F0R(j, c) {
//                    if (!visited[i][j]) {
//                        assert(false);
//                    }
//                }
//            }
//        }
    }

    return 0;
}
