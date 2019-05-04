# Biconnectivity

2 types: Vertex biconnected, Edge biconnected

Vertex biconnected: Removing a vertex splits the graph in two. Such vertex is called an articulation point.

Edge biconnected: Removing a edge splits the graph in two. Such edge is called a bridge.

To discover articulation points / bridges:

1. DFS through the whole tree, assigning a "time" for every node you visit in order.
2. Use Tarjan lowlinking: define lowlink(node) to be the earliest node that can be reached by going
   down DFS tree and using backedge (an edge that's not the parent)
3. If lowlink child >= dfs number of node: articulation point
4. Note: root is articulation point if and only if root has > 1 children in dfs tree

# Biconnected Components (BCC)

A Biconnected component is a set of edges that is biconnected