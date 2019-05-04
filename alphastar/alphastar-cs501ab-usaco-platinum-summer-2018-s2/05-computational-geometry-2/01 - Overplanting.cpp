/*
Overplanting
============

Farmer John has purchased a new machine that is capable of planting grass
within any rectangular region of his farm that is "axially aligned" (i.e.,
with vertical and horizontal sides).  Unfortunately, the machine
malfunctions one day and plants grass in not one, but N (1 <= N <= 1000)
different rectangular regions, some of which may even overlap.

Given the rectangular regions planted with grass, please help FJ compute
the total area in his farm that is now covered with grass.

PROBLEM NAME: planting

INPUT FORMAT:

* Line 1: The integer N.

* Lines 2..1+N: Each line contains four space-separated integers x1 y1
        x2 y2 specifying a rectangular region with upper-left corner
        (x1,y1) and lower-right corner (x2,y2).  All coordinates are
        in the range -10^8...10^8.

SAMPLE INPUT:

2
0 5 4 1
2 4 6 2

OUTPUT FORMAT:

* Line 1: The total area covered by grass.  Note that this could be
        too large to fit into a 32-bit integer.

SAMPLE OUTPUT:

20
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
#include <assert.h>

using namespace std;

#define INF 1000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define mp make_pair
#define A first
#define B second
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

struct Rect {
    int startX, startY, endX, endY;
};
struct Line {
    long long x;
    int rectID;
    bool endOfRect;
    Line(long long _x, int _rectID, bool _endOfRect) : x(_x), rectID(_rectID), endOfRect(_endOfRect) {}

    bool operator < (Line other) const {
        return x < other.x;
    }
};
struct VertLine {
    long long y;
    int rectID;
    bool end;

    VertLine(long long _y, int _rectID, bool _end) : y(_y), rectID(_rectID), end(_end) {}

    bool operator == (VertLine other) const {
        return other.y == y && other.rectID == rectID && end == other.end;
    }

    bool operator < (VertLine other) const {
        if (other.y == y) return other.rectID > rectID;
        return y > other.y;
    }
};

bool howToSort(Line a, Line b) {
    return a.x < b.x;
}

int main() {
    int n;
    cin >> n;
    Rect rects[n];
    vector<Line> lines;
    for (int i = 0; i < n; i++) {
        cin >> rects[i].startX >> rects[i].startY >> rects[i].endX >> rects[i].endY;
        lines.emplace_back(rects[i].startX, i, false);
        lines.emplace_back(rects[i].endX, i, true);
    }

    sort(lines.begin(), lines.end(), howToSort);

    set<VertLine> vertLines;
    long long distance = 0;
    long long area = 0;
    for (int i = 0; i < lines.size(); i++) {
        Line line = lines[i];

        long long height = 0; int numOfRects = 0; long long curY = -1;
        for (VertLine vertLine : vertLines) {
            if (vertLine.end) {
                numOfRects--;
                if (numOfRects <= 0) {
                    height += curY - vertLine.y;
                    curY = -1;
                    numOfRects = 0;
                }
            } else {
                numOfRects++;
                if (curY == -1) curY = vertLine.y;
            }
        }
        area += height * (line.x - distance);
        distance = line.x;

        if (line.endOfRect) {
            vertLines.erase(VertLine(rects[line.rectID].startY, line.rectID, false));
            vertLines.erase(VertLine(rects[line.rectID].endY, line.rectID, true));
        } else {
            vertLines.insert(VertLine(rects[line.rectID].startY, line.rectID, false));
            vertLines.insert(VertLine(rects[line.rectID].endY, line.rectID, true));
        }
    }

    cout << area << endl;
    return 0;
}