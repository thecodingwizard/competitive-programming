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
#define llinf 1e18

struct ticket {
    int c; ll p; int a, b, i;
};

const int maxn = 100000;

int n, k;
vector<ticket> tickets;
bool used[maxn];
ll dist1[maxn];
ll distn[maxn];
ll dist1andn[maxn];
ll distall[maxn];

vector<int> stTickets[2*maxn];
vector<int> updLoc[maxn];
void precalcUpd(int l, int r, int v) {
    l += n;
    r += n+1;
    for (; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
            updLoc[v].pb(l);
            l++;
        }
        if (r & 1) {
            r--;
            updLoc[v].pb(r);
        }
    }
}
void upd(int l, int r, int v, bool rem = false) {
    if (rem) return;
    for (int i : updLoc[v]) {
        stTickets[i].pb(v);
    }
    /*
    l += n;
    r += n+1;
    for (; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
            if (rem) stTickets[l].erase(v);
            else stTickets[l].insert(v);
            l++;
        }
        if (r & 1) {
            r--;
            if (rem) stTickets[r].erase(v);
            else stTickets[r].insert(v);
        }
    }
    */
}

vector<int> activeTickets;
void qry(int k) {
    for (k += n; k > 1; k >>= 1) {
        for (auto x : stTickets[k]) {
            if (used[x]) continue;
            activeTickets.pb(x);
        }
        stTickets[k].clear();
    }
}

void calc(ll *dist) {
    for (int i = 0; i < 2*maxn; i++) stTickets[i].clear();
    for (ticket t : tickets) {
        if (used[t.i]) continue;
        upd(t.a, t.b, t.i);
    }

    // step 2: update starting from lowest distances
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    for (int i = 0; i < n; i++) {
        if (dist[i] < llinf) {
            pq.push(mp(dist[i], i));
        }
    }
    while (!pq.empty()) {
        pair<ll, int> u = pq.top(); pq.pop();
        if (u.f > dist[u.s]) continue;

        // step 3: update distances of all tickets
        qry(u.s);
        for (int xi : activeTickets) {
            ticket x = tickets[xi];
            assert(!used[x.i]);
            used[x.i] = true;
            if (dist[u.s] + x.p < dist[x.c]) {
                dist[x.c] = dist[u.s] + x.p;
                pq.push(mp(dist[x.c], x.c));
            }
            upd(x.a, x.b, x.i, true);
        }
        activeTickets.clear();
    }
}

ll sparsetable1[maxn+10][20];
ll sparsetable2[maxn+10][20];
int logVal[maxn+10];
void calc1andn() {
    for (int i = 0; i < n; i++) {
        dist1andn[i] = dist1[i] + distn[i];
        sparsetable1[i][0] = dist1[i];
        sparsetable2[i][0] = distn[i];
    }
    sparsetable1[n][0] = sparsetable2[n][0] = llinf;
    for (int i = 1; i <= n; i++) {
        logVal[i] = i == 1 ? 0 : logVal[i/2]+1;
    }
    for (int j = 1; j < 20; j++) {
        for (int i = 0; i + (1 << j) <= n; i++) {
            sparsetable1[i][j] = min(sparsetable1[i][j-1], sparsetable1[i+(1<<(j-1))][j-1]);
            sparsetable2[i][j] = min(sparsetable2[i][j-1], sparsetable2[i+(1<<(j-1))][j-1]);
        }
    }
    for (ticket x : tickets) {
        int i = logVal[x.b-x.a+1];
        ll best1 = min(sparsetable1[x.a][i], sparsetable1[x.b-(1<<i)+1][i]);
        ll bestn = min(sparsetable2[x.a][i], sparsetable2[x.b-(1<<i)+1][i]);
        dist1andn[x.c] = min(dist1andn[x.c], best1+bestn+x.p);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    for (int i = 0; i < k; i++) {
        ticket x; cin >> x.c >> x.p >> x.a >> x.b;
        x.i = i;
        x.c--;
        x.a--;
        x.b--;
        tickets.pb(x);
    }

    // step 1: initialize base distances
    for (ticket x : tickets) precalcUpd(x.a, x.b, x.i);
    for (int i = 0; i < k; i++) used[i] = false;
    for (int i = 0; i < n; i++) {
        dist1[i] = llinf;
    }
    dist1[0] = 0;
    for (ticket x : tickets) {
        if (x.a == 0) {
            dist1[x.c] = min(dist1[x.c], x.p);
            used[x.i] = true;
        }
    }
    calc(dist1);
    for (int i = 0; i < k; i++) used[i] = false;
    for (int i = 0; i < n; i++) {
        distn[i] = llinf;
    }
    distn[n-1] = 0;
    for (ticket x : tickets) {
        if (x.a == n-1) {
            distn[x.c] = min(distn[x.c], x.p);
            used[x.i] = true;
        }
    }
    calc(distn);

    calc1andn();

    for (int i = 0; i < k; i++) used[i] = false;
    calc(dist1andn);

    for (int i = 0; i < n; i++) {
        if (dist1andn[i] >= llinf) {
            cout << -1 << "\n";
        } else {
            cout << dist1andn[i] << "\n";
        }
    }

    return 0;
}
