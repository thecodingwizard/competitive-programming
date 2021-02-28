/*
 * We want to construct a 2d boolean array that tells us if the ship
 * can be at position (x, y); once we have this array we can just bfs.
 *
 * Be careful when BFS'ing: In the case of a cross shape, you need to be
 * careful with how you check whether the shape is "in" or "out" of the map.
 * You can't just treat the boat like a rectangle.
 *
 * Process each column from left to right.
 * For each column, loop through rows from top to bottom. For each cell, find the
 * two rocks on the left and right side. Given the space between the two rocks,
 * you can calculate a range of cells that will be blocked due to
 * these two rocks in this column.
 */

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define ii pair<int, int>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define inf 1000000010

int n;
vector<int> rocks[2000];
vector<int> upperBoat, lowerBoat;
bool legal[4000][6000];
int bad[4001];
int dist[4001][6000]; 

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    char A[n][n];
    bool mustFlip = false;
    int axis = -1;
    F0R(i, n) {
        int boatStart = -1, boatEnd = -1;
        F0R(j, n) {
            cin >> A[i][j];
            if (A[i][j] == 'r') {
                if (boatStart == -1) boatStart = j;
                boatEnd = j;
            }
        }
        if (boatStart != -1) {
            if (axis == -1) axis = (boatEnd + boatStart)/2;
            if (axis != (boatEnd + boatStart)/2) mustFlip = 1;
        }
    }
    if (mustFlip) {
        F0R(i, n) {
            FOR(j, i+1, n) {
                int tmp = A[i][j];
                A[i][j] = A[j][i];
                A[j][i] = tmp;
            }
        }
    }

    axis = -1;
    vector<int> boatLengths;
    int maxBoatLen = 0;
    ii start;
    F0R(i, n) {
        rocks[i].pb(-inf);
        int boatStart = -1, boatEnd = -1;
        F0R(j, n) {
            char c = A[i][j];
            if (c == 'X') {
                rocks[i].pb(j);
            } else if (c == 'r') {
                if (boatStart == -1) boatStart = j;
                boatEnd = j;
            }
        }
        if (boatStart != -1) {
            if (axis == -1) {
                start = mp(i, (boatStart+boatEnd)/2);
            }
            if (axis != -1) assert(axis == (boatStart+boatEnd)/2);
            axis = (boatStart + boatEnd)/2;
            boatLengths.pb((boatEnd-boatStart)/2);
            maxBoatLen = max(maxBoatLen, boatLengths.back());
        }
        rocks[i].pb(inf);
    }
    bool lower = false;
    for (auto x : boatLengths) {
        if (x < maxBoatLen && !lower) upperBoat.pb(x);
        else {
            lower = true;
            lowerBoat.pb(x);
        }
    }

    reverse(all(lowerBoat));
    for (int col = -n; col < 2*n; col++) {
        F0R(i, 4000) bad[i] = 0;
        F0R(row, n) {
            int rht = *lower_bound(all(rocks[row]), col) - col - 1;
            int lft = col - *(--upper_bound(all(rocks[row]), col)) - 1;
            int maxSz = min(rht, lft);
            
            int startIdx = upper_bound(all(upperBoat), maxSz) - upperBoat.begin();
            int endIdx = sz(lowerBoat) - (upper_bound(all(lowerBoat), maxSz) - lowerBoat.begin()) + sz(upperBoat) - 1;
            //cout << row << " " << col << " --> " << startIdx << " to " << endIdx << endl;

            if (endIdx >= startIdx) {
                bad[row - endIdx + n]++;
                bad[row - startIdx + 1 + n]--;
            }
        }
        int ct = 0;
        F0R(row, 2*n) {
            ct += bad[row];
            if (ct <= 0) {
                legal[row][col+n] = 1;
            }
        }
    }

    //for(int i = 0; i < n; i++) { F0R(j, n) cout << legal[i+n][j+n]; cout << endl; }
    
    F0R(i, 2*n) F0R(j, 3*n) dist[i][j] = inf;
    dist[n+start.f][n+start.s] = 0;
    queue<ii> q; q.push(mp(n+start.f, n+start.s));
    int dx[4] = { -1, 0, 1, 0 };
    int dy[4] = { 0, 1, 0, -1 };
    reverse(all(lowerBoat));
    while (!q.empty()) {
        ii u = q.front(); q.pop();
        F0R(i, 4) {
            ii v = mp(u.f + dx[i], u.s + dy[i]);
            int tgtBoatLen = maxBoatLen;
            if (v.f-n < -sz(upperBoat)) {
                tgtBoatLen = lowerBoat[n-v.f-sz(upperBoat)];
            }
            if (v.f+sz(upperBoat)>=2*n) {
                tgtBoatLen = upperBoat[2*n-v.f-1];
            }
            bool horizGood = v.s < n-tgtBoatLen || v.s >= 2*n+tgtBoatLen;
            if (v.f >= 2*n || v.f <= n-(sz(upperBoat)+sz(lowerBoat)) || horizGood) {
                cout << dist[u.f][u.s]+1 << endl;
                return 0;
            }
            if (!legal[v.f][v.s] || dist[v.f][v.s] != inf) continue;
            dist[v.f][v.s] = dist[u.f][u.s]+1;
            q.push(v);
        }
    }

    cout << "NIE" << endl;

    return 0;
}
