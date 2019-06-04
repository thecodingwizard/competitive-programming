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

using namespace std;

#define INF 1000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

struct Cow {
    int x, y; bool g; // guernseys
};

bool howToSort(Cow a, Cow b) {
    if (a.x == b.x) {
        if ((a.g && b.g) || (!a.g && !b.g)) {
            return a.y < b.y;
        }
        if (a.g) return true;
        if (b.g) return true;
        return a.y < b.y;
    }
    return a.x < b.x;
}

int upperLimit = INF, lowerLimit = 0;
int main() {
    freopen("cowrect.in", "r", stdin);
    freopen("cowrect.out", "w", stdout);

    int n;
    cin >> n;
    vector<Cow> cows(n);
    for (int i = 0; i < n; i++) {
        cin >> cows[i].x >> cows[i].y;
        char c; cin >> c; cows[i].g = c == 'G';
    }

    sort(cows.begin(), cows.end(), howToSort);

    int maxNum = 0, minArea = INF;
    for (int i = 0; i < n; i++) {
        if (cows[i].g) continue;
        upperLimit = INF;
        lowerLimit = 0;
        vector<Cow> currentCows;
        currentCows.push_back(cows[i]);
        for (int j = i + 1; j < n; j++) {
            int x = cows[j].x, y = cows[j].y;
            if (cows[j].g) {
                if (y > cows[i].y) {
                    upperLimit = min(upperLimit, y);
                } else {
                    lowerLimit = max(lowerLimit, y);
                }
                currentCows.erase(remove_if(currentCows.begin(), currentCows.end(), [](const Cow &c){ return c.y >= upperLimit || c.y <= lowerLimit; }),
                                  currentCows.end());
            } else {
                if (cows[j].y > lowerLimit && cows[j].y < upperLimit) currentCows.push_back(cows[j]);
            }
            if (currentCows.size() >= maxNum) {
                int highestY = 0, lowestY = INF; int highestX = 0, lowestX = INF;
                for (Cow cow : currentCows) {
                    highestY = max(highestY, cow.y);
                    lowestY = min(lowestY, cow.y);
                    highestX = max(highestX, cow.x);
                    lowestX = min(lowestX, cow.x);
                }
                if (currentCows.size() > maxNum) {
                    maxNum = currentCows.size();
                    minArea = (lowestY - highestY)*(lowestX - highestX);
                } else if (currentCows.size() == maxNum) {
                    minArea = min(minArea, (lowestY - highestY)*(lowestX - highestX));
                }
            }
        }
    }

    cout << maxNum << endl << minArea << endl;

    return 0;
}