/*
 * Same solution as dolphingarlic:
 * https://github.com/dolphingarlic/CompetitiveProgramming/blob/master/Balkan/Balkan%2018-popa.cpp
 */
#include <bits/stdc++.h>
#include "popa.h"

using namespace std;

int solve(int N, int *L, int *R) {
    for (int i = 0; i < N; i++) {
        L[i] = R[i] = -1;
    }
    int root = -1;
    for (int i = 0; i < N; i++) {
        if (root == -1) {
            root = i;
            continue;
        }
        vector<int> nodes;
        int cur = root;
        while (cur != -1) {
            nodes.push_back(cur);
            cur = R[cur];
        }
        for (int idx = nodes.size()-1; idx >= 0; idx--) {
            cur = nodes[idx];
            if (query(cur, cur, cur, i)) {
                R[cur] = i;
                break;
            }
            if (idx > 0) {
                int par = nodes[idx-1];
                R[par] = i;
            } else {
                root = i;
            }
            R[cur] = L[i];
            L[i] = cur;
        }
    }
    return root;
}
