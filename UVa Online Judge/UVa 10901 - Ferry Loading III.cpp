#include <iostream>
#include <string>
#include <utility>
#include <sstream>
#include <algorithm>
#include <stack>
#include <vector>
#include <queue>

#define INF 1000000000

using namespace std;


int main() {
    int c;
    queue<pair<int, int>> left, right;
    int n, t, m, time, ferryArrivalTime = 0, carsLoaded = 0;
    string side, ferryLocation = "left";


    cin >> c;

    for (int x = 0; x < c; x++) {

        if (x != 0) cout << endl;

        ferryArrivalTime = 0;
        carsLoaded = 0;
        ferryLocation = "left";

        cin >> n >> t >> m;
        int arrivalTimes[m] = {0};
        for (int i = 0; i < m; i++) {
            cin >> time >> side;
            if (side == "left") left.push(make_pair(time, i));
            else right.push(make_pair(time, i));
        }

        while (!left.empty() || !right.empty()) {
            if (ferryLocation == "left") {
                while (!left.empty() && left.front().first <= ferryArrivalTime && carsLoaded < n) {
                    carsLoaded++;
                    arrivalTimes[left.front().second] = ferryArrivalTime + t;
                    left.pop();
                }
                if (carsLoaded == 0 && !right.empty() && right.front().first <= ferryArrivalTime) {
                    ferryLocation = "right";
                    ferryArrivalTime += t;
                    continue;
                }
            } else {
                while (!right.empty() && right.front().first <= ferryArrivalTime && carsLoaded < n) {
                    carsLoaded++;
                    arrivalTimes[right.front().second] = ferryArrivalTime + t;
                    right.pop();
                }
                if (carsLoaded == 0 && !left.empty() && left.front().first <= ferryArrivalTime) {
                    ferryLocation = "left";
                    ferryArrivalTime += t;
                    continue;
                }
            }
            if (carsLoaded != 0) {
                carsLoaded = 0;
                if (ferryLocation == "left") {
                    ferryLocation = "right";
                } else {
                    ferryLocation = "left";
                }
                ferryArrivalTime += t;
            } else {
                ferryArrivalTime++;
            }
        }

        for (auto &time : arrivalTimes) {
            cout << time << endl;
        }
    }

    return 0;
}