#include <bits/stdc++.h>

using namespace std;

#define f first
#define s second

int sz[500*500+10], pa[500*500+10];

int wat(int u) {
    return pa[u] == u ? u : pa[u] = wat(pa[u]);
}

void uf(int a, int b) {
    a = wat(a), b = wat(b);
    if (sz[a] > sz[b]) return uf(b, a);
    pa[a] = b;
    sz[b] += sz[a];
}

int main() {
    int n; cin >> n;
    int A[n][n]; for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> A[i][j];
    for (int i = 0; i < n*n+10; i++) {
        sz[i] = 1;
        pa[i] = i;
    }
    vector<pair<int, pair<int, int>>> edges;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i+1<n) edges.push_back({abs(A[i][j]-A[i+1][j]),{i*n+j,(i+1)*n+j}});
            if (j+1<n) edges.push_back({abs(A[i][j]-A[i][j+1]),{i*n+j,(i)*n+(j+1)}});
        }
    }
    sort(edges.begin(), edges.end());
    for (auto e : edges) {
        if (!(wat(e.s.f) == wat(e.s.s))) {
            uf(e.s.f, e.s.s);
            if (sz[wat(e.s.f)] >= (n*n+1)/2) {
                cout << e.f << endl;
                return 0;
            }
        }
    }
    return 0;
}
