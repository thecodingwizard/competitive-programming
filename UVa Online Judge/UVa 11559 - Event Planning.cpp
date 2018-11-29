#include <iostream>
#include <cstring>
#include <algorithm>
#define INF 1000000000

int main() {
    int N, B, H, W, costPerPerson, a;

    while (std::cin >> N >> B >> H >> W) {
        int minCost = INF;
        for (int i = 0; i < H; i++) {
            std::cin >> costPerPerson;
            for (int j = 0; j < W; j++) {
                std::cin >> a;
                if (a >= N) minCost = std::min(minCost, costPerPerson * N);
            }
        }

        if (minCost == INF || minCost > B) std::cout << "stay home" << std::endl;
        else std::cout << minCost << std::endl;
    }

    return 0;
}