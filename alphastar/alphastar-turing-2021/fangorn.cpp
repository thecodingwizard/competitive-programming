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

int w, h; 
ii gimli;
vector<ii> camps;
vector<pair<ii, int>> trees;

bool cmp(ii b, ii c, ii a) {
    ii v1 = mp(b.f-a.f, b.s-a.s);
    ii v2 = mp(c.f-a.f, c.s-a.s);
    ll res = (ll)v1.f*v2.s - (ll)v1.s*v2.f;
    return res > 0 ? true : false;
}

void init(ii a) {
    sort(all(trees), [&a](pair<ii, int> B, pair<ii, int> C) {
        ii b = B.f, c = C.f;
        return cmp(b, c, a);
    });
}

bool check(ii a) {
    int bad = !cmp(trees.back().f, trees[0].f, a);
    FOR(i, 1, sz(trees)) {
        if (!cmp(trees[i-1].f, trees[i].f, a)) bad++;
    }
    return bad <= 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> w >> h;
    cin >> gimli.f >> gimli.s;

    int c; cin >> c; camps.resize(c);
    F0R(i, c) cin >> camps[i].f >> camps[i].s;

    int n; cin >> n; trees.resize(n);
    F0R(i, n) {
        cin >> trees[i].f.f >> trees[i].f.s;
        trees[i].s = i;
    }

    vector<int> can;
    init(gimli);
    F0R(i, c) {
        if (check(camps[i])) can.pb(i+1);
    }

    cout << can.size() << endl;
    for (auto x : can) cout << x << " ";
    cout << endl;

    return 0;
}
