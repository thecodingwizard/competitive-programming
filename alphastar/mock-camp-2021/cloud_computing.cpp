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

int n, m;

struct event {
    int c, f; ll v;
    bool isCustomer;
};

vector<event> A;
bool operator <(const event &a, const event &b) {
    int x = -a.f;
    int y = -b.f;
    return tie(x, a.isCustomer) < tie(y, b.isCustomer);
}

const int maxcores = 2000*50;
ll dp[2][maxcores+1];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    F0R(i, n) {
        int c, f; ll v; cin >> c >> f >> v;
        A.pb(event{c,f,v,0});
    }
    cin >> m;
    F0R(i, m) {
        int c, f; ll v; cin >> c >> f >> v;
        A.pb(event{c,f,v,1});
    }
    sort(all(A));

    F0R(i, maxcores + 1) dp[0][i] = i == 0 ? 0 : -1e15;
    F0R(i, n+m) {
        F0R(j, maxcores+1) {
            dp[(i+1)%2][j] = dp[i%2][j];
        }
        F0R(j, maxcores + 1) {
            if (A[i].isCustomer) {
                if (j >= A[i].c) {
                    dp[(i+1)%2][j-A[i].c] = max(dp[(i+1)%2][j-A[i].c], dp[i%2][j] + A[i].v);
                }
            } else {
                if (j + A[i].c <= maxcores) {
                    dp[(i+1)%2][j + A[i].c] = max(dp[(i+1)%2][j+A[i].c], dp[i%2][j] - A[i].v);
                }
            }
        }
    }

    ll best = 0;
    F0R(i, maxcores+1) {
        best = max(best, dp[(n+m)%2][i]);
    }
    cout << best << endl;

    return 0;
}
