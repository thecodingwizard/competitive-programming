/*
 * Basically editorial solution
 *
 * Construct 2*n nodes, if you are at a node i and you have just traveled the most beautiful path, and if you
 * are at node i and you have not traveled the most beautiful path. Each node has exactly one outgoing edge.
 *
 * Notice that you will eventually have to reach a cycle. Hence, determine the cycle length of P, and
 * then from each possible starting node use DP to simulate traveling from that node until you reach a cycle.
 */

#include "garden.h"
#include "gardenlib.h"

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
#define pb push_back
#define PI acos(-1.0)
// #define MOD (int)(2e+9+11)
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
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<ll> vl;

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
}

using namespace input;

namespace output {
    template<class T1, class T2> void pr(const pair<T1,T2>& x);
    template<class T, size_t SZ> void pr(const array<T,SZ>& x);
    template<class T> void pr(const vector<T>& x);
    template<class T> void pr(const set<T>& x);
    template<class T1, class T2> void pr(const map<T1,T2>& x);

    template<class T> void pr(const T& x) { cout << x; }
    template<class Arg, class... Args> void pr(const Arg& first, const Args&... rest) {
      pr(first); pr(rest...);
    }

    template<class T1, class T2> void pr(const pair<T1,T2>& x) {
      pr("{",x.pA,", ",x.pB,"}");
    }
    template<class T> void prContain(const T& x) {
      pr("{");
      bool fst = 1; for (const auto& a: x) pr(!fst?", ":"",a), fst = 0; // const needed for vector<bool>
      pr("}");
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

ii nextNode[150000][2];
vii children[150000];
int maxRoute[150000];
bool visited[150000][2];
bool inStack[150000][2][2];
int memo[150000][2][2];
int ct[400000][2];
int pp;

int dp(int n, int x, int d) {
  if (n == pp && x == d) return 0;
  if (memo[n][x][d] != -1) return memo[n][x][d];
  if (inStack[n][x][d]) return INF;
  inStack[n][x][d] = true;
  return memo[n][x][d] = dp(nextNode[n][x].pA, nextNode[n][x].pB, d) + 1;
}

void count_routes(int N, int M, int P, int R[][2], int Q, int G[])
{
  pp = P;
  SET(maxRoute, INF, N);
  F0R(i, M) {
    children[R[i][0]].pb(mp(R[i][1], i));
    children[R[i][1]].pb(mp(R[i][0], i));
    MIN(maxRoute[R[i][0]], i);
    MIN(maxRoute[R[i][1]], i);
  }
  F0R(i, N) F0R(j, 2) nextNode[i][j] = { -1, -1 };
  F0R(i, N) {
    F0R(j, 2) {
      if (children[i].size() == 0) continue;
      if (children[i].size() == 1 || j == 0) {
        nextNode[i][j] = mp(children[i][0].pA, maxRoute[children[i][0].pA] == children[i][0].pB);
      }
      if (children[i].size() > 1 && j == 1) {
        nextNode[i][j] = mp(children[i][1].pA, maxRoute[children[i][1].pA] == children[i][1].pB);
      }
    }
  }

  int p0Loop = 0;
  SET2D(visited, false, N, 2);
  ii nxt = { P, 0 };
  while (true) {
    if (nxt.pA == -1 || visited[nxt.pA][nxt.pB]) {
      if (nxt.pA != P) p0Loop = -1;
      break;
    }
    visited[nxt.pA][nxt.pB] = true;
    if (nextNode[nxt.pA][nxt.pB].pA == -1) nxt = { -1, -1 };
    else {
      nxt = nextNode[nxt.pA][nxt.pB];
      p0Loop++;
    }
  }
  int p1Loop = 0;
  SET2D(visited, false, N, 2);
  nxt = { P, 1 };
  while (true) {
    if (nxt.pA == -1 || visited[nxt.pA][nxt.pB]) {
      if (nxt.pA != P) p1Loop = -1;
      break;
    }
    visited[nxt.pA][nxt.pB] = true;
    if (nextNode[nxt.pA][nxt.pB].pA == -1) nxt = { -1, -1 };
    else {
      nxt = nextNode[nxt.pA][nxt.pB];
      p1Loop++;
    }
  }

  SET3D(memo, -1, 150000, 2, 2);
  SET3D(inStack, false, 150000, 2, 2);
  SET2D(ct, 0, 400000, 2);
  int qryAns[Q]; SET(qryAns, 0, Q);
  F0R(startNode, N) {
    F0R(k, 2) {
      int xx = dp(startNode, 0, k);
      if (xx < INF) {
        ct[xx][k]++;
        F0R(i, Q) {
          if (G[i] - xx >= 0) {
            if (k == 0) {
              if (p0Loop != -1 && (G[i] - xx) % p0Loop == 0) qryAns[i]++;
              else if (xx == G[i]) qryAns[i]++;
            } else {
              if (p1Loop != -1 && (G[i] - xx) % p1Loop == 0) qryAns[i]++;
              else if (xx == G[i]) qryAns[i]++;
            }
          }
        }
      }
    }
  }

  F0R(i, Q) {
    answer(qryAns[i]);
  }
}


