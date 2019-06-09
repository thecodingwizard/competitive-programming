/*
 * Let us assume we are trying to answer a query on a number, Q, using integers A_1, A_2, ... A_n.
 * We can say that:
 * Q = A_1*k + n
 * where k >= 0 and n >= 0.
 *
 * Let's take this equation mod A_1:
 * Q mod A_1 = n mod A_1
 *
 * Now we have to determine whether it is possible to form a number n where n mod A_1 = Q mod A_1 using our numbers,
 * trying to minimize n.
 * If we can't, then Q cannot be formed using our numbers.
 * If we are able to form a number n, then there are two cases:
 * n <= Q: We can form Q using our numbers. We just have to repeatedly add A_1 to n until we reach Q, since (Q - n) mod A_1 = 0.
 * n > Q: We can't form Q using our numbers. We would have to *subtract* A_1 from n repeatedly to reach Q, but we can't subtract numbers.
 *
 * Now we have to answer a question: Given a number y < A_1, find a number n that satisfies the following:
 * 1. We can form n using the numbers we have (n is in the set A')
 * 2. n is as small as possible
 * 3. n mod A_1 = y
 *
 * We can do this using Dijkstra's. Create nodes 0...A_1 - 1. The distance to node i represents the smallest
 * number n where n mod A_1 = i. So dist[0] = 0.
 *
 * There is an edge between nodes i and j if there exists A_x s.t.
 * (i + A_x) mod A_1 = j
 * The cost of this edge is A_x.
 *
 * We can answer a query as follows:
 * 1. Find the smallest n s.t. n mod A_1 = Q mod A_1.
 * 2. If n <= S, TAK
 * 3. if n > S, NIE
 *
 * Complexity:
 * m = max value of A (50,000)
 * n = # of elements in A
 * k = # of queries (10,000)
 * O(mn log m + k)
 *
 * Note that this solution will only get 90 points, it will TLE on one test set. We can get 100
 * points by optimizing it a little bit. Since Q <= 1,000,000, we can stop running dijkstra's
 * once the cost of a mod exceeds 1 billion.
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

int main() {
    setupIO();

    int n; cin >> n;
    int A[n]; F0R(i, n) cin >> A[i];
    sort(A, A+n);

    int A0 = A[0];

    int dist[A0]; SET(dist, INF, A0);
    dist[0] = 0;
    min_heap<pair<int, int>> pq; pq.push(mp(0, 0));
    while (!pq.empty()) {
        pair<int, int> u = pq.top(); pq.pop();
        if (u.pA > dist[u.pB]) continue;
        F0R(i, n) {
            int v = (u.pB + A[i]) % A0;
            int v_cost = u.pA + A[i];
            if (dist[v] > v_cost) {
                dist[v] = v_cost;
                pq.push(mp(v_cost, v));
            }
        }
    }

    int k; cin >> k;
    F0R(i, k) {
        int q; cin >> q;
        int cost = dist[q % A[0]];
        if (cost > q) {
            cout << "NIE" << endl;
        } else {
            cout << "TAK" << endl;
        }
    }

    return 0;
}
