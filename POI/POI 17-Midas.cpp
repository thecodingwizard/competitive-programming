/*
 * The idea is we process the nodes in increasing order of value. When we process a node, we look at
 * all queries where that node is the first node. We check the second node to make sure we have already processed
 * it -- if we haven't processed it, that means the second node's value is greater, meaning we should output NIE.
 * Otherwise, we can output TAK since the first value is greater than or equal to the second value.
 *
 * In order to process nodes in increasing order of value, we start by processing all the 0 nodes at the same time.
 * All the right nodes of the zero nodes must be of value 1, so we process all the 1-valued nodes next.
 *
 * Starting from value 1 nodes, when we process nodes of value x, we make a list of all the nodes to the left
 * of a node of value x. We also make a list of all the nodes to the right of a node of value x.
 * We maintain a queue of lists of nodes we have to process; all the nodes in a given list are of the same value.
 * After we finish processing value x, we add the list of nodes to the left of a node of value x into the queue.
 * Then, we add the list of nodes to the right of a node of value x into the queue.
 *
 * See implementation for more details...
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
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define inf 1000000010

#define maxn 1000000
int L[maxn], R[maxn];
bool done[maxn];
vector<ii> queries[maxn];
bool bad[maxn];
vector<int> todo[maxn];
int idx = 0;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    F0R(i, n) {
        cin >> L[i] >> R[i]; --L[i]; --R[i];
    }

    int z; cin >> z;
    F0R(i, z) {
        int a, b; cin >> a >> b; --a; --b;
        queries[a].pb(mp(b, i));
    }

    int cur = 0;
    while (cur != -1) {
        todo[idx].pb(cur);
        cur = L[cur];
    }
    idx++;
    queue<int> process; process.push(0);
    while (!process.empty()) {
        int x = process.front(); process.pop();
        vector<int> lft, rht;
        for (int node : todo[x]) {
            done[node] = true;
        }
        for (int node : todo[x]) {
            for (auto q : queries[node]) {
                if (!done[q.f]) bad[q.s] = true;
            }
            if (L[node] != -1 && x != 0) {
                lft.pb(L[node]);
            }
            if (R[node] != -1) {
                rht.pb(R[node]);
            }
        }
        if (!lft.empty()) {
            todo[idx++] = lft;
            process.push(idx-1);
        }
        if (!rht.empty()) {
            todo[idx++] = rht;
            process.push(idx-1);
        }
    }

    F0R(i, z) cout << (bad[i] ? "NIE" : "TAK") << "\n";

    return 0;
}
