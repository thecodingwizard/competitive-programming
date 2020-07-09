#include "treasure.h"

void findTreasure (int N) {
    int cnt = countTreasure(1, 1, N, N);
    if(cnt > 0) Report (1, 1);
}