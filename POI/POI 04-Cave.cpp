/*
 *
 */

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

int n; 
vector<int> adj[50000];

vector<int> dp(int u, int p) {
    vector<int> children;
    for (int v : adj[u]) {
        if (v != p) {
            vector<int> other = dp(v, u);
            for (int x : other) children.pb(x);
        }
    }

    int rootVal = 0;
    sort(all(children));
    for (int i = sz(children)-2; i>=0; i--) {
        if (children[i] == children[i+1]) {
            rootVal = children[i]+1;
            break;
        }
    }
    for (int x : children) {
        if (x == rootVal) {
            rootVal++;
        }
    }

    vector<int> ans; ans.pb(rootVal);
    for (int x : children) {
        if (x > rootVal) ans.pb(x);
    }

    return ans;
}

int main() {
    cin >> n;
    F0R(i, n-1) {
        int a, b; cin >> a >> b;
        adj[a-1].pb(b-1);
        adj[b-1].pb(a-1);
    }

    vector<int> vals = dp(0, 0);
    int mx = 0;
    for (int x : vals) mx = max(x, mx);
    cout << mx << endl;

    return 0;
}
