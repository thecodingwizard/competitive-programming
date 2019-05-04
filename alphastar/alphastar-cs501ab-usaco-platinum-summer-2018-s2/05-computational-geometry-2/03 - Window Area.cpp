/*
Window Area
===========

You've just be assigned the project of implemented a windowing
interface. This windowing interface is fairly simple, and
fortunately, you don't have to display the actual windows. There
are 5 basic operations:

    Create a window
    Bring a window to the top
    Put a window to the bottom
    Destroy a window
    Output what percentage of a window is visible (i.e., isn't
covered by windows above it).

In the input, the operations appear in the following format:

    Create window: w(I,x,y,X,Y)
    Bring window to top: t(I)
    Put window on bottom: b(I)
    Destroy window: d(I)
    Output percentage visible: s(I)

The I is a unique identifier for each window, which is one
character. The character can be any of 'a'..'z', 'A'..'Z', and
'0'..'9'. No extra spaces will appear in the input.

(x,y) and (X,Y) are opposite corners of the window. When a window
is created, it is put `on top'. You can't create a window with an
identifier that is already in use, but you can destroy a window and
then create a new one with the identifier of the destroyed window.
Coordinates will be positive integers, and all windows will be of
non-zero area (x != X and y != Y). The x and y coordinates are
between 1 and 32767 inclusive.

PROGRAM NAME: window

INPUT FORMAT:

The input file consists of a sequence of commands to your
interpreter. They will be listed one per line. Terminate the
program when no more input is available

SAMPLE INPUT:

w(a,10,132,20,12)
w(b,8,76,124,15)
s(a)

OUTPUT FORMAT:

Output lines only for the s() commands. Of course, there might be
several s() commands (but no more than 500) so the output should be
a sequence of percentages, one per line, stating the percentage of
the windows that are visible. The percentages should be rounded to
3 decimal places.

SAMPLE OUTPUT:

49.167
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

struct Window {
    int x1, y1, x2, y2, layer; // x1 <= x2, y1 <= y2
    bool alive;
};

Window windows[128];
int topLayer = 1;
int bottomLayer = 0;

int area(int x1, int y1, int x2, int y2) {
    return (y1-y2)*(x2 - x1);
}

int calcArea(int x1, int y1, int x2, int y2, int layer) {
    if (x2 <= x1 || y2 <= y1) return 0;

    for (int i = 0; i < 128; i++) {
        if (!windows[i].alive || windows[i].layer <= layer) continue;
        if (y2 <= windows[i].y1 || windows[i].y2 <= y1 || x2 <= windows[i].x1 || windows[i].x2 <= x1) continue;
        return calcArea(x1, y1, max(windows[i].x1, x1), y2, layer)
               + calcArea(max(windows[i].x1, x1), min(windows[i].y2, y2), min(windows[i].x2, x2), y2, layer)
               + calcArea(min(windows[i].x2, x2), y1, x2, y2, layer)
               + calcArea(max(windows[i].x1, x1), y1, min(windows[i].x2, x2), max(windows[i].y1, y1), layer);
    }

    // this is the top-most layer, or has no windows above it
    return area(x1, y1, x2, y2);
}

int main() {
    char c;
    for (int i = 0; i < 128; i++) windows[i].alive = false;
    while (cin >> c) {
        char junk, id;
        switch (c) {
            case 'w':
                int x1, y1, x2, y2; cin >> junk >> id >> junk >> x1 >> junk >> y1 >> junk >> x2 >> junk >> y2 >> junk;
                windows[id] = Window{min(x1, x2), min(y1, y2), max(x1, x2), max(y1, y2), topLayer++};
                windows[id].alive = true;
                break;
            case 't':
                cin >> junk >> id >> junk;
                windows[id].layer = topLayer++;
                break;
            case 'b':
                cin >> junk >> id >> junk;
                windows[id].layer = bottomLayer--;
                break;
            case 'd':
                cin >> junk >> id >> junk;
                windows[id].alive = false;
                break;
            case 's':
                cin >> junk >> id >> junk;
                printf("%0.3f\n", abs(100.0*double(calcArea(windows[id].x1, windows[id].y1, windows[id].x2, windows[id].y2, windows[id].layer))/double(area(windows[id].x1, windows[id].y1, windows[id].x2, windows[id].y2))));
                break;
            default:
                assert(false);
        }
    }

    return 0;
}
