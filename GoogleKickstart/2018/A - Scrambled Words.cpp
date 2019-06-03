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

struct PS {
    int ct[26];
    PS() {
        F0R(i, 26) ct[i] = 0;
    }

    PS operator - (const PS &p) const {
        PS toReturn;
        F0R(i, 26) {
            toReturn.ct[i] = ct[i] - p.ct[i];
        }
        return toReturn;
    }

    bool operator<(const PS &rhs) const {
        F0R(i, 26) {
            if (ct[i] != rhs.ct[i]) return ct[i] < rhs.ct[i];
        }
        return false;
    }
};

bool operator!=(const PS &lhs, const PS &rhs) {
    F0R(i, 26) {
        if (lhs.ct[i] != rhs.ct[i]) return true;
    }
    return false;
}

ll si[1000000];
char text[1000000];
// following is important! I'm bad at C++ :(
PS arrayOutOfBounds;
PS ps[1000000];
bool ans[20000];

int main() {
    int t; cin >> t;
    FOR(caseNum, 1, t+1) {
        int l;
        cin >> l;
        string rawDict[l];
        F0R(i, l) cin >> rawDict[i];
        PS dict[l];
        map<int, map<int, map<PS, vi>>> fastDict[26];
        set<int> lengths;
        F0R(i, l) {
            F0R(j, rawDict[i].length()) {
                dict[i].ct[rawDict[i][j] - 'a']++;
            }
            fastDict[rawDict[i][0] - 'a'][rawDict[i].length()][rawDict[i][rawDict[i].length() - 1] - 'a'][dict[i]].pb(i);
            lengths.insert(rawDict[i].length());
        }
        cin >> text[0] >> text[1];
        si[0] = text[0]; si[1] = text[1];
        ll n, a, b, c, d;
        cin >> n >> a >> b >> c >> d;
        FOR(i, 2, n) {
            si[i] = (a*si[i-1]+b*si[i-2]+c)%d;
            text[i] = 97 + (si[i]%26);
        }
        F0R(i, n) {
            F0R(j, 26) {
                ps[i].ct[j] = ps[i - 1].ct[j];
                if (text[i] - 'a' == j) ps[i].ct[j]++;
            }
        }

        SET(ans, false, 20000);
        F0R(i, n) {
            for (int len : lengths) {
                if (len > n - 1) continue;
                if (fastDict[text[i]-'a'].count(len) == 0) continue;
                if (fastDict[text[i]-'a'][len].count(text[i+len-1]-'a') == 0) continue;
                if (fastDict[text[i]-'a'][len][text[i+len-1]-'a'].count(ps[i + len - 1] - ps[i - 1]) == 0) continue;
                for (int x : fastDict[text[i]-'a'][len][text[i+len-1]-'a'][ps[i + len - 1] - ps[i - 1]]) {
                    ans[x] = true;
                }
                fastDict[text[i]-'a'][len][text[i+len-1]-'a'].erase(ps[i + len - 1] - ps[i - 1]);
            }
        }
        int realAns = 0;
        F0R(i, l) if (ans[i]) realAns++;
        cout << "Case #" << caseNum << ": " << realAns << endl;
    }

    return 0;
}