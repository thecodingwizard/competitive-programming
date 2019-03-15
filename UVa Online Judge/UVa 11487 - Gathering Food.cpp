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

int n;
char A[10][10];
ii loc[30];

int main() {
    int caseNum = 1;
    while (cin >> n && n) {
        int biggest = -1;
        F0R(i, n) {
            F0R(j, n) {
                cin >> A[i][j];
                if (A[i][j] != '.' && A[i][j] != '#') {
                    A[i][j] -= 'A';
                    loc[A[i][j]] = { i, j };
                    MAX(biggest, (int)A[i][j]);
                }
            }
        }

        cout << "Case " << caseNum++ << ": ";


        int totDist = 0;
        int curWays = 1;
        bool bad = false;
        F0R1(i, biggest) {
            ii start = loc[i - 1], end = loc[i];
            int dist[10][10]; SET2D(dist, INF, 10, 10);
            dist[start.pA][start.pB] = 0;
            int ways[10][10]; SET2D(ways, 0, 10, 10);
            ways[start.pA][start.pB] = 1;
            queue<ii> q;
            q.push(start);
            bool good = false;
            while (!q.empty()) {
                ii front = q.front(); q.pop();
                if (front == end) {
                    totDist += dist[front.pA][front.pB];
                    curWays = (curWays * ways[front.pA][front.pB]) % 20437;
                    good = true;
                    break;
                }
                int dx[4] = { -1, 0, 1, 0 };
                int dy[4] = { 0, 1, 0, -1 };
                F0R(j, 4) {
                    ii next = { front.pA + dx[j], front.pB + dy[j] };
                    if (next.pA < 0 || next.pA >= n || next.pB < 0 || next.pB >= n || A[next.pA][next.pB] == '#') continue;
                    if (A[next.pA][next.pB] > i && A[next.pA][next.pB] != '.') continue;
                    if (dist[next.pA][next.pB] == INF) {
                        ways[next.pA][next.pB] += ways[front.pA][front.pB];
                        dist[next.pA][next.pB] = dist[front.pA][front.pB] + 1;
                        q.push(next);
                    } else if (dist[next.pA][next.pB] == dist[front.pA][front.pB] + 1) {
                        ways[next.pA][next.pB] += ways[front.pA][front.pB];
                    }
                }
            }
            if (!good) {
                bad = true;
                break;
            }
        }


        if (bad) {
            cout << "Impossible";
        } else {
            cout << totDist << " " << curWays;
        }
        cout << endl;
    }

    return 0;
}
