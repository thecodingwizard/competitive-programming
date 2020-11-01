// 8 min
// lol i solved this problem before

#include <bits/stdc++.h>

using namespace std;

int ft[100001];
bool vis[100001];
int out[100001];

int qry(int x) {
    int ans = 0;
    while (x) {
        ans += ft[x];
        x -= x&-x;
    }
    return ans;
}

void upd(int k, int v) {
    while (k <= 100000) {
        ft[k] += v;
        k += k&-k;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int n; cin >> n;

    int ans = 0;
    vector<int> inp;
    for (int i = 1; i <= 2*n; i++) {
        int x; cin >> x;
        inp.push_back(x);
        out[x] = i;
    }
    for (int i = 1; i <= 2*n; i++) {
        int x = inp[i-1];
        if (vis[x]) {
            upd(out[x], -1);
        } else {
            ans += qry(out[x]);
            upd(out[x], 1);
            vis[x] = 1;
        }
    }
    cout << ans << endl;

    return 0;
}
