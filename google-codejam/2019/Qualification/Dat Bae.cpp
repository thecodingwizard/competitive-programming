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
    int t; cin >> t;
    F0R1(caseNum, t) {
        int n, b, f; cin >> n >> b >> f;

        int val[n-b+1]; SET(val, 0, n-b);
        F0R(i, 5) {
            string s;
            F0R(j, n) {
                if (j & (1 << i)) s += "1";
                else s += "0";
            }
            cout << s << endl;
            string resp; cin >> resp;
            F0R(j, n-b) {
                if (resp[j] == '1') {
                    val[j] |= (1 << i);
                }
            }
        }

        int prevVal = -1;
        int ctr = 0;
        F0R(i, n-b) {
            val[i] += ctr*32;
            if (val[i] < prevVal) {
                ctr++;
                val[i] += 32;
            }
            prevVal = val[i];
        }

        vi missing;
        prevVal = -1;
        val[n-b] = n;
        F0R(i, n-b+1) {
            if (val[i] != prevVal+1) {
                FOR(j, prevVal+1, val[i]) {
                    missing.pb(j);
                }
            }
            prevVal = val[i];
        }
        cout << missing[0];
        for (int i = 1; i < missing.size(); i++) cout << " " << missing[i];
        cout << endl;

        int res; cin >> res;
    }

    return 0;
}
