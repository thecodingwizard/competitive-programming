// 3 min

#include <bits/stdc++.h>

using namespace std;

#define f first
#define s second

int pa[50000];
int sz[50000];

int find(int x) {
    return pa[x] == x ? x : pa[x] = find(pa[x]);
}

void unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return;
    if (sz[x] < sz[y]) {
        swap(x, y);
    }
    pa[y] = x;
    sz[y] += sz[x];
}

int main() {
    int v, e; cin >> v >> e;
    for (int i = 0; i < v; i++) {
        sz[i] = 1;
        pa[i] = i;
    }

    vector<pair<int, pair<int, int>>> edges;
    for (int i = 0; i < e; i++) {
        int a, b, c; cin >> a >> b >> c; --a; --b;
        edges.push_back(make_pair(c, make_pair(a, b)));
    }
    sort(edges.begin(), edges.end());

    int cost = 0;
    for (auto e : edges) {
        if (find(e.s.f) != find(e.s.s)) {
            cost += e.f;
            unite(e.s.f, e.s.s);
        }
    }
    cout << cost << endl;

    return 0;
}
