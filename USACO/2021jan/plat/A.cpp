/* Same as editorial */

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define ii pair<int, int>
#define f first
#define s second
#define pb push_back
#define mp make_pair

const int mod = 1000000007;
const int inf = 1000000010;
const int maxm = 4e5+10;

int k; 

vector<int> numEdges;
vector<vector<int>> evenDist;
vector<vector<int>> oddDist;
vector<vector<int>> adj;

ll compute_sum(vector<vector<int>> &dist) {
    // less[x] = number of tuples with max distance <= x
    vector<ll> less; less.assign(maxm, 0);
    vector<vector<ll>> ct; ct.resize(dist.size());
    vector<ll> left(maxm, 1), right(maxm, 1);
    for (int i = 0; i < k; i++) {
        ct[i].assign(2*numEdges[i]+1, 0);
        for (int j : dist[i]) {
            if (j < ct[i].size()) ct[i][j]++;
        }
        for (int j = 1; j < ct[i].size(); j++) ct[i][j] += ct[i][j-1];
        for (int j = 0; j < ct[i].size(); j++) {
            left[j] = (left[j]*ct[i][j])%mod;
        }
        right[ct[i].size()] = (right[ct[i].size()] * ct[i].back()) % mod;
    }
    for (int i = 1; i < maxm; i++) {
        right[i] = (right[i]*right[i-1])%mod;
    }
    ll ans = 0;
    F0R(i, maxm) {
        /*
        less[i] = 1;
        F0R(j, dist.size()) {
            less[i] *= (i >= ct[j].size() ? ct[j].back() : ct[j][i]);
            less[i] %= mod;
        }
        */
        less[i] = right[i]*left[i]%mod;
        if (i > 0) ans = (((ans + (less[i]-less[i-1])*i)%mod)+mod)%mod;
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> k;
    evenDist.resize(k);
    oddDist.resize(k);

    F0R(i, k) {
        int n, m; cin >> n >> m; numEdges.pb(m);
        vector<vector<int>>().swap(adj);
        evenDist[i].assign(n, inf);
        oddDist[i].assign(n, inf);
        adj.resize(n);
        F0R(j, m) {
            int a, b; cin >> a >> b; --a; --b;
            adj[a].pb(b);
            adj[b].pb(a);
        }
        evenDist[i][0] = 0;
        queue<ii> q; q.push(mp(0, 0));
        while (!q.empty()) {
            ii u = q.front(); q.pop();
            for (int v : adj[u.f]) {
                int newDist = u.s == 0 ? evenDist[i][u.f] : oddDist[i][u.f];
                newDist++;
                if (newDist % 2 == 0) {
                    // even
                    if (evenDist[i][v] == inf) {
                        evenDist[i][v] = newDist;
                        q.push(mp(v, 0));
                    }
                } else {
                    // odd
                    if (oddDist[i][v] == inf) {
                        oddDist[i][v] = newDist;
                        q.push(mp(v, 1));
                    }
                }
            }
        }
    }

    vector<vector<int>> maxDist; maxDist.resize(k);
    F0R(i, k) {
        maxDist[i].resize(evenDist[i].size());
        F0R(j, evenDist[i].size()) {
            maxDist[i][j] = max(evenDist[i][j], oddDist[i][j]);
        }
    }

    ll evenAns = compute_sum(evenDist);
    ll oddAns = compute_sum(oddDist);
    ll overcountAns = compute_sum(maxDist);

    cout << (evenAns + oddAns - overcountAns + mod) % mod << endl;

    return 0;
}
