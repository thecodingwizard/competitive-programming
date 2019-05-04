# Hamiltonian Path

Given a graph, visit every node exactly once. 

Brute Force Complexity: Around `O((n+1)!)`. Simply check all permutations.

Slightly faster DP solution: DP with state `pos` and `mask`, similar to TSP. Complexity is `O(n^2 * 2^n)`.
There are `n * 2^n` states, and each takes `n` time to compute.

# Eulerian Tour

```
vector<int> tour
dfs(int x)
    while x has edges
        pick an edge
        delete it
        dfs node that edge connects to
    add x to tour
```

# Checking for Cycles in DAG

```
dfs(x) {
    onStack[x] = true
    visited[x] = true
    for child if not visited:
        if (onStack[child]) cycle!
        dfs(child)
    add x to front of topological sort (topological sort will be reverse order)
    onStack(x) = false
```

# Longest Path for DAG

Call dp(x) the longest path that ends on x.

Process nodes in topological sort order as follows:

```
dp(y) = max(dp(y), dp(x) + weight(x -> y)))
```

The maximum dp value anywhere is the longest path in DAG.

# Finding SCC

**SCC**: A subgraph of a directed graph such that for any two nodes a, b, there exists a path
from a to b and from b to a.