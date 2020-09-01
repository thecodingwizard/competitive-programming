/*
 * Same as editorial: https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/official/2010/contest1_solutions/solutions.pdf
 *
 * First, we need to figure out the number of items given A, B, and the size of the range n.
 * So, we need to compute A%B, 2A%B, 3A%B, ... nA%B
 *
 * This is equivalent to A(1 + 2 + ... + n) - B(floor(A/B) + floor(2A/B) + floor(3A/B) + ... + floor(nA/B))
 *
 * Therefore, we only have to find floor(A/B) + ... + floor(nA/B)
 *
 * This can actually be viewed as a comp geo problem. Imagine a triangle with coordinates
 * (0, 0), (n, 0), and (n, nA/B). The problem above is equivalent to the number of lattice points
 * in this triangle, excluding points on the x-axis.
 *
 * If A >= B, then we can rewrite A as kB + c. Then our answer is k(1 + 2 + ... + n) + solve(c, B, n).
 *
 * If A < B, we want to convert this to the previous case. We can solve this by complementary counting.
 * We can fairly easy count the total number of points in the _rectangle_ (0, 0), (0, nA/B), (n, 0), and (n, nA/B).
 * Then we can count the number of lattice points strictly above the diagonal of the rectangle, and subtract this
 * number from the total number to get our desired result.
 *
 * We can count the number of lattice points above the diagonal by flipping the X & Y axis:
 * solve(a, b, n) = total points - solve(b, a, floor(a*b/n)) + points on diagonal.
 *
 * Then we can use a segment tree with coordinate compression to solve the rest of the problem.
 */

#include <bits/stdc++.h>

using namespace std;

#define ll long long

struct query {
    int c, l, r, a, b;
};

struct node {
    ll val;
    int a = -1, b, start;
};

int n, q; 
node st[800000];
vector<int> coords;
map<int, int> coordIdx;

// calculate number of lattice points in the triangle
// (0, 0), (x, 0), (x, a/b*x)
// Ignore the x-axis
ll calcTriangle(int a, int b, ll x) {
    /*
    ll ans = 0;
    for (int i = 0; i <= x; i++) {
        for (int j = 1; (double)a/b*i+1e-7 >= j; j++) {
            ans++;
        }
    }
    */
    //cout << "triangle: " << a << " " << b << " " << x << " " << ans << endl;
    if (x == 0) return 0;
    if (a >= b) {
        // kb + c = a
        int k = a/b;
        int c = a%b;
        return (ll)k*(x*(x+1)/2)+calcTriangle(c, b, x);
    } else {
        ll total = (ll)a*x/b;
        total *= x;
        ll onLine = a==0?0:x/(b/__gcd(a,b));
        total += onLine;
        return total - calcTriangle(b, a, (ll)a*x/b);
    }
}

// calculate [l, r] sum assuming the query started at start,
// is present for the entire given range, and had parameters A and B
ll calc(int a, int b, int start, int l, int r) {
    r -= start-1; l -= start-1;
    ll extra = (ll)b*(calcTriangle(a, b, r) - (l-1 > 0 ? calcTriangle(a, b, l-1) : 0));
    ll ltor = (ll)r*(r+1)/2-(ll)l*(l-1)/2;
    ll ans = (ll)a*ltor-extra;
    //cout << a << " " << b << " " << start << " " << l << " " << r << " " << ans << endl;
    return ans;
}

void down(int p, int i, int j) {
    if (st[p].a == -1) return;
    assert(i > 0);
    st[p].val = calc(st[p].a, st[p].b, st[p].start, coords[i-1]+1, coords[j]);
    if (i != j) {
        st[p*2].a = st[p*2+1].a = st[p].a;
        st[p*2].b = st[p*2+1].b = st[p].b;
        st[p*2].start = st[p*2+1].start = st[p].start;
    }
    st[p].a = -1;
}

void upd(int p, int i, int j, int l, int r, int a, int b, int start) {
    down(p, i, j);
    if (j < l || i > r) return;
    if (l <= i && j <= r) {
        st[p].a = a, st[p].b = b, st[p].start = start;
        down(p, i, j);
        return;
    }
    upd(p*2, i, (i+j)/2, l, r, a, b, start);
    upd(p*2+1, (i+j)/2+1, j, l, r, a, b, start);
    st[p].val = st[p*2].val + st[p*2+1].val;
    down(p, i, j);
}

ll stqry(int p, int i, int j, int l, int r) {
    down(p, i, j);
    if (j < l || i > r) return 0;
    if (l <= i && j <= r) {
        return st[p].val;
    }
    return stqry(p*2, i, (i+j)/2, l, r) + stqry(p*2+1, (i+j)/2+1, j, l, r);
}

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);
    cin >> n >> q;

    vector<query> queries;
    for (int i = 0; i < q; i++) {
        int c; cin >> c;
        if (c == 1) {
            int l, r, a, b; cin >> l >> r >> a >> b;
            queries.push_back({c,l,r,a,b});
            coords.push_back(l);
            coords.push_back(l-1);
            coords.push_back(r);
        } else {
            int l, r; cin >> l >> r;
            queries.push_back({c, l, r});
            coords.push_back(l);
            coords.push_back(l-1);
            coords.push_back(r);
        }
    }
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());
    for (int i = 0; i < (int)coords.size(); i++) {
        coordIdx[coords[i]] = i;
    }
    n = coords.size();
    assert(n <= 200000);

    for (query qry : queries) {
        if (qry.c == 1) {
            upd(1, 0, n-1, coordIdx[qry.l], coordIdx[qry.r], qry.a, qry.b, qry.l);
        } else {
            cout << stqry(1, 0, n-1, coordIdx[qry.l], coordIdx[qry.r]) << "\n";
        }
    }

    return 0;
}
