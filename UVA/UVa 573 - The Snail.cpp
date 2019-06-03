#include <iostream>
#include <cstring>
#include <algorithm>
#define INF 1000000000

int main() {
    double H, U, D, F;
    int day;
    double height;
    while (std::cin >> H >> U >> D >> F && H != 0) {
        height = 0;
        double fatigue = U * F/100.0;
        for (day = 1; ; day++) {
            height += U;
            if (height > H) {
                printf("success on day %d\n", day);
                break;
            }
            U -= fatigue;
            if (U < 0) U = 0;
            height -= D;
            if (height < 0) {
                printf("failure on day %d\n", day);
                break;
            }
        }
    }
    return 0;
}