/*
 * Sweep the lilies from increasing y coordinate, increasing x coordinate.
 * Each lily must come from below or from the left.
 *
 * Note: The grader is very sketchy. Despite multiple solutions existing, the grader only
 * seems to accept a specific solution. Prioritize going from below before going from the left.
 */

#include <bits/stdc++.h>

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
#define LL_INF 4500000000000000000LL
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

void setupIO(const string &PROB = "") {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if (PROB.length() != 0) {
        ifstream infile(PROB + ".in");
        if (infile.good()) {
            freopen((PROB + ".in").c_str(), "r", stdin);
            freopen((PROB + ".out").c_str(), "w", stdout);
        }
    }
}

/* ============================ */

vii yLilies[100001];
int xLilies[100001];
int energy[300000];
int parent[300000];
iii A[300000];

int main() {
    setupIO();

    int n, k; cin >> n >> k;
    F0R(i, n) {
        int x, y, f;
        cin >> x >> y >> f;
        assert(x >= 0 && x <= 100000);
        assert(y >= 0 && y <= 100000);
        yLilies[y].pb(mp(x, i));
        A[i] = mp(f, mp(x, y));
    }
    SET(xLilies, -1, 100001);

    // Sweep from increasing y
    SET(energy, -INF, 300000);
    F0R(i, 100001) {
        SORT(yLilies[i]);
        int bestLeft = -1;
        for (ii lily : yLilies[i]) {
            // base case: first lily
            if (lily.pB == 0) {
                energy[lily.pB] = A[lily.pB].pA;
                xLilies[lily.pA] = lily.pB;
                bestLeft = lily.pB;
                parent[lily.pB] = -1;
                continue;
            }

            // Note: Due to sketchy grader, go from bottom must come before go from left.
            // go from bottom
            int bestBot = xLilies[lily.pA];
            if (bestBot != -1) {
                int botEnergy = energy[bestBot];
                if (botEnergy >= k) {
                    if (energy[lily.pB] <= botEnergy - k + A[lily.pB].pA) {
                        energy[lily.pB] = botEnergy - k + A[lily.pB].pA;
                        parent[lily.pB] = bestBot;
                    }
                }
            }

            // go from left
            if (bestLeft != -1) {
                int leftEnergy = energy[bestLeft];
                if (leftEnergy >= k) {
                    if (energy[lily.pB] < leftEnergy - k + A[lily.pB].pA) {
                        energy[lily.pB] = leftEnergy - k + A[lily.pB].pA;
                        parent[lily.pB] = bestLeft;
                    }
                }
            }

            if (bestLeft == -1 || energy[bestLeft] < energy[lily.pB]) {
                bestLeft = lily.pB;
            }
            if (xLilies[lily.pA] == -1 || energy[xLilies[lily.pA]] < energy[lily.pB]) {
                xLilies[lily.pA] = lily.pB;
            }
        }
    }

    cout << energy[n-1] << endl;
    vi lilies;
    int curLily = n-1;
    while (curLily != -1) {
        lilies.pb(curLily);
        curLily = parent[curLily];
    }
    cout << lilies.size() << endl;
    assert(lilies.back() == 0);
    F0Rd(i, lilies.size()) {
        cout << A[lilies[i]].pB.pA << " " << A[lilies[i]].pB.pB << endl;
    }

    return 0;
}