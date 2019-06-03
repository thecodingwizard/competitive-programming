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
    int n; cin >> n;
    set<string> dict;
    vector<string> orderedDict;
    F0R(i, n) {
        string s; cin >> s;
        dict.insert(s);
        orderedDict.pb(s);
    }

    set<string> options;
    int q; cin >> q;
    F0R(i, q) {
        options.clear();
        string s; cin >> s;
        if (dict.count(s)) {
            cout << s << " is correct" << endl;
            goto next;
        }
        // insert character after s
        for (char c = 'a'; c <= 'z'; c++) {
            string test = s + c;
            if (dict.count(test)) {
                options.insert(test);
            }
        }
        F0R(j, s.length()) {
            // insert character before j
            for (char c = 'a'; c <= 'z'; c++) {
                string test = s.substr(0, j) + c + s.substr(j, s.length() - j);
                if (dict.count(test)) {
                    options.insert(test);
                }
            }
            // delete character
            string test = s.substr(0, j) + s.substr(j + 1, s.length() - j - 1);
            if (dict.count(test)) {
                options.insert(test);
            }
            // replace character
            for (char c = 'a'; c <= 'z'; c++) {
                test = s.substr(0, j) + c + s.substr(j + 1, s.length() - j - 1);
                if (dict.count(test)) {
                    options.insert(test);
                }
            }
            // swap character
            if (j != s.length() - 1) {
                test = s.substr(0, j) + s[j+1] + s[j] + s.substr(j+2, s.length() - j - 2);
                if (dict.count(test)) {
                    options.insert(test);
                }
            }
        }

        for (string x : orderedDict) {
            if (options.count(x)) {
                cout << s << " is a misspelling of " << x << endl;
                goto next;
            }
        }

        cout << s << " is unknown" << endl;

        next:
        continue;
    }

    return 0;
}

