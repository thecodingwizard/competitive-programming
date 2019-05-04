/*
City Horizon
============

Farmer John has taken his cows on a trip to the city! As the sun
sets, the cows gaze at the city horizon and observe the beautiful
silhouettes formed by the rectangular buildings.

The entire horizon is represented by a number line with N (1 <= N
<= 40,000) buildings. Building i's silhouette has a base that spans
locations A_i through B_i along the horizon (1 <= A_i < B_i <=
1,000,000,000) and has height H_i (1 <= H_i <= 1,000,000,000).
Determine the area, in square units, of the aggregate silhouette
formed by all N buildings.

PROBLEM NAME: horizon

INPUT FORMAT:

* Line 1: A single integer: N

* Lines 2..N+1: Input line i+1 describes building i with three
        space-separated integers: A_i, B_i, and H_i

SAMPLE INPUT:

4
2 5 1
9 10 4
6 8 2
4 6 3


OUTPUT FORMAT:

* Line 1: The total area, in square units, of the silhouettes formed
        by all N buildings

SAMPLE OUTPUT:

16

OUTPUT DETAILS:

The first building overlaps with the fourth building for an area of 1
square unit, so the total area is just 3*1 + 1*4 + 2*2 + 2*3 - 1 = 16.
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
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

struct Line {
    long long height, x; bool end;
    Line(int _height, int _x, bool _end) : height(_height), x(_x), end(_end) {}
    bool operator < (Line other) const {
        return other.x == x ? height < other.height : x < other.x;
    }
};

int main() {
    int n;
    cin >> n;
    long long a, b, h;
    vector<Line> lines;
    for (int i = 0; i < n; i++) {
        cin >> a >> b >> h;
        lines.emplace_back(h, a, false);
        lines.emplace_back(h, b, true);
    }
    sort(lines.begin(), lines.end());
    multiset<int> heights;
    int pos = 0;
    long long ans = 0;
    for (Line l : lines) {
        int height = !heights.empty() ? *heights.rbegin() : 0;
        ans += height * (l.x - pos);
        pos = l.x;
        if (l.end) {
            auto itr = heights.find(l.height);
            heights.erase(itr);
        } else {
            heights.insert(l.height);
        }
    }
    cout << ans << endl;
    return 0;
}
