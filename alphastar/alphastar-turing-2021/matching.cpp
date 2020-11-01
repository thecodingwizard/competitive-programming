#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m; cin >> n >> m;
    int B[n]; for (int i = 0; i < n; i++) cin >> B[i];
    int A[m]; for (int i = 0; i < m; i++) cin >> A[i];
    
    vector<int> indices;
    for (int i = 0; i <= m-n; i++) {
        int prev = -1;
        bool bad = false;
        for (int j = 0; j < n; j++) {
            int cur = A[i+B[j]-1];
            if (cur < prev) {
                bad = true;
                break;
            }
            prev = cur;
        }
        if (!bad) indices.push_back(i+1);
    }
    cout << indices.size() << endl;
    for (int v : indices) cout << v << " ";
    cout << endl;

    return 0;
}
