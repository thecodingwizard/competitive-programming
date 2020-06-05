/*
 * Solved with CDQ D&C:
 * https://robert1003.github.io/2020/01/31/cdq-divide-and-conquer.html
 *
 * Each point can be stored as (i, p_i, x_i) where i is the index,
 * p_i is the ith number in the permtuation array, and x_i is the
 * value of the (p_i)th number in the first array.
 *
 * There are two cases to consider:
 * 1. i > j, p_i > p_j, and x_i < x_j
 * 2. i . j, p_i < p_j, and x_i > x_j
 *
 * I just ran CDQ twice, but I believe it is doable by running it only once
 * (look at benq's code).
 */


#include <bits/stdc++.h>

using namespace std;

#define ll long long

struct Point {
    int x, y, z;
};

struct BIT {
    int b[500001];

    int query(int k) {
        int s = 0;
        while (k) {
            s += b[k];
            k -= k&-k;
        }
        return s;
    }

    void update(int k, int v) {
        while (k <= 500000) {
            b[k] += v;
            k += k&-k;
        }
    }
} bit;

vector<Point> A;
int ans[500000];

// case 1: i > j, p_i < p_j and x_i > x_j
void cdq_case1(int l, int r) {
    if (l+1==r) return;
    int m = (l+r)/2;

    // this also sorts [l, m) and [m, r) so we can do merge sort later
    cdq_case1(l, m); cdq_case1(m, r);
    
    int a = l, b = m, sum = 0;

    vector<int> bitchanges;
    vector<Point> tmp;

    while (a < m || b < r) {
        if (a < m && (b >= r || A[a].y > A[b].y)) {
            bit.update(A[a].z, 1);
            sum++;
            bitchanges.push_back(A[a].z);
            tmp.push_back(A[a]);
            a++;
        } else {
            ans[A[b].x] += bit.query(A[b].z - 1);
            tmp.push_back(A[b]);
            b++;
        }
    }

    for (int i = l; i < r; i++) A[i] = tmp[i - l];
    for (int x : bitchanges) bit.update(x, -1);
    bitchanges.clear();
    tmp.clear();
}

// case 2: i > j, p_i > p_j and x_i < x_j
void cdq_case2(int l, int r) {
    if (l+1==r) return;
    int m = (l+r)/2;

    // this also sorts [l, m) and [m, r) so we can do merge sort later
    cdq_case2(l, m); cdq_case2(m, r);
    
    int a = l, b = m, sum = 0;

    vector<int> bitchanges;
    vector<Point> tmp;

    while (a < m || b < r) {
        if (a < m && (b >= r || A[a].y < A[b].y)) {
            bit.update(A[a].z, 1);
            sum++;
            bitchanges.push_back(A[a].z);
            tmp.push_back(A[a]);
            a++;
        } else {
            ans[A[b].x] += sum - bit.query(A[b].z);
            tmp.push_back(A[b]);
            b++;
        }
    }

    for (int i = l; i < r; i++) A[i] = tmp[i - l];
    for (int x : bitchanges) bit.update(x, -1);
    bitchanges.clear();
    tmp.clear();
}

int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);

    int n; cin >> n;
    int X[n]; for (int i = 0; i < n; i++) cin >> X[i];
    int P[n]; for (int i = 0; i < n; i++) cin >> P[i];

    for (int i = 0; i < n; i++) {
        int p = P[i]-1;
        int v = X[p];
        A.push_back({ i, p, v });
    }
    vector<Point> B(A);

    for (int i = 0; i < n; i++) ans[i] = 0;
    for (int i = 1; i <= 500000; i++) bit.b[i] = 0;

    cdq_case1(0, n);
    A = B;
    cdq_case2(0, n);

    ll sum = 0;
    for (int i = 0; i < n; i++) {
        sum += ans[i];
        cout << sum << endl;
    }
}
