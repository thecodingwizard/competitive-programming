/*
 * See tmw: https://oj.uz/submission/296917
 *
 * Use a lazy seg tree. each node stores, for its range, the minimum height
 * of any column and the maximum height of any column. When propagating down,
 * update child nodes with min/max height, and then reset the min height to 0
 * and the max height to infinity.
 *
 * Also see tmw's implementation for more details :)
 */

#include <bits/stdc++.h>
using namespace std;
#include "wall.h"

struct node {
    int small = 0, large = 1e9;

    void upd(int op, int h) {
        if (op == 1) {
            // min
            small = max(small, h);
            large = max(large, h);
        } else {
            // max
            small = min(small, h);
            large = min(large, h);
        }
    }
};

node st[(1 << 22)];

void down(int p, int i, int j) {
    if (i == j) return;
    st[p*2].small = max(st[p].small, min(st[p*2].small, st[p].large));
    st[p*2].large = min(st[p].large, max(st[p*2].large, st[p].small));
    st[p*2+1].small = max(st[p].small, min(st[p*2+1].small, st[p].large));
    st[p*2+1].large = min(st[p].large, max(st[p*2+1].large, st[p].small));
    st[p].small = 0; st[p].large = 1e9;
}

void upd(int p, int i, int j, int l, int r, int op, int h) {
    down(p, i, j);
    if (i > r || j < l) return;
    if (l <= i && j <= r) {
        st[p].upd(op, h);
        return;
    }
    upd(p*2, i, (i+j)/2, l, r, op, h);
    upd(p*2+1, (i+j)/2+1, j, l, r, op, h);
}

int qry(int p, int i, int j, int x) {
    down(p, i, j);
    if (i == j && i == x) {
        return st[p].small;
    }
    if ((i+j)/2 >= x) return qry(p*2, i, (i+j)/2, x);
    return qry(p*2+1, (i+j)/2+1, j, x);
}

void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalHeight[]) {
    for (int i = 0; i < k; i++) {
        upd(1, 0, n-1, left[i], right[i], op[i], height[i]);
    }
    for (int i = 0; i < n; i++) {
        finalHeight[i] = qry(1, 0, n-1, i);
    }
}

