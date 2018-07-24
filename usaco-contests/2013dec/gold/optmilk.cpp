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

int left (int p) { return p << 1; }
int right(int p) { return (p << 1) + 1; }

struct Node {
    int bothEmpty, leftEmpty, rightEmpty, noneEmpty;
    Node(){}
    Node(int _a, int _b, int _c, int _d) : bothEmpty(_a), leftEmpty(_b), rightEmpty(_c), noneEmpty(_d) {}
};

Node tree[(1 << 17)];
int val[40001];

void merge(int p) {
    tree[p].bothEmpty = max(tree[left(p)].bothEmpty + tree[right(p)].rightEmpty, tree[left(p)].leftEmpty + tree[right(p)].bothEmpty);
    tree[p].leftEmpty = max(tree[left(p)].bothEmpty + tree[right(p)].noneEmpty, tree[left(p)].leftEmpty + tree[right(p)].leftEmpty);
    tree[p].rightEmpty = max(tree[left(p)].rightEmpty + tree[right(p)].rightEmpty, tree[left(p)].noneEmpty + tree[right(p)].bothEmpty);
    tree[p].noneEmpty = max(tree[left(p)].rightEmpty + tree[right(p)].noneEmpty, tree[left(p)].noneEmpty + tree[right(p)].leftEmpty);
}

void build(int p, int L, int R) {
    if (L == R) tree[p] = Node(0, 0, 0, val[L]);
    else {
        build(left(p), L, (L+R)/2);
        build(right(p), (L+R)/2+1, R);
        merge(p);
    }
}

void adjust(int p, int L, int R, int idx, int newVal) {
    if (idx > R || idx < L) return;
    if (L == idx && R == idx) {
        val[idx] = newVal;
        tree[p] = Node(0, 0, 0, newVal);
        return;
    }
    adjust(left(p), L, (L+R)/2, idx, newVal);
    adjust(right(p), (L+R)/2+1, R, idx, newVal);
    merge(p);
}

int main() {
    freopen("optmilk.in", "r", stdin);
    freopen("optmilk.out", "w", stdout);

    int n, d;
    cin >> n >> d;
    for (int i = 0; i < n; i++) cin >> val[i];
    build(1, 0, n - 1);
    long long ans = 0;
    for (int i = 0; i < d; i++) {
        int a, b; cin >> a >> b;
        adjust(1, 0, n - 1, --a, b);
        ans += tree[1].noneEmpty;
    }
    cout << ans << endl;
    return 0;
}
