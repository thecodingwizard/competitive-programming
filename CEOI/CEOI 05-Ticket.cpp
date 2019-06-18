/*
 * Greedy approach: https://github.com/mostafa-saad/MyCompetitiveProgramming/tree/master/Olympiad/CEOI/official/2005
 *
 * First, note that we should greedily take as many correct seat assignments as possible.
 * Assigning someone to a specific seat will force up to two other assignments to be removed. However,
 * even if two current assignments are removed, there will be no change in our income since we gain +2 income and lose 2 income.
 *
 * Therefore, we can greedily assign as many correct seats as we can by sweeping from right-to-left.
 *
 * However, consider a pair of requests, A and B. Suppose we can only fulfill one of them since they overlap. Which do we fulfill?
 * We want to minimize the number of wasted seats. Let's say that X < A, B is taken. if (A - X) % L < (B - X) % L, we would prefer
 * A over B. (the modulo is the number of wasted seats). We can sweep from left-to-right and try to optimize each correct seat assignment
 * to minimize the number of wasted seats. Note that it's important for us to sweep left-to-right since we swept in the
 * opposite direction the first time around.
 *
 * Then we can greedily assign the rest of the seats.
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

int main() {
    setupIO();

    int m, l; cin >> m >> l;
    int n; cin >> n;
    ii A[n];
    F0R(i, n) {
        cin >> A[i].pA;
        A[i].pB = i + 1;
    }
    sort(A, A+n);
    bool take[n];

    int curLoc = m + 1;
    F0Rd(i, n) {
        if (A[i].pA + l - 1 < curLoc) {
            curLoc = A[i].pA;
            take[i] = true;
        } else {
            take[i] = false;
        }
    }

    curLoc = 1;
    F0R(i, n) {
        int alternative = -1;
        int altMod = INF;
        while (i < n && !take[i]) {
            int thisMod = (A[i].pA - curLoc) % l;
            if (A[i].pA < curLoc) {
                i++;
                continue;
            }
            if (thisMod < altMod) {
                altMod = thisMod;
                alternative = i;
            }
            i++;
        }
        if (i == n || !take[i]) break;
        int curMod = (A[i].pA - curLoc) % l;
        if (curMod > altMod) {
            take[i] = false;
            take[alternative] = true;
            curLoc = A[alternative].pA + l;
            i = alternative;
        } else {
            curLoc = A[i].pA + l;
        }
    }

    vi takeTickets, availTickets;
    F0R(i, n) {
        if (take[i]) takeTickets.pb(i);
        else availTickets.pb(i);
    }

    int ans = 0;
    vii print;
    int takeIdx = 0, availIdx = 0;
    F0R1(i, m-l+1) {
        int t = takeIdx < takeTickets.size() ? takeTickets[takeIdx] : -1, a = availIdx < availTickets.size() ? availTickets[availIdx] : -1;
        if (t != -1 && A[t].pA < i + l) {
            ans += 2;
            print.pb(mp(A[t].pB, A[t].pA));
            i = A[t].pA + l - 1;
            takeIdx++;
        } else if (a != -1){
            ans++;
            print.pb(mp(A[a].pB, i));
            i += l - 1;
            availIdx++;
        }
    }

    cout << ans << endl;
    cout << print.size() << endl;
    for (ii x : print) cout << x.pA << " " << x.pB << endl;

    return 0;
}