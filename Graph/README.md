# Graph Algorithms

| File | Algorithm | Problem |
|------|-----------|---------|
| `BFS_unreachable_count.cpp` | Breadth-First Search | Count vertices unreachable from a given source |
| `Dijkstra_shortest_path.cpp` | Dijkstra's algorithm | Single-source shortest paths on a weighted undirected graph |
| `Dijkstra_with_time_constraints.cpp` | Dijkstra's algorithm (variant) | Shortest path where some edges are unusable within a forbidden time window |

## Input format

```
n m            # vertices, edges
a b t          # edge between vertices a and b with weight t  (m lines)
s              # source vertex (and possibly extra params for the time-constraint variant)
```
