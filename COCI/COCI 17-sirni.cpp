/*
 * Same as dolphingarlic's solution
 *
 * This is basically an mst problem except n^2 edges are too many
 *
 * For every multiple of every number, we can draw an edge from the number to the
 * first number that's greater than equal to the multiple of that number.
 * We can remove duplicate numbers, so the number of edges is maxVal/1 + maxVal/2 + ... + maxVal/maxVal
 * which is maxVal log maxVal.
 *
 * Then, we can run kruskal's.
 *
 * Note that TL is tight so remove the log factors from sorting and binary searching...
 */

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define pb push_back
#define mp make_pair
#define f first
#define s second
#define ii pair<int, int>

int pa[100000], sz[100000];
vector<ii> edges[(int)1e7+10];
int idx[(int)1e7+10];
int number[(int)1e7+10];
int findSet(int x) {
    return pa[x] == x ? x : pa[x] = findSet(pa[x]);
}
void unite(int a, int b) {
    a = findSet(a); b = findSet(b);
    if (sz[a] > sz[b]) swap(a, b);
    pa[a] = b;
    sz[b] += sz[a];
}

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);
    int n; cin >> n;

    set<int> nums;
    for (int i = 0; i < n; i++) {
        int p; cin >> p;
        nums.insert(p);
    }
    int ctr = 0;
    for (int num : nums) {
        idx[num] = ctr++;
    }
    for (int i = 0; i < n; i++) {
        sz[i] = 1;
        pa[i] = i;
    }
    auto it = nums.begin();
    for (int i = 0; i <= 1e7; i++) {
        while (it != nums.end() && *it < i) it++;
        if (it == nums.end()) number[i] = -1;
        else number[i] = *it;
    }

    for (int num : nums) {
        int prev = -1;
        for (int i = num; i <= 1e7; i += num) {
            int it = i == num ? number[i+1] : number[i];
            if (it != -1) {
                if (prev == it) continue;
                prev = it;
                edges[it%num].emplace_back(idx[num], idx[it]);
            } else {
                break;
            }
        }
        /*
        for (int num2 : nums) {
            if (num < num2)
                edges.pb(mp(num2%num, mp(idx[num], idx[num2])));
        }
        */
    }

    ll ans = 0;
    for (int c = 0; c <= 1e7; c++) {
        for (auto e : edges[c]) {
            if (findSet(e.f) != findSet(e.s)) {
                ans += c;
                unite(e.f, e.s);
            }
        }
    }
    cout << ans << endl;

    return 0;
}
