/*
 * Dijkstra APSP, gets TLE on last test case. Correct solution uses DP
 *
 * 90/100
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

int A[2000][200];
int rowTraverse[2000];
// dist from one cell to its right/left column, assuming start is free
int distToRight[2000][200];
int distToLeft[2000][200];
// Dist from one place to another, assuming start location is free
int dist[2*2000][2*2000]; // 0...r-1 is left nodes, r...2*r-1 is right nodes

int main() {
    setupIO();

    int r, c; cin >> r >> c;
    F0R(i, r) F0R(j, c) cin >> A[i][j];
    F0R(i, r) {
        rowTraverse[i] = 0;
        FOR(j, 1, c - 1) {
            rowTraverse[i] += A[i][j];
        }
    }
    F0R(i, r) {
        distToRight[i][c-1] = 0;
        F0Rd(j, c-1) {
            distToRight[i][j] = distToRight[i][j + 1] + A[i][j+1];
        }
        distToLeft[i][0] = 0;
        FOR(j, 1, c) {
            distToLeft[i][j] = distToLeft[i][j-1] + A[i][j-1];
        }
    }

    // Step 1: Dijkstra APSP
    SET2D(dist, INF, 2*r, 2*r);
    F0R(start, 2*r) {
        dist[start][start] = 0;
        min_heap<ii> pq;
        pq.push(mp(0, start));
        while (!pq.empty()) {
            ii u = pq.top();
            pq.pop();
            if (dist[start][u.pB] < u.pA) continue;
            // up, down, cross
            if (u.pB != 0 && u.pB != r) {
                int v = u.pB - 1;
                int newDist = dist[start][u.pB] + A[v % r][v >= r ? c - 1 : 0];
                if (dist[start][v] > newDist) {
                    dist[start][v] = newDist;
                    pq.push(mp(newDist, v));
                }
            }

            if (u.pB != r - 1 && u.pB != 2 * r - 1) {
                int v = u.pB + 1;
                int newDist = dist[start][u.pB] + A[v % r][v >= r ? c - 1 : 0];
                if (dist[start][v] > newDist) {
                    dist[start][v] = newDist;
                    pq.push(mp(newDist, v));
                }
            }

            int v = u.pB < r ? u.pB + r : u.pB - r;
            int newDist = dist[start][u.pB] + rowTraverse[u.pB % r] + A[v % r][v >= r ? c - 1 : 0];
            if (dist[start][v] > newDist) {
                dist[start][v] = newDist;
                pq.push(mp(newDist, v));
            }
        }
    }


    int d; cin >> d;
    ii curLoc = { 0, 0 };
    ll ans = A[0][0];
    F0R(i, d) {
        int a, b; cin >> a >> b;
        --a; --b;
        // assume start location is always free.
        int leftToRight = dist[curLoc.pA][a+r];
        int leftToLeft = dist[curLoc.pA][a];
        int rightToLeft = dist[curLoc.pA+r][a];
        int rightToRight = dist[curLoc.pA+r][a+r];
        int costGoLeft = distToLeft[curLoc.pA][curLoc.pB];
        int costGoRight = distToRight[curLoc.pA][curLoc.pB];
        int costFromLeft = distToLeft[a][b] + A[a][b] - A[a][0];
        int costFromRight = distToRight[a][b] + A[a][b] - A[a][c-1];
        int cheapest = INF;
        // left -> left
        MIN(cheapest, leftToLeft + costGoLeft + costFromLeft);
        // left -> right
        MIN(cheapest, leftToRight + costGoLeft + costFromRight);
        // right -> left
        MIN(cheapest, rightToLeft + costGoRight + costFromLeft);
        // right -> right
        MIN(cheapest, rightToRight + costGoRight + costFromRight);
        // Pizza is in same line?
        if (curLoc.pA == a) {
            if (curLoc.pB > b) {
                MIN(cheapest, distToLeft[a][curLoc.pB] - distToLeft[a][b]);
            } else {
                MIN(cheapest, distToRight[a][curLoc.pB] - distToRight[a][b]);
            }
        }
        ans += cheapest;
        curLoc = { a, b };
    }
    cout << ans << endl;

    return 0;
}