/*
Moovie Mooving
==============

Bessie is out at the movies.  Being mischievous as always, she has
decided to hide from Farmer John for L (1 <= L <= 100,000,000)
minutes, during which time she wants to watch movies continuously.
She has N (1 <= N <= 20) movies to choose from, each of which has a
certain duration and a set of showtimes during the day.  Bessie may
enter and exit a movie at any time during one if its showtimes, but
she does not want to ever visit the same movie twice, and she cannot
switch to another showtime of the same movie that overlaps the
current showtime.

Help Bessie by determining if it is possible for her to achieve her
goal of watching movies continuously from time 0 through time L.  If
it is, determine the minimum number of movies she needs to see to
achieve this goal (Bessie gets confused with plot lines if she watches
too many movies).

INPUT:

The first line of input contains N and L.

The next N lines each describe a movie.  They begin with its integer
duration, D (1 <= D <= L) and the number of showtimes, C (1 <= C <=
1000).  The remaining C integers on the same line are each in the
range 0..L, and give the starting time of one of the showings of the
movie.  Showtimes are distinct, in the range 0..L, and given in
increasing order.

SAMPLE INPUT:

4 100
50 3 15 30 55
40 2 0 65
30 2 20 90
20 1 0

OUTPUT:

A single integer indicating the minimum number of movies that Bessie
needs to see to achieve her goal.  If this is impossible output -1
instead.

SAMPLE OUTPUT:

3

SOLUTION NOTES:

Bessie should attend the first showing of the fourth movie from time 0
to time 20.  Then she watches the first showing of the first movie
from time 20 to time 65.  Finally she watches the last showing of the
second movie from time 65 to time 100.
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

int dp[(1 << 20)];
int movieStart[20][1000];
int movieDuration[20];
int movieCt[20];

int main() {
    ios_base::sync_with_stdio(false);
    int n, l; cin >> n >> l;
    for (int i = 0; i < n; i++) {
        int duration, ct; cin >> duration >> ct;
        for (int j = 0; j < ct; j++) {
            int start; cin >> start;
            movieStart[i][j] = start;
        }
        movieCt[i] = ct;
        movieDuration[i] = duration;
    }
    memset(dp, -1, sizeof dp);
    dp[0] = 0;
    int ans = INF;
    for (int i = 0; i < (1 << n); i++) {
        if (dp[i] == -1) continue;
        if (dp[i] >= l) {
            ans = min(ans, __builtin_popcount(i));
        }
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) continue;
            int idx = i | (1 << j);
            auto itr = lower_bound(movieStart[j], movieStart[j] + movieCt[j], dp[i]);
            if (*itr > dp[i]) itr--;
            if (itr < movieStart[j]) continue;
            dp[idx] = max(dp[idx], *itr + movieDuration[j]);
        }
    }
    if (ans == INF) {
        cout << "-1" << endl;
        return 0;
    }
    cout << ans << endl;
    return 0;
}
