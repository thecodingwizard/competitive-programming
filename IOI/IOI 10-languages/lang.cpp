//#pragma GCC optimize ("O3")
//#pragma GCC target ("sse4")

#include <bits/stdc++.h>

using namespace std;

template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define F0R1(i, a) for (int i=1; i<=(a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
#define trav(a, x) for (auto& a : x)
#define MIN(a, b) a = min(a, b)
#define MAX(a, b) a = max(a, b)

#define INF 1000000010
#define LL_INF 4500000000000000000LL
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define pA first
#define pB second
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define eb emplace_back
#define PI acos(-1.0)
#define MOD2 (int)(2e+9+11)
#define MOD (int)(1e+9+7)
#define SET(vec, val, size) for (int i = 0; i < size; i++) vec[i] = val;
#define SET2D(arr, val, dim1, dim2) F0R(i, dim1) F0R(j, dim2) arr[i][j] = val;
#define SET3D(arr, val, dim1, dim2, dim3) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) arr[i][j][k] = val;
#define SET4D(arr, val, dim1, dim2, dim3, dim4) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) F0R(l, dim4) arr[i][j][k][l] = val;

#define lb lower_bound
#define ub upper_bound
#define sz(x) (int)x.size()
#define beg(x) x.begin()
#define en(x) x.end()
#define all(x) beg(x), en(x)
#define resz resize
#define SORT(vec) sort(all(vec))
#define RSORT(vec) sort(vec.rbegin(),vec.rend())

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<ll> vl;

// @formatter:off
// Source: Benq (https://github.com/bqi343/USACO) [Modified]
namespace input {
    template<class T> void re(complex<T>& x);
    template<class T1, class T2> void re(pair<T1,T2>& p);
    template<class T> void re(vector<T>& a);
    template<class T, size_t SZ> void re(array<T,SZ>& a);
    template<class T> void reA(T A[], int sz);

    template<class T> void re(T& x) { cin >> x; }
    void re(double& x) { string t; re(t); x = stod(t); }
    void re(ld& x) { string t; re(t); x = stold(t); }
    template<class Arg, class... Args> void re(Arg& first, Args&... rest) {
        re(first); re(rest...);
    }

    template<class T1, class T2> void re(pair<T1,T2>& p) { re(p.pA,p.pB); }
    template<class T> void re(vector<T>& a) { F0R(i,sz(a)) re(a[i]); }
    template<class T, size_t SZ> void re(array<T,SZ>& a) { F0R(i,SZ) re(a[i]); }
    template<class T> void reA(T A[], int sz) { F0R(i, sz) re(A[i]); }

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
}
using namespace input;

namespace output {
    template<class T1, class T2> void prD(const pair<T1,T2>& x);
    template<class T, size_t SZ> void prD(const array<T,SZ>& x);
    template<class T> void prD(const vector<T>& x);
    template<class T> void prD(const set<T>& x);
    template<class T1, class T2> void prD(const map<T1,T2>& x);

    template<class T1, class T2> void pr(const pair<T1,T2>& x);
    template<class T, size_t SZ> void pr(const array<T,SZ>& x);
    template<class T> void pr(const vector<T>& x);
    template<class T> void pr(const set<T>& x);
    template<class T1, class T2> void pr(const map<T1,T2>& x);

    template<class T> void prD(const T& x) { cout << x; cout.flush(); }
    template<class Arg, class... Args> void prD(const Arg& first, const Args&... rest) {
        prD(first); prD(rest...);
    }

    template<class T1, class T2> void prD(const pair<T1,T2>& x) {
        prD("{",x.pA,", ",x.pB,"}");
    }
    template<class T> void prDContain(const T& x) {
        prD("{");
        bool fst = 1; for (const auto& a: x) prD(!fst?", ":"",a), fst = 0; // const needed for vector<bool>
        prD("}");
    }
    template<class T, size_t SZ> void prD(const array<T,SZ>& x) { prDContain(x); }
    template<class T> void prD(const vector<T>& x) { prDContain(x); }
    template<class T> void prD(const set<T>& x) { prDContain(x); }
    template<class T1, class T2> void prD(const map<T1,T2>& x) { prDContain(x); }

    void psD() { prD("\n"); }
    template<class Arg> void psD(const Arg& first) {
        prD(first); psD(); // no space at end of line
    }
    template<class Arg, class... Args> void psD(const Arg& first, const Args&... rest) {
        prD(first," "); psD(rest...); // print w/ spaces
    }


    template<class T> void pr(const T& x) { cout << x; }
    template<class Arg, class... Args> void pr(const Arg& first, const Args&... rest) {
        pr(first); pr(rest...);
    }

    template<class T1, class T2> void pr(const pair<T1,T2>& x) {
        pr(x.pA, " ", x.pB);
    }
    template<class T> void prContain(const T& x) {
        bool fst = 1; for (const auto& a: x) pr(!fst?" ":"",a), fst = 0; // const needed for vector<bool>
    }
    template<class T, size_t SZ> void pr(const array<T,SZ>& x) { prContain(x); }
    template<class T> void pr(const vector<T>& x) { prContain(x); }
    template<class T> void pr(const set<T>& x) { prContain(x); }
    template<class T1, class T2> void pr(const map<T1,T2>& x) { prContain(x); }

    void ps() { pr("\n"); }
    template<class Arg> void ps(const Arg& first) {
        pr(first); ps(); // no space at end of line
    }
    template<class Arg, class... Args> void ps(const Arg& first, const Args&... rest) {
        pr(first," "); ps(rest...); // print w/ spaces
    }
}
using namespace output;
// @formatter:on

/* ============================ */

#include "grader.h"
#include "lang.h"

#define SZ 100

bool init = false;
ll lang[56][65536];
unordered_set<ll> words[56];
map<ll, unordered_set<int>> whatLanguagesWordAppearedIn;
unordered_set<int> whatLanguagesCharacterAppearedIn[65536];
unordered_map<ll, ll> endsWith[56];
pair<ll, ll> reallyEndsWith[56];
int mostFrequentChar[56][65536];
ii reallyMostFrequentChar[56];
ll langCt[56];
int globalCharCt[65536];
int space = 1;
ll H = 65536;
ll avgSimilarity[56];
ll someCount[56];
unordered_map<ll, set<int>> langPhrases[100];

int bessieMin = 2, bessieMax = 5;
 
ll getPhrase(int *E, int start, int len) {
    ll p = 0;
    for (int i = start; i < start + len; i++) {
        if (E[i] == space) return -1;
        p = (p * H + E[i]) % 4983483;
    }
    return p;
}

vl getWords(int *A, bool golden = false) {
    vl words;
    ll cur = 0;
    int wordLen = 0;
    F0R(i, SZ) {
        if (A[i] == space) {
            words.pb(cur);
            cur = 0;
            wordLen = 0;
        } else {
            wordLen++;
            cur = ((cur*H)+A[i])%MOD;
        }
    }
    return words;
}

int ct = 0;
ld getSimilarity(const int l, int *A) {
    int sameWordsCt = 0;
    trav(word, getWords(A)) {
        if (words[l].count(word) > 0) {
            sameWordsCt++;
        }
    }

    ld score = sameWordsCt*10;
    map<int, int> askdjflj;
    ii smth = { -1, -1 };
    set<int> tmp;
    F0R(i, SZ) {
        if (lang[l][A[i]] > 0) {
            if (whatLanguagesCharacterAppearedIn[A[i]].size() <= 1) {
                tmp.insert(A[i]);
            } else {
                score++;
            }
        }
        if (i + 2 < SZ && A[i+2] == space) {
            if (reallyEndsWith[l].pB == A[i]*H+A[i+1]) {
                score += 2;
            }
        }
        if (A[i] == space) continue;
        askdjflj[A[i]]++;
        MAX(smth, mp(askdjflj[A[i]], A[i]));
    }
    score += sz(tmp)*10;
    if (smth.pB == reallyMostFrequentChar[l].pB) {
        score++;
    }
    /*
    FOR(i, bessieMin, bessieMax) {
        F0R(j, SZ-i) {
            ll p = getPhrase(A, j, i);
            if (p == -1) continue;
            if (langPhrases[l][i].count(p) > 0) {
                score++;
            }
        }
    }
    */
    return score;
}

int failCt = 0;
int langTotCt[56];
void excerpt(int *E) {
    ct++;
    if (!init) {
        init = true;
        SET2D(lang, 0, 56, 65536);
        SET2D(mostFrequentChar, 0, 56, 65536);
        SET(langCt, 0, 56);
        SET(langTotCt, 0, 56);
        SET(globalCharCt, 0, 65536);
        F0R(i, 56) reallyEndsWith[i] = { -1, -1 };
        F0R(i, 56) reallyMostFrequentChar[i] = { -1, -1 };
    }

    F0R(i, SZ) {
        globalCharCt[E[i]]++;
        if (globalCharCt[E[i]] > globalCharCt[space]) space = E[i];
    }


    int guess = 0; ld similarity = 0;
    int phraseAdd[56]; SET(phraseAdd, 0, 56);
    FOR(i, bessieMin, bessieMax) {
        F0R(j, SZ-i) {
            ll p = getPhrase(E, j, i);
            if (langPhrases[i].count(p) == 0) continue;
			set<int> &s = langPhrases[i][p];
            trav(v, s) {
                phraseAdd[v]+=1;
            }
        }
    }
    F0R(i, 56) {
        ld s = getSimilarity(i, E) + phraseAdd[i];
        if (s > similarity) {
            guess = i;
            similarity = s;
        }
    }

    int ans = language(guess);
    if (ans == guess) langCt[ans]++;
    langTotCt[ans]++;
    // avgSimilarity[ans] = (avgSimilarity[ans] * (someCount[ans]/(someCount[ans]+1))+similarity/(someCount[ans]+1));
    someCount[ans]++;
    avgSimilarity[ans] += similarity;
    F0R(i, SZ) {
        lang[ans][E[i]]++;
        whatLanguagesCharacterAppearedIn[E[i]].insert(ans);
    }
    vl words2 = getWords(E);
    trav(w, words2) {
        words[ans].insert(w);
        whatLanguagesWordAppearedIn[w].insert(ans);
    }
    F0R(i, 98) {
        if (E[i+2] == space) {
            endsWith[ans][E[i]*H+E[i+1]]++;
            MAX(reallyEndsWith[ans], mp(endsWith[ans][E[i]*H+E[i+1]], E[i]*H+E[i+1]));
        }
    }
    F0R(i, 100) {
        if (E[i] == space) continue;
        mostFrequentChar[ans][E[i]]++;
        MAX(reallyMostFrequentChar[ans], mp(mostFrequentChar[ans][E[i]], E[i]));
    }
    FOR(i, bessieMin, bessieMax) {
        F0R(j, SZ-i) {
            ll p = getPhrase(E, j, i);
            if (p == -1) continue;
            langPhrases[i][p].insert(ans);
        }
    }

    /*
    if (ct == 10000) {
        F0R(i, 56) {
            psD("lang", i, "acc:", 100.0*langCt[i]/langTotCt[i]);
        }
    }
    */
}
