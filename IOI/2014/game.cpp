/*
 * Solution: Create a 1D array count[n].
 * hasEdge: increment count[max(u, v)]. If the new value equals max(u, v), then return 1. Else, return 0.
 *
 * Read code for a better idea of what's going on.
 *
 * Very informal induction proof: We're always going to have the graph connected.
 *
 * Base case: Nodes 0 - 1 are connected.
 * Assume nodes 0...n-1 are connected. If we're getting queried for (x, n) where x < n, then we output
 * 0 n-2 times, and on the n-1st time, we output 1. Then nodes 0...n are connected.
 *
 * Note that we only output 1 n-1 times in total. Further note that it takes n(n-1)/2 queries for us to output
 * n-1 1's, so Mei-Yu must query n(n-1)/2 times to confirm that the graph is indeed connected.
 *
 * Intuitively, we're trying to delay outputting 1 as much as possible, while ensuring that in the end, node n
 * will be directly connected to exactly one node that's less than n. So we count the number of times we've
 * received a query of (x, n) where x < n, and we keep outputting 0 n-2 times. On the n-1st time,
 * we must output 1, otherwise n won't be connected to any nodes < n.
 */

#include <bits/stdc++.h>
#include "game.h"
using namespace std;

int ct[1500];
void initialize(int N) {
    for (int i = 0; i < N; i++) ct[i] = 0;
}
int hasEdge(int u, int v) {
    return ++ct[max(u, v)] == max(u, v);
}