#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define ii pair<int, int>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define inf 1000000010

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int w, h; cin >> w >> h;
    vector<vector<ll>> A; A.resize(w+2);
    F0R(i, w+2) A[i].assign(h+2, 0);
    int n; cin >> n;
    F0R(i, n) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        FOR(x, 1, w+1) {
            FOR(y, 1, h+1) {
                ll di = max(abs(a-x), abs(b-y));
                ll nxt = c - (ll)d*di;
                if (nxt > 0) {
                    A[x][y] += nxt;
                }
            }
        }
    }
    FOR(x, 1, w+2) {
        FOR(y, 1, h+2) {
            //cout << x << ", " << y << " ==> " << A[x][y] << endl;
            A[x][y] += A[x-1][y] + A[x][y-1] - A[x-1][y-1];
        }
    }

    int q; cin >> q;
    F0R(i, q) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        ll sum = A[c][d] - A[a-1][d] - A[c][b-1] + A[a-1][b-1];
        ll size = (d-b+1)*(c-a+1); 
        cout << sum/size + ((sum%size)*2>=size?1:0) << endl;
    }

    return 0;
}
