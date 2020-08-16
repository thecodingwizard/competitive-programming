/*
 * THe code below gets 9/10; it fails on one test case due to floating point error in the line interesction function:
 *
 * 4 4
 * 0 -999999
 * 1 1000000
 * 1 999999
 * 0 -1000000
 * 1 2
 * 2 3
 * 3 4
 * 1 4
 *
 *
 * The idea is you want to greedily take the road that leads to the town with the smallest number.
 * To do this:
 * - For every town, find the town it is connected to with the smallest number
 * - Process the towns from n to 1. At each town, check if the road will lead to a smaller
 *   town than we're currently headed to. If so, take the road.
 *
 * My implementation uses a line segment intersection from cp-algorithms but it doesn't
 * pass the above test case due to floating point precision issues; maybe there's a better
 * way to solve the problem?
 */


#include <bits/stdc++.h>

using namespace std;

#define ii pair<int, int>
#define f first
#define s second
#define mp make_pair

#define double long double
#define co pair<double, double>


const double EPS = 6E-7;

struct pt {
    double x, y;

    bool operator<(const pt& p) const
    {
        return x < p.x - EPS || (abs(x - p.x) < EPS && y < p.y - EPS);
    }
};

struct line {
    double a, b, c;

    line() {}
    line(pt p, pt q)
    {
        a = p.y - q.y;
        b = q.x - p.x;
        c = -a * p.x - b * p.y;
        norm();
    }

    void norm()
    {
        double z = sqrt(a * a + b * b);
        if (abs(z) > EPS)
            a /= z, b /= z, c /= z;
    }

    double dist(pt p) const { return a * p.x + b * p.y + c; }
};

double det(double a, double b, double c, double d)
{
    return a * d - b * c;
}

inline bool betw(double l, double r, double x)
{
    return min(l, r) <= x + EPS && x <= max(l, r) + EPS;
}

inline bool intersect_1d(double a, double b, double c, double d)
{
    if (a > b)
        swap(a, b);
    if (c > d)
        swap(c, d);
    return max(a, c) <= min(b, d) + EPS;
}

bool intersect(pt a, pt b, pt c, pt d, pt& left, pt& right)
{
    if (!intersect_1d(a.x, b.x, c.x, d.x) || !intersect_1d(a.y, b.y, c.y, d.y))
        return false;
    line m(a, b);
    line n(c, d);
    double zn = det(m.a, m.b, n.a, n.b);
    if (abs(zn) < EPS) {
        if (abs(m.dist(c)) > EPS || abs(n.dist(a)) > EPS) {
            return false;
        }
        if (b < a)
            swap(a, b);
        if (d < c)
            swap(c, d);
        left = max(a, c);
        right = min(b, d);
        return true;
    } else {
        left.x = right.x = -det(m.c, m.b, n.c, n.b) / zn;
        left.y = right.y = -det(m.a, m.c, n.a, n.c) / zn;
        return betw(a.x, b.x, left.x) && betw(a.y, b.y, left.y) &&
               betw(c.x, d.x, left.x) && betw(c.y, d.y, left.y);
    }
}




int n, m;
ii A[100000];
vector<ii> blocked;
int tgt[100000];

co findIntersection(pair<co, co> seg1, pair<co, co> seg2) {
    pt l, r;
    bool res = intersect(pt{seg1.f.f, seg1.f.s}, pt{seg1.s.f, seg1.s.s}, pt{seg2.f.f, seg2.f.s}, pt{seg2.s.f,seg2.s.s}, l, r);
    if (!res) {
        return mp(1e9, 1e9);
    }
    // assert(l == r);
    return mp(r.x, r.y);
}

int main() {
    cin.tie(0); ios_base::sync_with_stdio(0);

    // read in input
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> A[i].f >> A[i].s;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        blocked.push_back(mp(b-1, a-1));
    }
    sort(blocked.begin(), blocked.end());

    // for every point, find the first point it can reach
    int idx = 0;
    for (int i = 0; i < n; i++) {
        tgt[i] = -1;
        for (int j = 0; j < i; j++) {
            while (idx < m && (blocked[idx].f < i || (blocked[idx].f == i && blocked[idx].s < j))) idx++;

            if (idx < m && blocked[idx].f == i && blocked[idx].s == j) continue;

            tgt[i] = j;
            break;
        }
    }
    vector<ii>().swap(blocked);
    assert(tgt[n-1] != -1);

    // greedily add each point's segment, from n to 1
    // maintain a stack of segments, denoted by coordinate
    stack<pair<co, co>> s;
    s.push(mp(A[n-1], A[tgt[n-1]]));
    int curCoord = tgt[n-1];
    for (int i = n-2; i > 0; i--) {
        // when adding segment:
        // - check if the endpoint of the segment is less than the last segment's endpoint
        if (tgt[i] == -1 || curCoord <= tgt[i]) continue;

        // - if it does, then find intersection, update last segment, and push the new segment
        //   - if intersection DNE, then pop the last segment and repeat
        while (true) {
            assert(!s.empty());
            co intersection = findIntersection(s.top(), mp(A[i], A[tgt[i]]));
            if (intersection.f >= 1e8 && intersection.s >= 1e8) {
                s.pop();
                continue;
            }
            pair<co, co> updatedPrevious = mp(s.top().f, intersection);
            s.pop();
            s.push(updatedPrevious);
            s.push(mp(intersection, A[tgt[i]]));
            curCoord = tgt[i];
            break;
        }
    }

    cout << fixed; setprecision(20);
    // calculate final answer by looping through stack
    double ans = 0;
    while (!s.empty()) {
        pair<co, co> seg = s.top(); s.pop();
        ans += sqrt((seg.s.f-seg.f.f)*(seg.s.f-seg.f.f)+(seg.s.s-seg.f.s)*(seg.s.s-seg.f.s));
    }
    cout << ans << endl;

    return 0;
}
