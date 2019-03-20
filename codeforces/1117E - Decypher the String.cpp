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
    string s; cin >> s;
    int n = s.length();
    int A[n]; F0R(i, n) A[i] = 0;
    int B[n]; F0R(i, n) B[i] = 0;

    string first = "", second = "", third = "";
    F0R(i, n) {
        first += ('a' + (i%26));
        A[i] += (i%26);
    }
    F0R(i, 10000) {
        F0R(j, 26) {
            second += ('a' + (i % 26));
            A[i*26+j] += (i%26)*26;
            if (second.length() == n) goto bessie;
        }
    }
    bessie:
    F0R(i, 10000) {
        F0R(j, 26*26) {
            third += ('a' + (i % 26));
            A[i*26*26+j] += (i%26)*26*26;
            if (third.length() == n) goto fj;
        }
    }
    fj:
    // cout << first << " " << second << " " << third << endl;
    assert(first.length() == n);
    assert(second.length() == n);
    assert(third.length() == n);

    cout << "? " << first << endl << "? " << second << endl << "? " << third << endl;

    string res1, res2, res3; cin >> res1 >> res2 >> res3;
    map<int, int> mapping;
    F0R(i, n) {
        B[i] = res1[i] - 'a' + (res2[i] - 'a')*26 + (res3[i] - 'a')*26*26;
        assert(mapping.count(B[i]) == 0);
        mapping[B[i]] = i;
        // cout << "Mapping " << B[i] << " to " << i << endl;
    }

    char ans[n];
    F0R(i, n) {
        ans[i] = s[mapping[i]];
    }

    cout << "! ";
    F0R(i, n) cout << ans[i];
    cout << endl;

    return 0;
}
