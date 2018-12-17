/*
ID: nathan.18
TASK: lgame
LANG: C++
*/
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

using namespace std;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define F0R1(i, a) for (int i=1; i<=(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define F0Rd1(i, a) for (int i=a; i>0; i--)
#define SORT(vec) sort(vec.begin(), vec.end())

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
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<ll> vl;

void fastscan(int&n) {bool negative=false;register int c;n=0;c=getchar();if(c=='-') {negative=true;c=getchar();}
    for(;(c>47&&c<58);c=getchar()){n=n*10+c-48;}
    if(negative){n*=-1;}}

/* For every k in the range 0...n!-1 inclusive, returns a unique permutation of s */
/* See: https://stackoverflow.com/questions/1995328/are-there-any-better-methods-to-do-permutation-of-string */
string permutation(int k, string x) {
    string s = x;
    for (int j = 1; j < s.size(); ++j) {
        swap(s[k % (j + 1)], s[j]);
        k = k / (j + 1);
    }
    return s;
}
int fact(int n) {
    int x = 1;
    while (n > 0) {
        x *= n--;
    }
    return x;
}

void setupIO(string PROB) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    ifstream infile(PROB + ".in");
    if (infile.good()) {
        freopen((PROB + ".in").c_str(), "r", stdin);
        freopen((PROB + ".out").c_str(), "w", stdout);
    }
}

/* ============================ */

ifstream dictFile;
map<char, int> val;

int getScore(string s) {
    int score = 0;
    for (char c : s) score += val[c];
    return score;
}

int main() {
    setupIO("lgame");

    set<string> dict;
    dictFile.open("lgame.dict");
    string x;
    while (dictFile >> x && x != ".") {
        dict.insert(x);
    }
    dictFile.close();

    val.insert(mp('a', 2));
    val.insert(mp('b', 5));
    val.insert(mp('c', 4));
    val.insert(mp('d', 4));
    val.insert(mp('e', 1));
    val.insert(mp('f', 6));
    val.insert(mp('g', 5));
    val.insert(mp('h', 5));
    val.insert(mp('i', 1));
    val.insert(mp('j', 7));
    val.insert(mp('k', 6));
    val.insert(mp('l', 3));
    val.insert(mp('m', 5));
    val.insert(mp('n', 2));
    val.insert(mp('o', 3));
    val.insert(mp('p', 5));
    val.insert(mp('q', 7));
    val.insert(mp('r', 2));
    val.insert(mp('s', 1));
    val.insert(mp('t', 2));
    val.insert(mp('u', 4));
    val.insert(mp('v', 6));
    val.insert(mp('w', 6));
    val.insert(mp('x', 7));
    val.insert(mp('y', 5));
    val.insert(mp('z', 7));

    cin >> x;
    int n = x.length();
    int bestScore = 0;
    vector<pair<string, string>> combinations;
    F0R(k, fact(n)) {
        string bessie = permutation(k, x);
        F0R(i, n) {
            F0R(j, n-i) {
                string first = bessie.substr(i, j);
                string next = bessie.substr(i+j, n-i-j);
                int score = 0;
                if ((first == "" || dict.count(first) > 0) && (next == "" || dict.count(next) > 0)) {
                    score = getScore(first) + getScore(next);
                    if (score > bestScore) {
                        combinations.clear();
                        bestScore = score;
                        if (first == "") combinations.pb(mp(next, first));
                        else if (next == "") combinations.pb(mp(first, next));
                        else if (first > next) combinations.pb(mp(next, first));
                        else combinations.pb(mp(first, next));
                    } else if (score == bestScore) {
                        if (first == "") combinations.pb(mp(next, first));
                        else if (next == "") combinations.pb(mp(first, next));
                        else if (first > next) combinations.pb(mp(next, first));
                        else combinations.pb(mp(first, next));
                    }
                }
            }
        }
    }
    cout << bestScore << endl;

    SORT(combinations);

    set<pair<string, string>> magic;
    for (pair<string, string> x : combinations) {
        if (x.pB == "") {
            if (magic.count(x) > 0) continue;
            magic.insert(x);
            cout << x.pA << endl;
        } else {
            string a = x.pA, b = x.pB;
            if (a > b) continue;
            if (magic.count(x) > 0) continue;
            magic.insert(x);
            cout << a << " " << b << endl;
        }
    }

    return 0;
}