#include <iostream>
#include <cstring>
#include <algorithm>
#define INF 1000000000

int main() {
    int T, N, minSpeed = 0, speed, caseNum = 1;
    std::cin >> T;
    while (T-- > 0) {
        std::cin >> N;
        for (int i = 0; i < N; i++) {
            std::cin >> speed;
            minSpeed = std::max(minSpeed, speed);
        }
        printf("Case %d: %d\n", caseNum++, minSpeed);
        minSpeed = 0;
    }

    return 0;
}