#include<bits/stdc++.h>
#define MAX_NODES 100001
using namespace std;

/*
 * Solution idea:
 *
 * Step 0: Store the weight of the edge (u, v) in G in edgeWeights.
 * We use an array of unordered_map<int, int> because the lookup should be O(1),
 * without excessive memory usage.
 *
 * Step 1: Find the MST, T, of the given graph G. We use an adjacency list for T.
 *
 * Step 2: Build two arrays using Binary Lifting on T: ancestor and maxEdge.
 *
 * ancestor[i][j] informs the 2^j-th ancestor of the node i, in T.
 * If no such ancestor exists, it's 0.
 *
 * Similar for maxEdge[i][j]: It's the maximum cost of an edge in the path from the node i to its
 * 2^j-th ancestor, in T. If no edge exists in that path, it's 0.
 *
 * We initialize these arrays by performing a DFS on T, and fill the rest of them
 * by using a specialized form of DP in trees, known as "Binary Lifting".
 *
 * Step 3: For each query (u, v), find the maximum cost of an edge in the path from u to v in T.
 * This basically involves finding the maximum cost of an edge in the path from
 * u to LCA(u, v) and also in the path from v to LCA(u, v), so the algorithm is
 * a slight modification of the binary-lifting-based LCA algorithm.
 * When we find it, it's a simple matter of arithmetic.
 */

vector<tuple<int, int, int>> edges;
vector<pair<int, int>> mst[MAX_NODES];
unordered_map<int, int> edgeWeights[MAX_NODES];
int depth[MAX_NODES], parent[MAX_NODES], ancestor[MAX_NODES][18], maxEdge[MAX_NODES][18];
int numNodes, numEdges, numQueries, mstWeight;

void initialize() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  cin >> numNodes >> numEdges;
  for (int i = 0; i < numEdges; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    if (u > v) swap(u, v);
    edges.emplace_back(w, u, v);
    edgeWeights[u][v] = w;
  }
}

int findParent(int node) {
  return parent[node] = (parent[node] == node) ? node : findParent(parent[node]);
}

void buildMST() {
  sort(edges.begin(), edges.end());
  iota(parent, parent + MAX_NODES, 0);
  for (auto& [w, u, v] : edges) {
    int rootU = findParent(u), rootV = findParent(v);
    if (rootU != rootV) {
      if (rootU > rootV) swap(rootU, rootV);
      parent[rootV] = rootU;
      mst[u].emplace_back(v, w);
      mst[v].emplace_back(u, w);
      mstWeight += w;
    }
  }
}

void initializeLCA(int node, int currentDepth) {
  depth[node] = currentDepth;
  for (auto& [neighbor, weight] : mst[node]) {
    if (!depth[neighbor]) {
      ancestor[neighbor][0] = node;
      maxEdge[neighbor][0] = weight;
      initializeLCA(neighbor, currentDepth + 1);
    }
  }
}

void buildSparseTable() {
  for (int j = 1; j < 18; j++) {
    for (int i = 1; i <= numNodes; i++) {
      ancestor[i][j] = ancestor[ancestor[i][j - 1]][j - 1];
      maxEdge[i][j] = max(maxEdge[i][j - 1], maxEdge[ancestor[i][j - 1]][j - 1]);
    }
  }
}

int getMaxEdgeOnPath(int u, int v) {
  if (depth[u] < depth[v]) swap(u, v);
  int diff = depth[u] - depth[v], maxWeight = 0;
  for (int i = 0; diff; diff >>= 1, i++) {
    if (diff & 1) {
      maxWeight = max(maxWeight, maxEdge[u][i]);
      u = ancestor[u][i];
    }
  }
  if (u != v) {
    for (int i = 17; i >= 0; i--) {
      if (ancestor[u][i] != ancestor[v][i]) {
        maxWeight = max({maxWeight, maxEdge[u][i], maxEdge[v][i]});
        u = ancestor[u][i];
        v = ancestor[v][i];
      }
    }
    maxWeight = max({maxWeight, maxEdge[u][0], maxEdge[v][0]});
  }
  return maxWeight;
}

void handleQueries() {
  cin >> numQueries;
  while (numQueries--) {
    int u, v;
    cin >> u >> v;
    if (u > v) swap(u, v);
    int newEdgeWeight = edgeWeights[u][v];
    int maxEdgeOnPath = getMaxEdgeOnPath(u, v);
    cout << mstWeight + newEdgeWeight - maxEdgeOnPath << '\n';
  }
}

int main() {
  initialize();
  buildMST();
  initializeLCA(1, 1);
  buildSparseTable();
  handleQueries();
}
