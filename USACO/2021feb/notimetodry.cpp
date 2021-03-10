#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define vi vector<int>
#define pb push_back
#define mp make_pair
#define ii pair<int, int>
#define f first
#define s second
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()

int n, q; 
vector<int> input;
vector<int> A;

vector<pair<ii, int>> queries;
int ans[200000];
int lastSeen[200000];

int ft[200001];

void upd(int k, int v) {
    while (k <= 200000) {
        ft[k] += v;
        k += k&-k;
    }
}
int qry(int k) {
    int s = 0;
    while (k) {
        s += ft[k];
        k -= k&-k;
    }
    return s;
}

int main() {
    cin >> n >> q;
    F0R(i, n) {
        int x; cin >> x; input.pb(x);
    }

    stack<ii> s;
    int ctr = 0;
    for (int x : input) {
        while (!s.empty() && s.top().f > x) s.pop();
        if (s.empty() || s.top().f != x) {
            s.push(mp(x, ctr++));
        }
        A.pb(s.top().s);
    }

    for (int i = 0; i < q; i++) {
        int a, b; cin >> a >> b;
        --a; --b;
        queries.pb(mp(mp(a, b), i));
    }

    sort(all(queries), [](pair<ii, int> a, pair<ii, int> b) {
        return a.f.s < b.f.s;
    });
    F0R(i, n) lastSeen[i] = -1;

    int idx = 0;
    F0R(i, n) {
        if (lastSeen[A[i]] != -1) {
            upd(lastSeen[A[i]], -1);
        }
        lastSeen[A[i]] = i+1;
        upd(lastSeen[A[i]], 1);

        while (idx < queries.size() && queries[idx].f.s <= i) {
            ans[queries[idx].s] = qry(n) - qry(queries[idx].f.f);
            idx++;
        }
    }

    F0R(i, q) {
        cout << ans[i] << "\n";
    }

    return 0;
}
