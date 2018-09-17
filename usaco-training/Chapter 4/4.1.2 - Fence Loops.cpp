/*
ID: nathan.18
TASK: fence6
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
#define READGRID(arr, dim) F0R(i, dim) F0R(j, dim) cin >> arr[i][j];
typedef pair<int, int> ii;
typedef pair<ii, int> iii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vl;

bool cLeft[110][110], cRight[110][110];

int main() {
    freopen("fence6.in", "r", stdin);
    freopen("fence6.out", "w", stdout);

    int n; cin >> n;
    int length[110];
    SET2D(cLeft, false, 110, 110); SET2D(cRight, false, 110, 110);
    F0R(i, n) {
        int s, l, n2, n3; cin >> s >> l >> n2 >> n3;
        length[s] = l;
        F0R(j, n2) {
            int x; cin >> x;
            cLeft[s][x] = true;
        }
        F0R(j, n3) {
            int x; cin >> x;
            cRight[s][x] = true;
        }
    }

    int best = INF;
    F0R1(i, n) {
        priority_queue<pair<int, ii>, vector<pair<int, ii>>, greater<pair<int, ii>>> pq;
        int dist[110][2]; SET2D(dist, INF, 110, 2);
        pq.push(mp(0, mp(i, 1)));
        dist[i][1] = 0;
        while (!pq.empty()) {
            pair<int, ii> next = pq.top(); pq.pop();
            if (next.pA > dist[next.pB.pA][next.pB.pB]) continue;
            if ((next.pB.pB && cRight[next.pB.pA][i]) || (!next.pB.pB && cLeft[next.pB.pA][i])) {
                best = min(best, next.pA + length[i]);
                break;
            }
            if (next.pB.pB) {
                // connected right
                F0R1(j, n) {
                    if (!cRight[next.pB.pA][j]) continue;
                    bool connRight = cRight[j][next.pB.pA];
                    if (dist[j][!connRight] > dist[next.pB.pA][next.pB.pB] + length[j]) {
                        dist[j][!connRight] = dist[next.pB.pA][next.pB.pB] + length[j];
                        pq.push(mp(dist[j][!connRight], mp(j, !connRight)));
                    }
                }
            } else {
                // connected left
                F0R1(j, n) {
                    if (!cLeft[next.pB.pA][j]) continue;
                    bool connRight = cRight[j][next.pB.pA];
                    if (dist[j][!connRight] > dist[next.pB.pA][next.pB.pB] + length[j]) {
                        dist[j][!connRight] = dist[next.pB.pA][next.pB.pB] + length[j];
                        pq.push(mp(dist[j][!connRight], mp(j, !connRight)));
                    }
                }
            }
        }
    }
    cout << best << endl;

    return 0;
}