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

int res[80][80], mf, f;
vi p;

void augment(int v, int minEdge) {
    if (v == 0) {
        f = minEdge; return;
    } else if (p[v] != -1) {
        augment(p[v], min(minEdge, res[p[v]][v]));
        res[p[v]][v] -= f;
        res[v][p[v]] += f;
    }
}

int main() {
    string line;
    while (getline(cin, line)) {
        int tot = 0;
        SET2D(res, 0, 80, 80);
        stringstream ss; ss << line;
        char app; ss >> app;
        int quantity; ss >> quantity;
        tot += quantity;
        res[0][app - 'A' + 1] = quantity;
        char computer;
        while (ss >> computer && computer != ';') {
            res[app - 'A' + 1][30 + computer-'0'] = INF;
        }
        while (getline(cin, line) && !line.empty()) {
            stringstream ss; ss << line;
            char app; ss >> app;
            int quantity; ss >> quantity;
            tot += quantity;
            res[0][app - 'A' + 1] = quantity;
            char computer;
            while (ss >> computer && computer != ';') {
                res[app - 'A' + 1][30 + computer-'0'] = INF;
            }
        }

        F0R(i, 10) res[30 + i][50] = 1;

        mf = 0;
        while (true) {
            f = 0;
            bool visited[80]; SET(visited, false, 80);
            visited[0] = true;
            queue<int> q; q.push(0);
            p.assign(80, -1);

            while (!q.empty()) {
                int u = q.front(); q.pop();
                if (u == 50) break;
                F0R(v, 80) {
                    if (res[u][v] > 0 && !visited[v]) {
                        visited[v] = true;
                        q.push(v);
                        p[v] = u;
                    }
                }
            }

            augment(50, INF);
            if (f == 0) break;
            mf += f;
        }

        char program[10]; SET(program, '_', 10);

        F0R(i, 10) {
            FOR(j, 1, 27) {
                if (res[30 + i][j] > 0) program[i] = 'A' + (j - 1);
            }
        }

        if (mf != tot) {
            cout << "!" << endl;
        } else {
            F0R(i, 10) {
                cout << program[i];
            }
            cout << endl;
        }
    }

    return 0;
}