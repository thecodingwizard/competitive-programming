#include <iostream>
#include <string>
#include <utility>
#include <sstream>
#include <algorithm>
#include <stack>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <bitset>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <fstream>

using namespace std;

#define INF 1000000000
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define PI acos(-1.0)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;


#define DONE 0
#define TAKEN 1
#define EMPTY 2

struct Node {
    int left, right, max, len; // gap left edge, gap right edge, biggest gap in range, length
};

class SegmentTree {
private:
    vector<Node> st;
    vi lazy;
    int n;
    int left(int p) { return p << 1; }
    int right(int p) { return (p << 1) + 1; }

    void build(int p, int L, int R) {
        st[p].max = st[p].left = st[p].right = st[p].len = R - L + 1;
        if (L != R) {
            build(left(p), L, (L+R)/2);
            build(right(p), (L+R)/2 + 1, R);
        }
    }

    void propagate(int p) {
        lazy[left(p)] = lazy[right(p)] = lazy[p];
        if (lazy[p] == TAKEN) {
            st[left(p)].left = st[left(p)].right = st[left(p)].max = 0;
            st[right(p)].left = st[right(p)].right = st[right(p)].max = 0;
        } else {
            st[left(p)].left = st[left(p)].right = st[left(p)].max = st[left(p)].len;
            st[right(p)].left = st[right(p)].right = st[right(p)].max = st[right(p)].len;
        }
        lazy[p] = DONE;
    }

    int seat(int p, int L, int R, int partySize) {
        if (lazy[p] != DONE) propagate(p);
        if (st[p].left >= partySize) return L;
        if (st[left(p)].max >= partySize) return seat(left(p), L, (L+R)/2, partySize);
        if (st[left(p)].right + st[right(p)].left >= partySize) return (L+R)/2-st[left(p)].right+1;
        return seat(right(p), (L+R)/2+1, R, partySize);
    }

    void updateEmpty(int p, int L, int R, int i, int j, bool value) {
        if (i > R || j < L) return;
        if (L >= i && R <= j) {
            st[p].left = st[p].right = st[p].max = (value ? R-L+1 : 0);
            lazy[p] = (value ? EMPTY : TAKEN);
            return;
        }
        if (lazy[p] != DONE) propagate(p);
        updateEmpty(left(p), L, (L+R)/2, i, j, value);
        updateEmpty(right(p), (L+R)/2+1, R, i, j, value);
        st[p].max = max(max(st[left(p)].max, st[right(p)].max), st[left(p)].right + st[right(p)].left);
        if (st[left(p)].left == st[left(p)].len) {
            st[p].left = st[left(p)].left + st[right(p)].left;
        } else {
            st[p].left = st[left(p)].left;
        }
        if (st[right(p)].right == st[right(p)].len) {
            st[p].right = st[right(p)].right + st[left(p)].right;
        } else {
            st[p].right = st[right(p)].right;
        }
    }

public:
    SegmentTree(int _n) {
        n = _n;
        st.resize(4*n);
        lazy.assign(4*n, DONE);
        build(1, 1, n);
    }

    bool seat(int partySize) {
        if (st[1].max < partySize) return false;
        int startPos = seat(1, 1, n, partySize);
        updateEmpty(startPos, startPos + partySize - 1, false);
        return true;
    }

    bool updateEmpty(int i, int j, bool value) {
        updateEmpty(1, 1, n, i, j, value);
    }
};

int main() {
    freopen("seating.in", "r", stdin);
    freopen("seating.out", "w", stdout);
    int n, m; cin >> n >> m;
    SegmentTree st(n);
    int missed = 0;
    for (int i = 0; i < m; i++) {
        char c; cin >> c;
        if (c == 'A') {
            int x; cin >> x;
            if (!st.seat(x)) {
                missed++;
            }
        } else {
            int a, b; cin >> a >> b;
            st.updateEmpty(a, b, true);
        }
    }
    cout << missed << endl;
    return 0;
}
