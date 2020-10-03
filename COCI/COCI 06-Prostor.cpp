/*
 * Similar solution to editorial, sweep through one axis and use 2D fenwick tree
 * on the other two axes.
 *
 * My implementation is super messy because of memory issues...
 */

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define ii pair<int, int>
#define mp make_pair
#define f first
#define s second

int n; 
array<int, 6> A[100000];

struct FenwickTree {
    vector<int> ft = vector<int>(1000, 0);
    ll qry(int k) {
        ll ans = 0;
        while (k) {
            ans += ft[k];
            k -= k&-k;
        }
        return ans;
    }
    void upd(int k, int v) {
        while (k < 1000) {
            ft[k] += v;
            k += k&-k;
        }
    }
};

struct FenwickTree2D {
    vector<FenwickTree> ft;
    void init() {
        ft.resize(1000);
    }
    void freeMemory() {
        vector<FenwickTree>().swap(ft);
    }
    ll qry(int x, int y) {
        ll ans = 0;
        while (x) {
            ans += ft[x].qry(y);
            x -= x&-x;
        }
        return ans;
    }
    void upd(int x, int y, int v) {
        while (x < 1000) {
            ft[x].upd(y, v);
            x += x&-x;
        }
    }
};

//FenwickTree verticalIndivFirst[1000], verticalIndivSecond[1000];
vector<FenwickTree> verticalIndivFirst, verticalIndivSecond;
int verticalIndivCt[1000];
//FenwickTree horizontalIndivFirst[1000], horizontalIndivSecond[1000];
vector<FenwickTree> horizontalIndivFirst, horizontalIndivSecond;
int horizontalIndivCt[1000];
FenwickTree2D horizontalSegments, verticalSegments;

ll qry(int x1, int y1, int x2, int y2) {
    ll ans = 0;
    if (x1 != x2) {
        // horizontal line
        ans += verticalSegments.qry(x2, y1) - verticalSegments.qry(x1-1, y1);
    } else {
        // vertical line
        ans += horizontalSegments.qry(x1, y2) - horizontalSegments.qry(x1, y1-1);
    }
    return ans;
}

void upd(int x1, int y1, int x2, int y2, int v) {
    if (x1 != x2) {
        assert(y1 == y2);
        // horizontal line
        horizontalSegments.upd(x1, y1, v);
        horizontalSegments.upd(x2+1, y1, -v);
    } else {
        assert(x1 == x2);
        // vertical line
        verticalSegments.upd(x1, y1, v);
        verticalSegments.upd(x1, y2+1, -v);
    }
}

ll qry2(int x1, int y1, int x2, int y2) {
    ll ans = 0;
    if (x1 != x2) {
        // horizontal line
        ans += horizontalIndivCt[y1] - (horizontalIndivCt[y1] - horizontalIndivFirst[y1].qry(x2)) - horizontalIndivSecond[y1].qry(x1-1);
    } else {
        // vertical line
        ans += verticalIndivCt[x1] - (verticalIndivCt[x1] - verticalIndivFirst[x1].qry(y2)) - verticalIndivSecond[x1].qry(y1-1);
    }
    return ans;
}

void upd2(int x1, int y1, int x2, int y2, int v) {
    if (x1 != x2) {
        assert(y1 == y2);
        // horizontal line
        horizontalIndivCt[y1] += v;
        horizontalIndivFirst[y1].upd(x1, v);
        horizontalIndivSecond[y1].upd(x2, v);
    } else {
        assert(x1 == x2);
        // vertical line
        verticalIndivCt[x1] += v;
        verticalIndivFirst[x1].upd(y1, v);
        verticalIndivSecond[x1].upd(y2, v);
    }
}

ll solve(int a, int b, int c, int d = -1) {
    horizontalSegments.init();
    verticalSegments.init();
    //cerr << "Solving: " << a << ", " << b << ", " << c << endl;
    ll ans = 0;
    // first is c-coordinate, second is add (-1) or remove (+1)
    // array represents (x1, y1) and (x2, y2)
    vector<pair<ii, array<int, 4>>> events;
    for (int i = 0; i < n; i++) {
        array<int, 6> x = A[i];
        if (x[c] == x[c+3]) continue;
        if (d != -1 && x[d] != x[d+3]) continue;
        events.push_back(mp(mp(min(x[c], x[c+3]), -1), array<int, 4>{x[a],x[b],x[a+3],x[b+3]}));
        events.push_back(mp(mp(max(x[c], x[c+3]), 1), array<int, 4>{x[a],x[b],x[a+3],x[b+3]}));
    }
    sort(events.begin(), events.end());
    for (auto e : events) {
        if (e.s[0] == e.s[2] && e.s[1] > e.s[3]) {
            swap(e.s[0], e.s[2]);
            swap(e.s[1], e.s[3]);
        }
        if (e.s[1] == e.s[3] && e.s[0] > e.s[2]) {
            swap(e.s[0], e.s[2]);
            swap(e.s[1], e.s[3]);
        }
        //cerr << "z-coord: " << e.f.f << ". status: " << e.f.s << ". coordinates: (" << e.s[0] << "," << e.s[1] << "); (" << e.s[2] << "," << e.s[3] << ")." << endl;

        if (e.f.s == -1) {
            // adding
            ans += qry(e.s[0], e.s[1], e.s[2], e.s[3]);
            //cerr << "updated answer: " << ans << endl;
            upd(e.s[0], e.s[1], e.s[2], e.s[3], 1);
        } else {
            // removing
            upd(e.s[0], e.s[1], e.s[2], e.s[3], -1);
        }
    }
    horizontalSegments.freeMemory();
    verticalSegments.freeMemory();
    verticalIndivFirst.resize(1000);
    horizontalIndivFirst.resize(1000);
    verticalIndivSecond.resize(1000);
    horizontalIndivSecond.resize(1000);
    for (auto e : events) {
        if (e.s[0] == e.s[2] && e.s[1] > e.s[3]) {
            swap(e.s[0], e.s[2]);
            swap(e.s[1], e.s[3]);
        }
        if (e.s[1] == e.s[3] && e.s[0] > e.s[2]) {
            swap(e.s[0], e.s[2]);
            swap(e.s[1], e.s[3]);
        }
        //cerr << "z-coord: " << e.f.f << ". status: " << e.f.s << ". coordinates: (" << e.s[0] << "," << e.s[1] << "); (" << e.s[2] << "," << e.s[3] << ")." << endl;

        if (e.f.s == -1) {
            // adding
            ans += qry2(e.s[0], e.s[1], e.s[2], e.s[3]);
            //cerr << "updated answer: " << ans << endl;
            upd2(e.s[0], e.s[1], e.s[2], e.s[3], 1);
        } else {
            // removing
            upd2(e.s[0], e.s[1], e.s[2], e.s[3], -1);
        }
    }
    vector<FenwickTree>().swap(verticalIndivFirst);
    vector<FenwickTree>().swap(horizontalIndivFirst);
    vector<FenwickTree>().swap(verticalIndivSecond);
    vector<FenwickTree>().swap(horizontalIndivSecond);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 6; j++) cin >> A[i][j];
    }

    ll ans = 0;
    ans += solve(0, 1, 2);
    ans += solve(1, 2, 0);
    ans += solve(2, 0, 1);
    ans -= solve(0, 1, 2, 0);
    ans -= solve(1, 2, 0, 1);
    ans -= solve(2, 0, 1, 2);
    cout << ans << endl;

    return 0;
}
