/*
ID: nathan.18
TASK: shopping
LANG: C++11
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
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
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
typedef pair<int, int> ii;
typedef pair<ii, int> iii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vl;


typedef pair<int, array<int, 5>> state;

int main() {
    freopen("shopping.in", "r", stdin);
    freopen("shopping.out", "w", stdout);

    int s; cin >> s;
    pair<int, vii> deals[s];
    F0R(i, s) {
        int n; cin >> n;
        F0R(j, n) {
            int c, k; cin >> c >> k;
            deals[i].pB.pb(mp(c, k));
        }
        cin >> deals[i].pA;
    }
    int quantity[5];
    int product[5];
    int price[5];
    map<int, int> codes;
    SET(quantity, 0, 5);
    SET(product, 0, 5);
    SET(price, 0, 5);
    int n; cin >> n;
    F0R(i, n) {
        cin >> product[i] >> quantity[i] >> price[i];
        codes.insert(mp(product[i], i));
    }
    int dist[6][6][6][6][6];
    F0R(i, 6) F0R(j, 6) F0R(k, 6) F0R(l, 6) F0R(m, 6) dist[i][j][k][l][m] = INF;
    dist[0][0][0][0][0] = 0;
    priority_queue<state, vector<state>, greater<state>> pq;
    array<int, 5> init;
    pq.push(mp(0, init));
    while (!pq.empty()) {
        state next = pq.top(); pq.pop();
        int a = next.pB[0], b = next.pB[1], c = next.pB[2], d = next.pB[3], e = next.pB[4];
        if (dist[a][b][c][d][e] < next.pA) continue;
        int ct[5] = { a, b, c, d, e };
        F0R(i, n) {
            if (ct[i] + 1 <= quantity[i]) {
                state toInsert = next;
                toInsert.pA+=price[i];
                toInsert.pB[i]++;
                auto x = toInsert.pB;
                if (dist[x[0]][x[1]][x[2]][x[3]][x[4]] <= toInsert.pA) continue;
                dist[x[0]][x[1]][x[2]][x[3]][x[4]] = toInsert.pA;
                pq.push(toInsert);
            }
        }
        F0R(i, s) {
            state toInsert = next;
            toInsert.pA += deals[i].pA;
            bool good = true;
            for (ii item : deals[i].pB) {
                toInsert.pB[codes[item.pA]] += item.pB;
                if (toInsert.pB[codes[item.pA]] > quantity[codes[item.pA]]) {
                    good = false;
                }
            }
            if (!good) continue;
            auto x = toInsert.pB;
            if (dist[x[0]][x[1]][x[2]][x[3]][x[4]] <= toInsert.pA) continue;
            dist[x[0]][x[1]][x[2]][x[3]][x[4]] = toInsert.pA;
            pq.push(toInsert);
        }
    }
    cout << dist[quantity[0]][quantity[1]][quantity[2]][quantity[3]][quantity[4]] << endl;

    return 0;
}
