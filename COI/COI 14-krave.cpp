/*
 * Same solution as editorial
 *
 * For every point we need to find the y bound above / below and x bound left / right.
 * 
 * We can do this by maintaining one set for every x coordinate and one set for every
 * y coordinate. Every time we add a horizontal fence, we loop through every x
 * coordinate that the fence covers, and for the corresponding set, we insert the
 * y coordinate of that fence. Similarly for vertical fences.
 *
 * Then, to find the y bound / x bound, we just have to binary search in the
 * appropriate set.
 *
 * However, this is too slow as fences can be very long. Therefore, we can
 * use a segment tree like idea, where instead of an array of length A
 * we make a segment tree of size A. Each segment tree node is a set that corresponds
 * to a certain range. Every value in the set is a value that appears across the entire range.
 */

#include <bits/stdc++.h>

using namespace std;

#define maxn 100000
#define ii pair<int, int>
#define f first
#define s second

set<int> vert[4*maxn], horiz[4*maxn];

ii qry(int p, int i, int j, int k, int l, set<int> s[]) {
    ii ans = make_pair(*(--s[p].lower_bound(l)), *s[p].lower_bound(l));

    if (i != j) {
        int mid = (i+j)/2;
        ii a2;
        if (mid >= k) {
            a2 = qry((p << 1), i, mid, k, l, s);
        } else {
            a2 = qry(2*p+1, mid+1, j, k, l, s);
        }
        ans.f = max(ans.f, a2.f);
        ans.s = min(ans.s, a2.s);
    }

    return ans;
}

ii queryHoriz(int p, int i, int j, int k, int l) {
    return qry(p, i, j, k, l, horiz);
}
ii queryVert(int p, int i, int j, int k, int l) {
    return qry(p, i, j, k, l, vert);
}

void upd(int p, int i, int j, int x, int y, int v, set<int> s[]) {
    if (i > y || j < x) return;
    if (x <= i && j <= y) {
        s[p].insert(v);
        return;
    }
    if (i != j) {
        upd(p << 1, i, (i+j)/2, x, y, v, s);
        upd(p*2+1, (i+j)/2+1, j, x, y, v, s);
    }
}

int main() {
    cin.tie(0); ios::sync_with_stdio(false);

    int A, B; cin >> A >> B;
    int n; cin >> n;

    for (int i = 1; i < 4*maxn; i++) {
        vert[i].insert(0); vert[i].insert(A);
        horiz[i].insert(0); horiz[i].insert(B);
    }

    for (int i = 0; i < n; i++) {
        int x, y, d; cin >> x >> y >> d;
        ii yBound = queryHoriz(1, 1, A-1, x, y);
        ii xBound = queryVert(1, 1, B-1, y, x);
        if (d == 1) {
            long long w = xBound.s - xBound.f;
            long long a = w*(y-yBound.f), b = w*(yBound.s-y);
            cout << min(a, b) << " " << max(a, b) << "\n";
            upd(1, 1, A-1, xBound.f, xBound.s, y, horiz);
        } else {
            long long h = yBound.s - yBound.f;
            long long a = h*(x-xBound.f), b = h*(xBound.s-x);
            cout << min(a, b) << " " << max(a, b) << "\n";
            upd(1, 1, B-1, yBound.f, yBound.s, x, vert);
        }
    }

    return 0;
}
