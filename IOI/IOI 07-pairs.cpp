/*
 * 1D case can be solved with an ordered statistics tree
 * 2D case can be solved with a 1D fenwick tree + line sweep, rotate it 45 degrees
 * 3D case:
 * - For every point, I just looped through all different z values and then reduced
 *   it to the 2D case. To solve the 2D case, I used a 2d fenwick tree.
 *
 * My final time complexity for 3D case was O(n*d*logd*logd)
 * It's also possible to solve the 3D case with a 3D fenwick tree apparently
 */

#include <bits/stdc++.h>

using namespace std;

#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <class T> using Tree = tree<T, null_type, less<T>,
     rb_tree_tag, tree_order_statistics_node_update>;
#define ii pair<int, int>
#define f first
#define s second

int b, n, d, m; 

struct FT {
    vector<int> ft;
    int n;
    void init(int _n) {
        n = _n;
        ft.assign(n+1, 0);
    }
    void upd(int k, int v) {
        while (k <= n) {
            ft[k] += v;
            k += k&-k;
        }
    }
    int qry(int k) {
        k = min(k, n-1);
        if (k <= 0) return 0;
        int sum = 0;
        while (k) {
            sum += ft[k];
            k -= k&-k;
        }
        return sum;
    }
};

struct FT2D {
    vector<FT> ft;
    int X, Y;
    void init(int _x, int _y) {
        X = _x; Y = _y;
        ft.resize(X+1);
        for (int i = 0; i <= X; i++) {
            ft[i].init(Y+1);
        }
    }
    void upd(int x, int y, int v) {
        assert(x > 0 && x <= X && y > 0 && y <= Y);
        while (x < X) {
            ft[x].upd(y, v);
            x += x&-x;
        }
    }
    int qry(int x, int y) {
        if (x <= 0 || y <= 0) return 0;
        x = min(x, X); y = min(y, Y);
        int sum = 0;
        while (x) {
            sum += ft[x].qry(y);
            x -= x & -x;
        }
        return sum;
    }
};

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);
    cin >> b >> n >> d >> m;
    if (b == 1) {
        Tree<pair<int, int>> TS;
        long long ans = 0;
        vector<int> nums;
        for (int i = 0; i < n; i++) {
            int x; cin >> x;
            nums.push_back(x);
        }
        sort(nums.begin(), nums.end());
        int ct = 0;
        for (int x : nums) {
            ans += ct-TS.order_of_key(make_pair(x-d, 0));
            TS.insert(make_pair(x, ct++));
        }
        cout << ans << endl;
    } else if (b == 2) {
        vector<ii> nums;
        for (int i = 0; i < n; i++) {
            int x, y; cin >> x >> y;
            nums.push_back(make_pair(x-y, x+y));
        }
        sort(nums.begin(), nums.end());
        int l = 0;
        FT ft; ft.init(2*m+1);
        long long ans = 0;
        for (int r = 0; r < n; r++) {
            while (nums[r].f - nums[l].f > d) {
                ft.upd(nums[l].s, -1);
                l++;
            }
            ans += ft.qry(nums[r].s+d) - ft.qry(nums[r].s-d-1);
            ft.upd(nums[r].s, 1);
        }
        cout << ans << endl;
    } else {
        vector<ii> nums[m+1];
        for (int i = 0; i < n; i++) {
            int x, y, z; cin >> x >> y >> z;
            nums[z].push_back(make_pair(x-y+m, x+y));
        }
        FT2D ft[m+1];
        for (int i = 1; i <= m; i++) {
            ft[i].init(2*m+1, 2*m+1);
            for (ii j : nums[i]) {
                ft[i].upd(j.f, j.s, 1);
            }
        }
        long long ans = 0;
        for (int i = 1; i <= m; i++) {
            for (ii j : nums[i]) {
                for (int k = 1; k <= m; k++) {
                    int d2 = d - abs(k - i);
                    if (d2 < 0) continue;
                    ans += ft[k].qry(j.f + d2, j.s + d2) - ft[k].qry(j.f + d2, j.s - d2 - 1) - ft[k].qry(j.f - d2 - 1, j.s + d2) + ft[k].qry(j.f - d2 - 1, j.s - d2 - 1);
                }
                ans--; // don't count the point itself
            }
        }
        assert(ans % 2 == 0);
        cout << ans / 2 << endl;
    }
    return 0;
}
