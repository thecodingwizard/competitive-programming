/*
 * Note that R has a period of 7. Send *random* numbers until you have a collision. When you
 * get a collision, solve for one of the R values until you have solved for all 7 of them.
 * It should not take too many queries. Make sure to store the queries you send in this step.
 *
 * Then figure out all the M values you can from the queries in the first step. For the remaining
 * M values, send one query to fill in one M value.
 *
 * Using random numbers is very important.
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

#include "decrypt.h"

void decrypt() {
    int R[7]; SET(R, -1, 7);
    int M[256]; SET(M, -1, 256);
    map<int, ii> seen;
    int magic[7] = { 1, 2, 4, 1^2, 2^4, 1^2^4, 1^4 };
    set<int> unknownR; F0R(i, 7) unknownR.insert(i);
    vii spentQueries[7];
    while (true) {
        if (unknownR.size() <= 0) break;
        F0R(j, 7) {
            int x = rand() % 256;
            int resp = query(x);
            spentQueries[j].pb(mp(x, resp));
            if (seen.count(resp)) {
                int k = seen[resp].pA;
                for (int l = 0; l < 7; l++) {
                    if (unknownR.count(l) == 0) continue;
                    if (magic[l] == (magic[k]^magic[j])) {
                        R[l] = (x ^ seen[resp].pB);
                        unknownR.erase(l);
                    }
                }
            } else {
                seen[resp] = mp(j, x);
            }
        }
    }
    F0R(i, 7) {
        for (ii q : spentQueries[i]) {
            M[R[i]^q.pA] = q.pB;
        }
    }
    vector<int> need;
    F0R(i, 256) if (M[i] == -1) need.pb(i);
    int kCtr = 0;
    for (int x : need) {
        M[x] = query(R[kCtr++]^x);
        if (kCtr == 7) kCtr -= 7;
    }
    solution(R,M);
    return;
}

//int main() {
//    setupIO();
//    return 0;
//}