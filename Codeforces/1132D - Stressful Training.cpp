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

int n, k; 
ll A[200000], B[200000];
int ct[200001];

bool can(ll x) {
    /* cout << "can: " << x << endl; */
    SET(ct, 0, 200001);

    int kLeft = k;
    F0R(i, n) {
        ll charge = A[i];
        if (x == 0) {
            if (charge > k*B[i]) continue;
            return false;
        }
        ll elapsedTime = 0;
        while (true) {
            /* if (kLeft < 0) return false; */
            if (elapsedTime >= k) break;
            ll nextChargeTime = charge/B[i] + elapsedTime;
            if (nextChargeTime >= k) break;
            if (x < B[i]) {
                /* cout << nextChargeTime << endl; */
                ll extraChargeNeeded = -charge + (charge/B[i] + 1)*B[i] - x;
                nextChargeTime -= (extraChargeNeeded+x-1)/x;
                /* cout << extraChargeNeeded << " " << nextChargeTime << endl; */
                if (nextChargeTime < 0) return false;
            }
            ct[nextChargeTime]++;
            charge = charge - B[i]*(nextChargeTime-elapsedTime+1) + x;
            /* if (x == 5) cout << "inner " << charge << " " << nextChargeTime+1 << endl; */
            assert(charge >= 0);
            kLeft--;
            elapsedTime = nextChargeTime + 1;
        }
    }
    
    /* if (x == 5) { */
    /*     cout << "hi" << endl; */
    /*     F0R(i, k+1) cout << ct[i] << endl; */
    /*     cout << "bye" << endl; */
    /* } */

    F0R(i, k+1) {
        if (i != 0) ct[i] += ct[i-1];
        if (ct[i] > i+1) return false;
    }

    return true;
}

int main() {
    cin >> n >> k;
    --k;
    F0R(i, n) cin >> A[i];
    F0R(i, n) cin >> B[i];

    ll lo = 0, hi = 2000000000001L, mid, ans = -1;
    while (lo < hi) {
        mid = (lo + hi)/2;
        if (can(mid)) {
            hi = mid;
            ans = mid;
        } else {
            lo = mid + 1;
        }
    }
    cout << ans << endl;

    return 0;
}

