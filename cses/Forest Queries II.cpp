#include <bits/stdc++.h>

using namespace std;

#define F0R(i, n) for (int i = 0; i < n; i++)

int bit[1001][1001];

void upd2(int i, int j, int v) {
    while (j <= 1000) {
        bit[i][j] += v;
        j += j&-j;
    }
}

void upd(int i, int j, int v) {
    while (i <= 1000) {
        upd2(i, j, v);
        i += i&-i;
    }
}

int qry2(int i, int j) {
    int s = 0;
    while (j) {
        s += bit[i][j];
        j -= j&-j;
    }
    return s;
}

int qry(int i, int j) {
    if (i==0||j==0) return 0;
    int s = 0;
    while (i) {
        s += qry2(i, j);
        i -= i&-i;
    }
    return s;
}

int main() {
    int n, q; cin >> n >> q;

    int A[n][n];
    F0R(i, n+1) F0R(j, n+1) bit[i][j] = 0;
    F0R(i, n) {
        F0R(j, n) {
            char c; cin >> c;
            if (c == '*') {
                upd(i+1, j+1, 1);
            }
            A[i][j] = c == '*';
        }
    }

    F0R(i, q) {
        int c; cin >> c;
        if (c == 1) {
            int x, y; cin >> x >> y;
            if (A[x-1][y-1] == 0) {
                A[x-1][y-1] = 1;
                upd(x, y, 1);
            } else {
                A[x-1][y-1] = 0;
                upd(x, y, -1);
            }
        } else {
            int a, b, x, y; cin >> a >> b >> x >> y;
            cout << qry(x, y) - qry(a-1, y) - qry(x, b-1) + qry(a-1, b-1) << endl;
        }
    }

    return 0;
}
