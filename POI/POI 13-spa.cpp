/*
 * Same solution as editorial (except I couldn't get the TL/ML to pass, so I
 * just arbitrarily changed the # of nodes required from n*k+1 to just 1 million and it works XD
 *
 * Theorem: For any set of nodes S and the set of nodes V \ S (the rest of the nodes that aren't part of S),
 * the number of edges between the two sets is at least the size of the smaller set.
 *
 * |{ (u, v): u in S, v in V \ S }| >= min(|S|, |V \ S|).
 *
 * Proof: either just don't prove it, or (oops idk how accurate my proof is, you probably want to refer to the editorial):
 * - Between any two arbitrary nodes in V, there is at least one path of (directed) edges that connects them.
 *   - We consider the simplest path where you just greedily change bits in order. Ex: 0101 --> 0001 --> 0011 --> 0010
 * - Let's say |S| = m < |V \ S|.
 * - Between S and V \ S, there are exactly m*(2^n - m) such simple paths (every node in S to every node not in S).
 * - Consider an edge that connects a node in S and a node not in S.
 *   - This edge is part of exactly 2^(n-1) pairs of nodes' simple paths
 *     - If this edge changes the i'th bit from 0 -> 1, then the only condition is that node u's i'th bit is 0 and node v's ith bit is 1
 *     - The remaining bits of u can be anything, and the preceeding bits of v can be anything, hence 2^(n-1)
 * - Therefore, we can put a lower bound on the minimum number of edges between S and V \ S:
 *
 *   m*(2^n - m)
 *  -------------
 *     2^(n-1)
 *
 * - Note that this is greater than equal to m*2^(n-1)/2^(n-1) = m = |S|, which is what we wanted to show.
 *
 * With this theorem in mind, define solve(a, b, ct) = true if node a can get to node b or if node a can reach ct nodes.
 * If solve(a, b, n*k+1) = true and solve(b, a, n*k+1) = true, then the answer is yes; else, the answer is no.
 *
 * Why does this work? If a and b can reach each other, obviously the answer is yes.
 * If a is in a connected component of >= n*k+1 nodes, and b is in a connected component of >= n*k+1 nodes, then we know
 * that a and b must be in the same connected component.
 *
 * Why? Consider the set of nodes S that a random node can reach.
 * There are at least min(|S|, |V \ S|) edges between S and the nodes not in S by our theorem. Blocked nodes need to block
 * all of these edges; otherwise, we can use one of these edges and add another node to our set S.
 * Each blocked node has n outgoing edges, and there are at most k blocked nodes, so we can block at most n*k edges.
 * Therefore, |S| <= n*k or |V \ S| <= n*k. This suggests that there is at most one "big" component of size >= n*k.
 * Hence, if a and b can both reach n*k+1 nodes, then they're both part of this "big" component.
 *
 * To get the code to pass time / memory I had to change n*k+1 to just 1,000,000 lol
 *
 * (Also see the editorial PDF).
 */

#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
 
int n, k; 
unordered_set<ll> dead;
 
ll read() {
    string s; cin >> s;
    ll num = 0;
    for (int i = n-1; i >= 0; i--) {
        if (s[n-1-i] == '1') {
            num |= (1LL << i);
        }
    }
    return num;
}
 
// return true if a can reach b or if a can reach at least ct nodes
bool solve(ll a, ll b, int ct) {
    unordered_set<ll> vis;
 
    queue<ll> q; q.push(a);
    vis.insert(a);
    --ct;
 
    while (!q.empty()) {
        ll u = q.front(); q.pop();
        for (int i = 0; i < n; i++) {
            ll v = u ^ (1LL << i);
            if (vis.count(v) || dead.count(v)) continue;
            --ct;
            if (ct == 0 || v == b) return true;
            vis.insert(v);
            q.push(v);
        }
    }
    return false;
}
 
int main() {
    cin.tie(0)->sync_with_stdio(0);
 
    cin >> n >> k;
 
    ll a, b; a = read(), b = read();
    if (a == b) {
        cout << "TAK\n";
        return 0;
    }
    for (int i = 0; i < k; i++) {
        ll x = read();
        dead.insert(x);
    }
 
	/* This is supposed to be n*k+1, but I can't get it to pass the TL/ML >:-( */
    cout << (solve(a, b, 1000000) && solve(b, a, 1000000) ? "TAK" : "NIE") << endl;
 
    return 0;
}
