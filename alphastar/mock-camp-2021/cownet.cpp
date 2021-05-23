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

int p, n, k, m;
vector<ii> adj[5000];
vector<ii> adjrev[5000];
// c1 is to server, c2 is from server
int c1[5000], c2[5000];

void calcc1() {
    F0R(i, p) {
        c1[i] = inf;
    }
    c1[n] = 0;
    priority_queue<ii, vector<ii>, greater<ii>> pq;
    pq.push(mp(0, n));
    while (!pq.empty()) {
        ii u = pq.top(); pq.pop();
        if (c1[u.s] < u.f) continue;
        for (ii v : adjrev[u.s]) {
            if (c1[v.f] > c1[u.s] + v.s) {
                c1[v.f] = c1[u.s] + v.s;
                pq.push(mp(c1[v.f], v.f));
            }
        }
    }
}

void calcc2() {
    F0R(i, p) {
        c2[i] = inf;
    }
    c2[n] = 0;
    priority_queue<ii, vector<ii>, greater<ii>> pq;
    pq.push(mp(0, n));
    while (!pq.empty()) {
        ii u = pq.top(); pq.pop();
        if (c2[u.s] < u.f) continue;
        for (ii v : adj[u.s]) {
            if (c2[v.f] > c2[u.s] + v.s) {
                c2[v.f] = c2[u.s] + v.s;
                pq.push(mp(c2[v.f], v.f));
            }
        }
    }
}

vector<int> costs;

ll ps[5000];
ll cost(int a, int b) {
    if (a == b) return 0;
    return (ps[b-1]-(a-1>=0?ps[a-1]:0))*(b-a-1);
}

ll dp[2][5001];

void dnc(int l, int r, int L, int R, bool i) {
    if (l > r) return;
    int mid = (l+r)/2;
    pair<ll, int> opt = mp(1e15, -1);
    for (int k = L; k <= min(mid, R); k++) {
        opt = min(opt, mp(dp[!i][k]+cost(k, mid), k));
    }
    dp[i][mid] = opt.f;
    dnc(l, mid-1, L, opt.s, i);
    dnc(mid+1, r, opt.s, R, i);
}

ll solve() {
    F0R(i, n+1) dp[0][i] = 1e15;
    dp[0][0] = 0;
    F0R(i, k) {
        dnc(0, n, 0, n, (i+1)%2);
    }
    return dp[k%2][n];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> p >> n >> k >> m;
    F0R(i, m) {
        int a, b, w; cin >> a >> b >> w; --a; --b;
        adj[a].pb(mp(b, w));
        adjrev[b].pb(mp(a, w));
    }

    calcc1();
    calcc2();

    F0R(i, n) {
        costs.push_back(c1[i]+c2[i]);
    }
    sort(all(costs));

    ps[0] = costs[0];
    FOR(i, 1, n) ps[i] = ps[i-1]+costs[i];

    cout << solve() << endl;

    return 0;
}
