/*
ID: nathan.18
TASK: charrec
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

int dict[27][20];
int memo[1300][80], n;
int A[1200];
ii ans[1200][30];

void readdict() {
    ifstream dictfile("font.in");
    int n; dictfile >> n;
    F0R(i, 27) {
        F0R(j, 20) {
            int val = 0;
            F0R(k, 20) {
                char c; dictfile >> c;
                if (c == '1') val |= (1 << k);
            }
            dict[i][j] = val;
        }
    }
}

int dp(int line, int location) {
    if (line == n) return 0;
    if (memo[line][location] != -1) return memo[line][location];
    int finalAns = INF, choice = -1, res;

    // case 1: 19 lines
    if (line + 19 <= n) {
        int bestDiff = INF, bestIdx = -1;
        int op = dp(line + 19, location + 1);
        if (op != INF) {
            F0R(i, 27) {
                F0R(ignore, 20) {
                    int ct = 0;
                    F0R(row, 20) {
                        if (row == ignore) continue;
                        int a = A[line + row - (ignore < row ? 1 : 0)], b = dict[i][row];
                        ct += __builtin_popcount(a ^ b);
                        if (ct >= bestDiff) break;
                    }
                    if (ct < bestDiff) {
                        bestDiff = ct;
                        bestIdx = i;
                    }
                }
            }
            if (op != INF && op + bestDiff < finalAns) {
                finalAns = op + bestDiff;
                choice = 0;
                res = bestIdx;
            }
        }
    }

    // case 2: 20 lines
    if (line + 20 <= n) {
        int bestDiff = INF, bestIdx = -1;
        int op = dp(line + 20, location + 1);
        if (op != INF) {
            F0R(i, 27) {
                int ct = 0;
                F0R(row, 20) {
                    int a = A[line + row], b = dict[i][row];
                    ct += __builtin_popcount(a ^ b);
                    if (ct >= bestDiff) break;
                }
                if (ct < bestDiff) {
                    bestDiff = ct;
                    bestIdx = i;
                }
            }
            if (op != INF && op + bestDiff < finalAns) {
                finalAns = op + bestDiff;
                choice = 1;
                res = bestIdx;
            }
        }
    }

    // case 3: 21 lines
    if (line + 21 <= n) {
        int bestDiff = INF, bestIdx = -1;
        int op = dp(line + 21, location + 1);
        if (op != INF) {
            F0R(i, 27) {
                F0R(ignore, 21) {
                    int ct = 0;
                    F0R(row, 20) {
                        int a = A[line + row + (ignore <= row ? 1 : 0)], b = dict[i][row];
                        ct += __builtin_popcount(a ^ b);
                        if (ct >= bestDiff) break;
                    }
                    if (ct < bestDiff) {
                        bestDiff = ct;
                        bestIdx = i;
                    }
                }
            }
            if (op + bestDiff < finalAns) {
                finalAns = op + bestDiff;
                choice = 2;
                res = bestIdx;
            }
        }
    }

    if (choice == -1) return memo[line][location] = INF;
    ans[line][location] = { choice, res };

    return memo[line][location] = finalAns;
}

int main() {
    setupIO("charrec");

    readdict();

    cin >> n;
    F0R(i, n) {
        int val = 0;
        F0R(j, 20) {
            char c; cin >> c;
            if (c == '1') {
                val |= (1 << j);
            }
        }
        A[i] = val;
    }

    SET2D(memo, -1, 1300, 80);
    dp(0, 0);

    int cur = 0, loc = 0;
    string toPrint;
    while (cur != n) {
        if (ans[cur][loc].pB == 0) toPrint += ' ';
        else toPrint += ('a' + ans[cur][loc].pB - 1);
        cur += ans[cur][loc].pA + 19;
        loc++;
    }
    cout << toPrint << endl;

    return 0;
}