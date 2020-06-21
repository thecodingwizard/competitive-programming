#include <bits/stdc++.h>

using namespace std;

#define ii pair<int,int>
#define f first
#define s second

int main() {
    int n; cin >> n;
    int W[n]; for (int i = 0; i < n; i++) cin >> W[i];
    int A[n][n]; for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> A[i][j];

    int cst = 0;
    
    priority_queue<ii, vector<ii>, greater<ii>> pq;
    for (int i = 0; i < n; i++) {
        pq.push({W[i], i});
    }
    while (!pq.empty()) {
        ii u = pq.top(); pq.pop();
        if (W[u.s] < u.f) continue;
        cst += W[u.s];
        for (int v = 0; v < n; v++) {
            if (A[u.s][v] < W[v]) {
                W[v] = A[u.s][v];
                pq.push({W[v], v});
            }
        }
    }

    cout << cst << endl;
}
