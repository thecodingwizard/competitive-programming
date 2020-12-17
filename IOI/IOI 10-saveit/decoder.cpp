#include "grader.h"
#include "decoder.h"

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define F0R(i, n) for (int i = 0; i < n; ++i)
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define pb push_back
#define inf 1000000010
#define ii pair<int, int>
#define f first
#define s second
#define mp make_pair

int ans[1000], codes[1000];
vector<int> children[1000];

int readNum() {
    int n = 0;
    F0R(i, 10) {
        int x = decode_bit();
        if (x) n |= (1 << i);
    }
    return n;
}

void dfs(int u) {
    for (int v : children[u]) {
        int code = codes[v];
        if (code == 0) ans[v] = ans[u];
        else if (code == 1) ans[v] = ans[u]+1;
        else if (code == 2) ans[v] = ans[u]-1;
        else assert(false);
        dfs(v);
    }
}

queue<int> codeQueue;
int readCode() {
    if (codeQueue.size() == 0) {
        ll num = 0;
        F0R(i, 59) {
            int x = decode_bit();
            if (x == 1) num |= (1LL << i);
        }
        F0R(i, 37) {
            codeQueue.push(num%3);
            num /= 3;
        }
    }
    int x = codeQueue.front();
    codeQueue.pop();
    return x;
}

void decode(int n, int h) {
    int pa[1000];

    FOR(i, 1, n) {
        pa[i] = readNum();
        children[pa[i]].pb(i);
    }
    F0R(i, h) {
        ans[0] = readNum();

        FOR(j, 1, n) {
            codes[j] = readCode();
        }
        while (!codeQueue.empty()) codeQueue.pop();

        dfs(0);

        F0R(j, n) {
            hops(i, j, ans[j]);
        }
    }
}
