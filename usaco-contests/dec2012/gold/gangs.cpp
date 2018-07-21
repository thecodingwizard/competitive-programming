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
#include <math.h>
#include <assert.h>

using namespace std;

#define INF 1000000000
#define LL_INF 0xfffffffffffffffLL
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define PI acos(-1.0)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

vi cowCount;
int n, m;

int curCowsOnField = 0, curGang = -1;
int send(int startGang) {
    priority_queue<ii, vii> pq;
    for (int i = 2; i <= m; i++) {
        if (i == startGang && cowCount[i] == 1) continue;
        if (cowCount[i] == 0) continue;
        pq.push(mp((i == startGang ? cowCount[i] - 1 : cowCount[i]), i));
    }
    int cowsOnField = 1, gang = startGang;
    if (curGang == startGang) {
        cowsOnField += curCowsOnField;
    } else {
        if (curCowsOnField == cowsOnField) {
            cowsOnField = 0;
        } else if (curCowsOnField > cowsOnField) {
            cowsOnField = curCowsOnField - cowsOnField;
            gang = curGang;
        } else {
            cowsOnField = cowsOnField - curCowsOnField;
        }
    }
    while (!pq.empty()) {
        ii cow = pq.top(); pq.pop();
        if (cow.B == gang) {
            cowsOnField += cow.A;
            continue;
        }
        if (cowsOnField == 0) {
            cowsOnField = cow.A;
            gang = cow.B;
        } else {
            cowsOnField--;
            if (cow.A > 1) pq.push(mp(cow.A - 1, cow.B));
        }
    }
    if (startGang == 1) return cowCount[1] - cowsOnField - 1;
    return cowCount[1] - cowsOnField;
}

int main() {
    freopen("gangs.in", "r", stdin);
    freopen("gangs.out", "w", stdout);
    
    cin >> n >> m;
    cowCount.resize(m+10);
    for (int i = 1; i <= m; i++) {
        cin >> cowCount[i];
    }
    vi order;
    int answer = -INF;
    while (order.size() < n) {
        int best = -INF, bestGang;
        for (int i = 1; i <= m; i++) {
            if (cowCount[i] == 0) continue;
            int left = send(i);
            if (best < left) {
                best = left;
                bestGang = i;
            }
        }
        int cowsOnField = 1, gang = bestGang;
        if (curGang == bestGang) {
            cowsOnField += curCowsOnField;
        } else {
            if (curCowsOnField == cowsOnField) {
                cowsOnField = 0;
            } else if (curCowsOnField > cowsOnField) {
                cowsOnField = curCowsOnField - cowsOnField;
                gang = curGang;
            } else {
                cowsOnField = cowsOnField - curCowsOnField;
                gang = bestGang;
            }
        }
        curCowsOnField = cowsOnField;
        curGang = gang;
        cowCount[bestGang]--;
        order.push_back(bestGang);
        if (answer == -INF) answer = best;
    }
    if (answer <= 0) {
        cout << "NO" << endl;
        return 0;
    }
    cout << "YES" << endl << answer << endl;
    for (int cow : order) cout << cow << endl;
    return 0;
}
