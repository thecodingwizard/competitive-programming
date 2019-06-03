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

using namespace std;

#define INF 1000000000
#define ONE 1
#define ZERO 0
#define FLIP 2
#define DONE 3
typedef vector<int> vi;

int flip(int x) {
    if (x == ONE) return ZERO;
    if (x == ZERO) return ONE;
    if (x == FLIP) return DONE;
    return FLIP;
}

class SegmentTree {         // the segment tree is stored like a heap array
private: vi st, A, lazy;            // recall that vi is: typedef vector<int> vi;
    int n;
    int left (int p) { return p << 1; }     // same as binary heap operations
    int right(int p) { return (p << 1) + 1; }

    void build(int p, int L, int R) {                           // O(n log n)
        if (L == R)                            // as L == R, either one is fine
            st[p] = A[L];                                         // store the index
        else {                                // recursively compute the values
            build(left(p) , L              , (L + R) / 2);
            build(right(p), (L + R) / 2 + 1, R          );
            int p1 = st[left(p)], p2 = st[right(p)];
            st[p] = p1 + p2;
        } }

    int rmq(int p, int L, int R, int i, int j) {                  // O(log n)

        if (lazy[p] != DONE) {
            if (lazy[p] == FLIP) {
                st[p] = R - L + 1 - st[p];
            } else {
                st[p] = lazy[p] * (R - L + 1);
            }

            if (L != R) { // this node has children
                if (lazy[p] == ONE || lazy[p] == ZERO) {
                    lazy[left(p)] = lazy[p];
                    lazy[right(p)] = lazy[p];
                } else {
                    lazy[left(p)] = flip(lazy[left(p)]);
                    lazy[right(p)] = flip(lazy[right(p)]);
                }
            }

            lazy[p] = DONE;
        }

        if (i >  R || j <  L) return 0; // current segment outside query range

        if (L >= i && R <= j) return st[p];               // inside query range

        // compute the min position in the left and right part of the interval
        int p1 = rmq(left(p) , L              , (L+R) / 2, i, j);
        int p2 = rmq(right(p), (L+R) / 2 + 1, R          , i, j);

        return p1 + p2; }          // as as in build routine

    int update_tree(int p, int L, int R, int i, int j, int val) {
        if (lazy[p] != DONE) { // this node needs to be updated
            if (lazy[p] == FLIP) {
                st[p] = R - L + 1 - st[p];
            } else {
                st[p] = lazy[p] * (R - L + 1);
            }

            if (L != R) { // this node has children
                if (lazy[p] == ONE || lazy[p] == ZERO) {
                    lazy[left(p)] = lazy[p];
                    lazy[right(p)] = lazy[p];
                } else {
                    lazy[left(p)] = flip(lazy[left(p)]);
                    lazy[right(p)] = flip(lazy[right(p)]);
                }
            }

            lazy[p] = DONE;
        }

        if (L > R || L > j || R < i) return st[p]; // Current segment not in range

        if (L >= i && R <= j) { // segment fully in range
            if (val == FLIP) {
                st[p] = R - L + 1 - st[p];
            } else {
                st[p] = val * (R - L + 1);
            }

            if (L != R) { // Not leaf node
                if (val == ONE || val == ZERO) {
                    lazy[left(p)] = val;
                    lazy[right(p)] = val;
                } else {
                    lazy[left(p)] = flip(lazy[left(p)]);
                    lazy[right(p)] = flip(lazy[right(p)]);
                }
            }

            return st[p];
        }

        int p1 = update_tree(left(p), L, (L + R) / 2, i, j, val);
        int p2 = update_tree(right(p), (L + R) / 2 + 1, R, i, j, val);

        return st[p] = p1 + p2;
    }

public:
    SegmentTree(const vi &_A) {
        A = _A; n = (int)A.size();              // copy content for local usage
        st.assign(4 * n, 0);            // create large enough vector of zeroes
        lazy.assign(4 * n, DONE);
        build(1, 0, n - 1);                                  // recursive build
    }

    int rmq(int i, int j) { return rmq(1, 0, n - 1, i, j); }   // overloading

    int update_tree(int i, int j, int new_value) {
        return update_tree(1, 0, n - 1, i, j, new_value); }
};


int main() {
    int T;
    vi data;
    cin >> T;
    for (int x = 1; x <= T; x++) {
        cout << "Case " << x << ":" << endl;
        data.clear();
        int M;
        cin >> M;
        for (int i = 0; i < M; i++) {
            int T2;
            cin >> T2;
            string s;
            cin >> s;
            while (T2--) {
                for (auto &c : s) {
                    data.push_back(c - '0');
                }
            }
        }
        SegmentTree st(data);
        int Q, q = 1;
        cin >> Q;
        int a, b;
        char c;
        while (Q--) {
            cin >> c >> a >> b;
            if (c == 'F') {
                st.update_tree(a, b, ONE);
            } else if (c == 'E') {
                st.update_tree(a, b, ZERO);
            } else if (c == 'I') {
                st.update_tree(a, b, FLIP);
            } else {
                cout << "Q" << q++ << ": " << st.rmq(a, b) << endl;
            }
        }
    }
    return 0;
}