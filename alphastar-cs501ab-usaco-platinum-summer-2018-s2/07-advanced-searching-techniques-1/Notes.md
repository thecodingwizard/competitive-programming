# Binary Indexed Trees (Fenwick Trees)

### Classic Application: Counting Inversions

Given an array of numbers, how many inversions are in the array?

**Inversion**: When a bigger number appears before a smaller number. i.e.
```#i, j s.t. a(i) > a(j) and i < j```

**Solution using Binary Indexed Trees**: For every possible value, query the binary indexed
tree for the number of numbers between 0...infinity, and 0...x where x is the current
value. Then update the tree to add 1 to index x. Pseudocode below.

```
for i = 1 to N
    ans += sum(INF) - sum(a(i))
    update(a(i), 1)
```


# Lowest Common Ancestor

1. Root a node (via DFS, node choice doesn't matter)
2. Assign each node a parent (the root's parent is itself)
3. Define `p[i][j]` to be the parent of node `j` `2^i` nodes up
```
p[0][x] = parent of node x
p[1][x] = p[0][p[0][x]]
...
p[i][x] = p[i - 1][p[i - 1][x]]
```

To calculate the LCA of two nodes, first make the depth of the two nodes the same.
For example, if the depth of one node is 17, and the other node is 35, we must make
the lower node `35 - 17 = 18` steps higher.

We essentially binary search to find the LCA. If the parent two nodes above
the nodes we are looking for are the same, we do nothing. If they are different, then
our query becomes the LCA of those two nodes.

```
// Building the parent array, n log n
dfs(int x, int pa, int d) {                  // node, parent of node, depth of node
    depth[x] = d
    p[0][x] = pa
    for i = 1 to ceil(log2 n)                // ceil(log2 n) = 17 for n = 100,000
        p[i][x] = p[i - 1][p[i - 1][x]]
    dfs on children
}

// query, log n
int lca(int a, int b) {
    /* ===== Bring a and b to the same depth ===== */
    if (depth[a] < depth[b])
        swap(a, b)           // we assue a is the deeper node
    c = depth[a] - depth[b]
    for i = 0 to 20                    // 20 = ceil(log2 n) for n = 1,000,000
        if ((c >> i) & 1)
            a = p[i][a]
    if (a == b) return a        // Edge case: lca(a, b) = b
    
    /* ===== LCA ===== */
    for i = 20 to 0                    // 20 = ceil(log2 n) for n = 1,000,000
        if (p[i][a] != p[i][b])
            a = p[i][a]
            b = p[i][b]
    return p[0][a]
}

// distance between two nodes a and b, log n
dist(x) = distance from node 1 to node x
lca(a, b) = lowest common ancestor of a, b
dist(a, b) = distance from node a to node b

dist(a, b) = dist(a) + dist(b) - 2*dist(lca(a, b))
```