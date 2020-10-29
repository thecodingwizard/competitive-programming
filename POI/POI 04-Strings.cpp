/*
 * See also: https://www.cnblogs.com/ydnhaha/p/9809409.html
 *
 * Arbitrarily root the tree.
 *
 * To find the first number, note that at each node of the tree, we need ceil((n-1)/2) strings, where n is the number of *children* of that node.
 * However, if we're at the root of the tree, then we need ceil(n/2) strings where n is the number of children of the root.
 *
 * We can binary search on the second number. Define solve(i) = the minimum length of the path that connects node i to its parent.
 * For a given node i, we call solve(j) for every child j of node i. Insert the values of solve(j) into a multiset.
 *
 * If i has an even number of children, also insert 0 into the multiset; we either match this 0 with one of the children (the child is connected
 * to node i only, nothing else), or we match 0 with the parent (in which case we want to return 1 from solve(i). hopefully this will be more clear
 * later.)
 *
 * Now, while the multiset is not empty, take the greatest value from the multiset and remove it. We want to find another child to match this value with.
 * So, if our binary search target length is mx, then we search the multiset for the largest number less than or equal to mx-value. If such a number exists,
 * delete it from the multiset; we've "paired" those two children. If the value does not exist, then we are forced to match the original value with the parent.
 * So we set the original value aside.
 *
 * Note that we can have at most one value set aside since we can only match the parent with one child. Also, because we have an odd number of children
 * (if we had an even number of children then we added 0 to the multiset as a fake child), we must have exactly one value set aside. The answer to solve(i)
 * is simply this value plus one (the plus one comes from the edge connecting node i to its parent).
 *
 * The root node needs some very minor modification (we add a fake node when we have an odd number of children rather than when we have an even number of children).
 */

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define ii pair<int, int>
#define f first
#define s second
#define mp make_pair

const int inf = 1000000000;

int n;
vector<int> adj[10000];

int getMinBits(int u = 0, int p = 0) {
    int ans = 0;
    if (u == 0) {
        ans += ((int)adj[u].size()+1)/2;
    } else {
        ans += ((int)adj[u].size()-1)/2;
    }
    for (int v : adj[u]) {
        if (v != p) {
            ans += getMinBits(v, u);
        }
    }
    return ans;
}

int solve(int u, int p, int mx) {
    multiset<int> nums;
    for (int v : adj[u]) {
        if (v != p) {
            nums.insert(solve(v, u, mx));
        }
    }
    if (adj[u].size() % 2 == 1) {
        nums.insert(0);
    }
    int aside = -1;
    while (!nums.empty()) {
        int cur = *nums.rbegin();
        nums.erase(--nums.end());
        auto it = nums.upper_bound(mx-cur);
        if (it == nums.begin()) {
            if (aside == -1) {
                aside = cur;
                continue;
            } else {
                return inf;
            }
        }
        --it;
        nums.erase(it);
    }
    return aside + 1;
}

int main() {
    cin >> n;
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        --a; --b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    int minBits = getMinBits();

    int lo = 1, hi = n, mid, ans = -1;
    while (lo < hi) {
        mid = (lo+hi)/2;
        if (solve(0, 0, mid) <= mid) {
            hi = mid;
            ans = mid;
        } else {
            lo = mid + 1;
        }
    }

    cout << minBits << " " << ans << endl;
    return 0;
}
