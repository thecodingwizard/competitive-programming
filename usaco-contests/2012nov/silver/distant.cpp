/* Distant Pastures */

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

using namespace std;

#define INF 1000000000
#define LL_INF 4523372036854775807
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define PI acos(-1.0)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

ofstream fout("distant.out");
ifstream fin("distant.in");


int main() {
    int n, sameCost, diffCost; fin >> n >> sameCost >> diffCost;
    bool isOpen[n][n];
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
            char c; fin >> c;
            isOpen[i][j] = c == '(';
        }
    long long dist[n][n];
    int dx[4] = {0, -1, 0, 1};
    int dy[4] = {1, 0, -1, 0};
    long long longest = 0;
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) for (int l = 0; l < n; l++) dist[k][l] = LL_INF;
            dist[i][j] = 0;
            priority_queue<pair<long long, ii>, vector<pair<long long, ii>>, greater<pair<long long, ii>>> pq;
            pq.push(mp(0, mp(i, j)));
            while (!pq.empty()) {
                pair<long long, ii> next = pq.top(); pq.pop();
                if (dist[next.B.A][next.B.B] < next.A) continue;
                for (int x = 0; x < 4; x++) {
                    int a = next.B.A + dy[x], b = next.B.B + dx[x];
                    if (a < 0 || a >= n || b < 0 || b >= n) continue;
                    long long altCost = next.A + (isOpen[next.B.A][next.B.B] == isOpen[a][b] ? sameCost : diffCost);
                    if (dist[a][b] <= altCost) continue;
                    dist[a][b] = altCost;
                    pq.push(mp(dist[a][b], mp(a, b)));
                }
            }
            for (int k = 0; k < n; k++) for (int l = 0; l < n; l++) longest = max(longest, dist[k][l]);
        }
    fout << longest << endl;
    return 0;
}
