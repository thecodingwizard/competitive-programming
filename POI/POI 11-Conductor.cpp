/*
 * Define cost_j(i) = h_j + ceil(sqrt(abs(i-j))). We just need to calculate, for
 * every i, the maximum cost_j(i) across all j.
 *
 * We can split up each function into two parts to get rid of the absolute value.
 * If we get rid of the ceil() function, then note that cost_j(i) intersects
 * another cost_j(i) only once, so we can apply *convex hull trick*
 *
 * Note that with the ceil() function I think functions may intersect more than once
 * so the convex hull trick sometimes fails (not 100% sure...) so would recommend
 * using floating point numbers and not using the ceil function...
 */

#include <bits/stdc++.h>

using namespace std;

const int inf = 1e9+10;

struct func {
    int h, i; long double l, r;
};

int n; 
int mx1[500000];
int mx2[500000];
int H[500000];
int Sqrt[500000];

int eval(func f, int i) {
    return f.h+Sqrt[abs(i-f.i)];
    assert(i>=f.i);
    return f.h+Sqrt[i-f.i];
}

// returns when right part of func a intersects func b
long double intersectRight(func a, func b) {
    if (a.h>=b.h) return inf;
    long long d = b.h-a.h;
    if (b.i-a.i-d*d<0) return -1;
    long double x = (b.i-a.i)/2.0/d-d/2.0;
    long double ans = x*x+b.i;
    return ans;
}

void solveRight(int mx[]) {
    vector<func> s;
    for (int i = 0; i < n; i++) {
        func f = {H[i], i, 0, (long double)n-1};
        while (!s.empty()) {
            func f2 = s.back();
            long double intersect = intersectRight(f2, f);
            if (intersect <= f2.l) {
                s.pop_back();
            } else {
                if (intersect <= n-1) s.back().r = intersect;
                f.l = intersect;
                break;
            }
        }
        if (f.l <= n-1) s.push_back(f);
    }
    while (!s.empty()) {
        func f = s.back(); s.pop_back();
        for (int i = ceil(f.l); i <= floor(f.r); i++) {
            mx[i] = max(mx[i], eval(f, i));
        }
    }
}

int main() {
    cin.tie(0); ios_base::sync_with_stdio(0);
    cin >> n;
    Sqrt[0] = 0;
    for (int i = 1; i <= 1000; i++) {
        for (int j = (i-1)*(i-1)+1; j <= min(i*i, n-1); j++) Sqrt[j] = i;
    }
    for (int i = 0; i < n; i++) {
        cin >> H[i]; mx1[i] = mx2[i] = 0;
    }
    solveRight(mx1);
    for (int i = 0; i < n/2; i++) {
        swap(H[i], H[n-i-1]);
    }
    solveRight(mx2);
    for (int i = 0; i < n/2; i++) {
        swap(H[i], H[n-i-1]);
    }
    for (int i = 0; i < n; i++) {
        mx1[i] = max(mx1[i], mx2[n-1-i]);
    }
    for (int i = 0; i < n; i++) {
        cout << mx1[i]-H[i] << "\n";
    }
    return 0;
}
