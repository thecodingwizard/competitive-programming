/*
- Use 4 writes for remember, and 6 reads for compare
- Split 0...4095 into groups of 373. Write 1 to the group that contains a, and leave everything else alone.
- In the compare function, query the group that contains b.
  - If this group is set to 0, then we query the remaining groups on the smaller side of b to determine
    whether a is larger or smaller than b. There are 11 groups. Worst case we will need six queries (middle group + 5 groups on one side)
  - If this group is not set to 0, then a and b are both in the same group of length 373.
- Now we have the same problem but with fewer reads/writes and a smaller range.
- We'll split the group of size 373 into groups of size 42, and run the same algorithm.
  There are 9 such groups, so compare() will use at most 5 queries.
- If they're both in the same group of size 42, then we'll split it into groups of size 6, then finally groups of size 1.
*/

#include "cmp.h"
#include <bits/stdc++.h>

using namespace std;

void remember(int n) {
    vector<int> gaps = { 373, 42, 6, 1 };
    int cur = 0;
    int end = 4096;
    int nxt = -1;
    int nxtEnd = -1;
    vector<int> shift = { 1, 12, 21, 28, 34 };
    for (int i = 0; i < 4; i++) {
        int idx = shift[i];
        while (cur < end) {
            if (cur <= n && n < cur+gaps[i]) {
                bit_set(idx);
                nxt = cur;
                nxtEnd = cur + gaps[i];
            }
            cur += gaps[i];
            idx++;
        }
        cur = nxt;
        end = nxtEnd;
    }
}

int compare(int b) {
    vector<int> gaps = { 373, 42, 6, 1 };
    // vector<int> shift = { 11, 9, 7, 6 };
    vector<int> shift = { 1, 12, 21, 28, 34 };
    int cur = 0;
    for (int i = 0; i < 4; i++) {
        int idx = shift[i];
        while (true) {
            if (cur <= b && b < cur + gaps[i]) {
                break;
            }
            cur += gaps[i];
            idx++;
        }
        if (!bit_get(idx)) {
            int lowerIndex = shift[i], upperIndex = shift[i+1]-1;
            if (idx - lowerIndex < upperIndex - idx) {
                // ask [lowerIndex...index)
                while (lowerIndex < idx) {
                    if (bit_get(lowerIndex)) return 1;
                    lowerIndex++;
                }
                return -1;
            } else {
                // ask (index...upperIndex]
                idx++;
                while (idx <= upperIndex) {
                    if (bit_get(idx)) return -1;
                    idx++;
                }
                return 1;
            }
        }
    }
    return 0;
}

