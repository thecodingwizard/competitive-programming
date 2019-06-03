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

using namespace std;

#define INF 1000000000
typedef vector<int> vi;

struct Result {
    bool inRange;
    int lval, rval, lfreq, rfreq, ans;
};

Result make_result(bool inRange, int lval, int rval, int lfreq, int rfreq, int ans) {
    Result r{};
    r.inRange = inRange;
    r.lval = lval;
    r.rval = rval;
    r.lfreq = lfreq;
    r.rfreq = rfreq;
    r.ans = ans;
    return r;
}

Result make_result(bool inRange) {
    return make_result(inRange, 0, 0, 0, 0, 0);
}

class SegmentTree {         // the segment tree is stored like a heap array
private: vi ans, lval, rval, lfreq, rfreq, A;            // recall that vi is: typedef vector<int> vi;
    int n;
    int left (int p) { return p << 1; }     // same as binary heap operations
    int right(int p) { return (p << 1) + 1; }

    void build(int p, int L, int R) {                           // O(n log n)
        if (L == R) {                           // as L == R, either one is fine
            ans[p] = 1;
            lval[p] = A[L];
            rval[p] = A[L];
            lfreq[p] = 1;
            rfreq[p] = 1;
        }
        else {                                // recursively compute the values
            build(left(p) , L              , (L + R) / 2);
            build(right(p), (L + R) / 2 + 1, R          );
            lval[p] = lval[left(p)];
            rval[p] = rval[right(p)];
            int leftFreq = lfreq[left(p)];
            if (lval[left(p)] == lval[right(p)]) leftFreq += lfreq[right(p)];
            int rightFreq = rfreq[right(p)];
            if (rval[right(p)] == rval[left(p)]) rightFreq += rfreq[left(p)];
            int best = max(ans[left(p)], ans[right(p)]);
            best = max(best, leftFreq);
            best = max(best, rightFreq);
            int middle = rfreq[left(p)];
            if (rval[left(p)] == lval[right(p)]) middle += lfreq[right(p)];
            best = max(best, middle);
            lfreq[p] = leftFreq;
            rfreq[p] = rightFreq;
            ans[p] = best;
        } }

    Result rmq(int p, int L, int R, int i, int j) {                  // O(log n)
        if (i >  R || j <  L) return make_result(false); // current segment outside query range
        if (L >= i && R <= j) return make_result(true, lval[p], rval[p], lfreq[p], rfreq[p], ans[p]);               // inside query range

        // compute the min position in the left and right part of the interval
        Result p1 = rmq(left(p) , L              , (L+R) / 2, i, j);
        Result p2 = rmq(right(p), (L+R) / 2 + 1, R          , i, j);

        if (!p1.inRange) return p2;   // if we try to access segment outside query
        if (!p2.inRange) return p1;                               // same as above

        int l = p1.lval;
        int r = p2.rval;
        int lfreq = p1.lfreq;
        int rfreq = p2.rfreq;
        int lans = p1.ans;
        int rans = p2.ans;
        int middle = p1.rfreq;
        if (p1.rval == p2.lval) middle += p2.lfreq;
        if (p1.lval == p2.lval) lfreq += p2.lfreq;
        if (p2.rval == p1.rval) rfreq += p1.rfreq;
        int best = max(lans, rans);
        best = max(best, middle);

        return make_result(true, l, r, lfreq, rfreq, best);
    }

public:
    SegmentTree(const vi &_A) {
        A = _A; n = (int)A.size();              // copy content for local usage
        ans.assign(4 * n, 0);            // create large enough vector of zeroes
        lval.assign(4 * n, INF);
        rval.assign(4 * n, INF);
        lfreq.assign(4 * n, 0);
        rfreq.assign(4 * n, 0);
        build(1, 0, n - 1);                                  // recursive build
    }

    int rmq(int i, int j) { return rmq(1, 0, n - 1, i, j).ans; }   // overloading
};

int main() {
    int n, q, l, r, tmp;
    while (cin >> n) {
        if (n == 0) break;
        cin >> q;
        vi a;
        for (int i = 0; i < n; i++) {
            cin >> tmp;
            a.push_back(tmp);
        }
        SegmentTree st(a);
        for (int i = 0; i < q; i++) {
            cin >> l >> r;
            cout << st.rmq(l - 1, r - 1) << endl;
        }
    }
    return 0;
}