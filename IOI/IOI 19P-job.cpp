/*
 * https://github.com/tmwilliamlin168/CompetitiveProgramming/blob/master/IOI/19P-Job.cpp
 *
 * "merging" a child node with a parent node basically means that we will take the parent,
 * then immediately after taking the parent we take that child node.
 */

#include "job.h"
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define pb push_back
#define all(x) x.begin(), x.end()
#define ii pair<int, int>
#define f first
#define s second
#define mp make_pair

vector<int> adj[200000];
vector<ll> p, u, d;

struct cmp {
    // returns true if i should go after j
    bool operator()(int i, int j) {
        return d[i]*u[j]>d[j]*u[i];
    }
};
struct cmp2 {
    // returns true if i should go after j
    bool operator()(int i, int j) {
        return d[i]*u[j]>=d[j]*u[i];
    }
};
priority_queue<int, vector<int>, cmp> children[200000];

bool merged[200000];

ll ans = 0;
ll curTime = 0;
void dfs(int node) {
    for (int child : adj[node]) {
        dfs(child);
    }
    for (int child : adj[node]) {
        children[node].push(child);
    }
    while (!children[node].empty()) {
        if (cmp2()(node, children[node].top())) {
            int toMerge = children[node].top();
            children[node].pop();
            ans -= d[toMerge]*u[node];
            d[node] += d[toMerge];
            u[node] += u[toMerge];
            if (children[node].size() < children[toMerge].size()) {
                swap(children[node], children[toMerge]);
            }
            while (children[toMerge].size()) {
                children[node].push(children[toMerge].top());
                children[toMerge].pop();
            }
            merged[toMerge] = true;
        } else {
            break;
        }
    }
}

long long scheduling_cost(std::vector<int> _p, std::vector<int> _u, std::vector<int> _d) {
    int n = _p.size();
    for (int i = 0; i < n; i++) {
        p.pb(_p[i]);
        u.pb(_u[i]);
        d.pb(_d[i]);
    }

    for (int i = 1; i < n; i++) {
        adj[p[i]].pb(i);
    }

    dfs(0);

    vector<int> indices;
    for (int i = 0; i < n; i++) {
        if (!merged[i]) {
            indices.pb(i);
        }
    }
    sort(all(indices), cmp());
    reverse(all(indices));

    ll curTime = 0;

    for (auto x : indices) {
        curTime += d[x];
        ans += curTime*u[x];
    }

    return ans;
}
