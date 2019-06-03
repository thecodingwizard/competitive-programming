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
#define LSOne(S) (S & (-S))
#define ZERO (-2)
#define POSITIVE (-10)
#define NEGATIVE (-100)
typedef vector<int> vi;

class FenwickTree {
private:
    vi zeroes, positive, A; // positive if integer is 1, negative if 0

public:
    FenwickTree() {}
    // initialization: n + 1 zeroes, ignore index 0
    FenwickTree(int n) { zeroes.assign(n + 1, 0); positive.assign(n + 1, POSITIVE); A.assign(n + 1, POSITIVE); }

    pair<int, int> rsq(int b) {                                     // returns RSQ(1, b)
        int zero = 0; for (int x = b; x; x -= LSOne(x)) {
            zero += zeroes[x];
        }
        bool sign = true;
        for (; b; b -= LSOne(b)) {
            if (positive[b] == NEGATIVE) sign = !sign;
        }
        int ans = sign ? POSITIVE : NEGATIVE;
        return make_pair(zero, ans);
    }

    int rsq(int a, int b) {                              // returns RSQ(a, b)
        pair<int, int> x = rsq(b);
        pair<int, int> y = a == 1 ? make_pair(0, POSITIVE) : rsq(a - 1);
        int zero = x.first - y.first;
        if (zero > 0) return ZERO;
        if (x.second == POSITIVE && y.second == NEGATIVE) return NEGATIVE;
        if (x.second == POSITIVE && y.second == POSITIVE) return POSITIVE;
        if (x.second == NEGATIVE && y.second == NEGATIVE) return POSITIVE;
        if (x.second == NEGATIVE && y.second == POSITIVE) return NEGATIVE;
    }

    // adjusts value of the k-th element by v (v can be +ve/inc or -ve/dec)
    void adjust(int k, int v) {                    // note: n = ft.size() - 1
        for (int i = k; i < (int)zeroes.size(); i += LSOne(i)) {
            if (A[k] != ZERO && v == ZERO) zeroes[i]++;
            if (A[k] == ZERO && v != ZERO) zeroes[i]--;
        }
        for (int i = k; i < (int)positive.size(); i += LSOne(i)) {
            if ((A[k] == NEGATIVE && v == POSITIVE)
                || (A[k] == NEGATIVE && v == ZERO)
                || (A[k] == POSITIVE && v == NEGATIVE)
                || (A[k] == ZERO && v == NEGATIVE)) {
                if (positive[i] == POSITIVE) positive[i] = NEGATIVE;
                else positive[i] = POSITIVE;
            }
        }
        A[k] = v;
    }
};

int main() {
    int N, K;
    while (cin >> N >> K) {
        int x;
        FenwickTree ft(N);
        for (int i = 1; i <= N; i++) {
            cin >> x;
            if (x == 0) {
                ft.adjust(i, ZERO);
            } else if (x > 0) {
                ft.adjust(i, POSITIVE);
            } else if (x < 0) {
                ft.adjust(i, NEGATIVE);
            }
        }
        char c;
        int a, b;
        for (int i = 0; i < K; i++) {
            cin >> c >> a >> b;
            if (c == 'C') {
                if (b == 0) {
                    ft.adjust(a, ZERO);
                } else if (b > 0) {
                    ft.adjust(a, POSITIVE);
                } else {
                    ft.adjust(a, NEGATIVE);
                }
            } else {
                char ans;
                int result = ft.rsq(a, b);
                if (result == ZERO) {
                    ans = '0';
                } else if (result == POSITIVE) {
                    ans = '+';
                } else {
                    ans = '-';
                }
                cout << ans;
            }
        }
        cout << endl;
    }
    return 0;
}