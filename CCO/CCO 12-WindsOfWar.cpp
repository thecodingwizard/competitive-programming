/*
 * Sort all the points by the angle origin->point makes with the x-axis.
 *
 * Define dp(i, j) = maximum advantage we can get assuming the last edge in the
 * net was i->j, not counting any point that's less than equal to j.
 *
 * We transition to k by making the next edge of the net j->k. We need to make
 * sure that i->j and j->k still maintain a convex polygon.
 */

#include <bits/stdc++.h>

using namespace std;

#define ii pair<int, int>
#define f first
#define s second
#define maxn 101
#define ll long long
#define inf 10000

struct coord {
    ll x, y; int w;
    double angle() {
        return atan2(y, x);
    }
    bool operator<(coord &other) {
        return angle() < other.angle();
    }
};

int p, t; 
coord A[maxn];

bool valid(int i, int j, int k) {
    // return if we can draw edge i->j and j->k while being convex
    ii va = make_pair(A[j].x-A[i].x,A[j].y-A[i].y);
    ii vb = make_pair(A[k].x-A[j].x,A[k].y-A[j].y);
    ll cross = (ll)va.f*vb.s-(ll)va.s*vb.f;
    return cross >= 0;
}

bool in(int i, int j, int point) {
    // return true if point p is in triangle defined by 0->A[i] and 0->A[j]
    coord p = A[point], p0 = A[0], p1 = A[i], p2 = A[j];
    // Source: https://stackoverflow.com/questions/2049582/how-to-determine-if-a-point-is-in-a-2d-triangle
    ll A = (-p1.y * p2.x + p0.y * (-p1.x + p2.x) + p0.x * (p1.y - p2.y) + p1.x * p2.y);
    ll sign = A < 0 ? -1 : 1;
    ll s = (p0.y * p2.x - p0.x * p2.y + (p2.y - p0.y) * p.x + (p0.x - p2.x) * p.y) * sign;
    ll t = (p0.x * p1.y - p0.y * p1.x + (p0.y - p1.y) * p.x + (p1.x - p0.x) * p.y) * sign;
    return s > 0 && t > 0 && (s + t) < A * sign;
}

int score(int i, int j) {
    // return score in between i and j, excluding i
    int s = A[j].w;
    for (int a = i+1; a < j; a++) {
        if (a == i) continue;
        if (in(i, j, a)) s += A[a].w;
    }
    return s;
}

int memo[maxn][maxn];
int dp(int u, int v) {
    if (memo[u][v] != -inf) return memo[u][v];
    int best = 0;

    for (int i = v+1; i <= p+t; i++) {
        if (valid(u, v, i)) {
            best = max(best, dp(v, i) + score(v, i));
        }
    }

    return memo[u][v] = best;
}

int main() {
    cin >> p >> t;
    A[0].x = A[0].y = A[0].w = 0;
    for (int i = 1; i <= p; i++) {cin >> A[i].x >> A[i].y; A[i].w = 1;}
    for (int i = p+1; i <= p+t; i++) {cin >> A[i].x >> A[i].y; A[i].w = -1;}
    sort(A, A+p+t+1);

    for (int i = 0; i <= p+t; i++) {
        fill(memo[i], memo[i]+p+t+1, -inf);
    }

    int best = 0;
    for (int i = 1; i <= p+t; i++) {
        best = max(best, dp(0, i) + A[i].w);
    }
    cout << best << endl;

    return 0;
}
